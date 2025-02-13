#include "common.h"
#include <pthread.h>

int32_t count_max = 0;
int32_t count_min = 0;
pthread_mutex_t count_mut = PTHREAD_MUTEX_INITIALIZER;
uint8_t kill = 0;
pthread_mutex_t kill_mut = PTHREAD_MUTEX_INITIALIZER;

void *ui(void *arg)
{
    if(arg == NULL)
    {
        printf("Bledny argument ui\n");
        return NULL;
    }
    struct common_t *shared = (struct common_t *)arg;
    char input[6];
    while(1)
    {
        scanf("%5s", input);
        if(strcmp(input, "reset") == 0)
        {
            count_max = 0;
            count_min = 0;
        }
        if(strcmp(input, "stat") == 0)
        {
            pthread_mutex_lock(&count_mut);
            printf("MAX zostal wykonany %d razy, a MIN %d razy\n", count_max, count_min);
            pthread_mutex_unlock(&count_mut);
        }
        if(strcmp(input, "quit") == 0)
        {
            pthread_mutex_lock(&kill_mut);
            kill = 1;
            pthread_mutex_unlock(&kill_mut);
            sem_post(&shared->sem_start);
            return NULL;
        }
    }
}

void *proc(void *arg)
{
    if(arg == NULL)
    {
        printf("Bledny argument watka proc\n");
        return NULL;
    }
    struct common_t *shared = (struct common_t *)arg;
    int shm_arr = shm_open(shared->shm_name, O_RDWR, 0666);
    ftruncate(shm_arr, sizeof(int32_t) * shared->size);
    int32_t *arr = mmap(NULL, sizeof(int32_t) * shared->size, PROT_READ | PROT_WRITE,MAP_SHARED, shm_arr, 0);
    int32_t max = 0;
    int32_t min = INT32_MAX;
    for(size_t i = 0; i < shared->size; i++)
    {
        if(min > *(arr + i) && shared->op == 0)
            min  = *(arr + i);
        if(max < *(arr + i) && shared->op == 1)
            max = *(arr + i);
    }
    munmap(arr, sizeof(int32_t) * shared->size);
    pthread_mutex_lock(&count_mut);
    if(shared->op)
        count_max++;
    else
        count_min++;
    pthread_mutex_unlock(&count_mut);
    if(shared->op)
        shared->res = max;
    else
        shared->res = min;
    return NULL;
}

int main()
{
    printf("Kacper Orkwiszewski, 251197\nZadanie na ocene 3\n");
    sem_unlink(SEM_SERVER_ON);
    shm_unlink(SHM_NAME);
    int shm = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
    ftruncate(shm, sizeof(struct common_t));
    struct common_t *shared = mmap(NULL, sizeof(struct common_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0);
    sem_init(&shared->sem_start, 1, 0);
    sem_init(&shared->sem_stop, 1, 0);
    sem_t *server_on = sem_open(SEM_SERVER_ON, O_CREAT | O_EXCL, 0666, 0);
    pthread_t th_ui;
    pthread_t th_proc;
    pthread_create(&th_ui, NULL, ui, shared);
    while(1)
    {
        sem_post(server_on);
        sem_wait(&shared->sem_start);
        pthread_mutex_lock(&kill_mut);
        if(kill)
        {
            pthread_mutex_unlock(&kill_mut);
            break;
        }
        pthread_mutex_unlock(&kill_mut);
        pthread_create(&th_proc, NULL, proc, shared);
        pthread_join(th_proc, NULL);
        sem_post(&shared->sem_stop);
    }
    pthread_join(th_ui, NULL);
    sem_close(&shared->sem_start);
    sem_close(&shared->sem_stop);
    sem_close(server_on);
    sem_unlink(SEM_SERVER_ON);
    munmap(shared, sizeof(struct common_t));
    shm_unlink(SHM_NAME);
    return 0;
}