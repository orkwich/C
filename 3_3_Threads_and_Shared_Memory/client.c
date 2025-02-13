#include "common.h"

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("Brak odpowiednich argumentow\n");
        return 1;
    }
    if(strcmp(*(argv + 2), "min") != 0 && strcmp(*(argv + 2), "max") != 0)
    {
        printf("Akceptowane zapytania: max, min\n");
        return 1;
    }
    FILE *f = fopen(*(argv + 1), "r");
    if(f == NULL)
    {
        printf("Blad otwarcia pliku\n");
        return 1;
    }
    sem_t *server_on = sem_open(SEM_SERVER_ON, 0);
    if(server_on == SEM_FAILED)
    {
        printf("Serwer wylaczony\n");
        fclose(f);
        return 1;
    }
    if(sem_trywait(server_on) == -1)
    {
        printf("Serwer zajety\n");
        fclose(f);
        sem_close(server_on);
        return 1;
    }
    int shm = shm_open(SHM_NAME, O_RDWR, 0666);
    ftruncate(shm, sizeof(struct common_t));
    struct common_t *shared = mmap(NULL, sizeof(struct common_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0);
    sprintf(shared->shm_name, "/shm_%d", getpid());
    size_t size = 0;
    int32_t tmp;
    while(!feof(f))
        if(fscanf(f, "%d", &tmp) == 1)
            size++;
    if(size == 0)
    {
        printf("Nie udalo sie odczytac danych z pliku\n");
        fclose(f);
        munmap(shared, sizeof(struct common_t));
        sem_close(server_on);
        return 1;
    }
    int shm_arr = shm_open(shared->shm_name, O_CREAT | O_EXCL | O_RDWR, 0666);
    ftruncate(shm_arr, sizeof(int32_t) * size);
    int32_t *arr = mmap(NULL, sizeof(int32_t) * size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_arr, 0);
    fseek(f, 0, SEEK_SET);
    size_t i = 0;
    while(!feof(f))
        if(fscanf(f, "%d", arr + i) == 1)
            i++;
    fclose(f);
    shared->size = size;
    shared->op = 0;
    if(strcmp(*(argv + 2), "max") == 0)
        shared->op = 1;
    sem_post(&shared->sem_start);
    sem_wait(&shared->sem_stop);
    munmap(arr, sizeof(int32_t) * size);
    shm_unlink(shared->shm_name);
    if(shared->op)
        printf("Wartosc maksymalna: %d\n", shared->res);
    else
        printf("Wartosc minimalna: %d\n", shared->res);
    sem_close(server_on);
    munmap(shared, sizeof(struct common_t));
    return 0;
}