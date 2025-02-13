#include <stdio.h>
#define SIZE 100
#define FNAME_SIZE 30

struct message_t
{
    char a;
    double b;
    int c;
};

int load_data(struct message_t *cp, int size, const char *filename)
{
    if(cp == NULL || filename == NULL || size <= 0)
        return -1;
    FILE *f = fopen(filename, "rb");
    if(f == NULL)
        return -2;
    unsigned int n = 0;
    if(fread(&n, sizeof(unsigned int), 1, f) == 0)
    {
        fclose(f);
        return -3;
    }
    if(n % 24)
    {
        fclose(f);
        return -3;
    }
    long unsigned int tmp = 0;
    if((tmp = fread(cp, sizeof(struct message_t), size, f)) < (n / 24) && tmp != (long unsigned int)size)
    {
        fclose(f);
        return -3;
    }
    fclose(f);
    return tmp;
}

int decode_message(const struct message_t *cp, int size, char *msg, int text_size)
{
    if(cp == NULL || msg == NULL || size <= 0 || text_size <= 0)
        return 1;
    for(int i = 0; i < size; i++)
    {
        char *tmp = (char*)(cp + i);
        tmp += sizeof(char);
        for(long unsigned int j = sizeof(char); j < sizeof(struct message_t) / 3; j++)
        {
            if(text_size-- == 1)
            {
                *msg = '\0';
                return 0;
            }
            *msg++ = *tmp++;
        }
        tmp += sizeof(double) + sizeof(int);
        for(long unsigned int j = sizeof(int); j < sizeof(struct message_t) / 3; j++)
        {
            if(text_size-- == 1)
            {
                *msg = '\0';
                return 0;
            }
            *msg++ = *tmp++;
        }
    }
    *msg = '\0';
    return 0;
}

int main(void)
{
    printf("Enter file name:");
    char fname[FNAME_SIZE + 1];
    scanf("%30s", fname);
    struct message_t cp[SIZE];
    int size = load_data(cp, SIZE, fname);
    if(size == -2)
    {
        printf("Couldn't open file");
        return 4;
    }
    if(size == -3)
    {
        printf("File corrupted");
        return 6;
    }
    char msg[(SIZE * (sizeof(struct message_t) - sizeof(char) - sizeof(double) - sizeof(int))) + 1];
    int text_size = (SIZE * (sizeof(struct message_t) - sizeof(char) - sizeof(double) - sizeof(int))) + 1;
    decode_message(cp, size, msg, text_size);
    printf("%s", msg);
    return 0;
}