#ifndef KOLOSO2_COMMON_H
#define KOLOSO2_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

#define SEM_SERVER_ON "/semserveron"
#define SHM_NAME "/shmem"

struct common_t
{
    char shm_name[32];
    size_t size;
    uint8_t op; // 1 - max, 0 - min
    int32_t res;
    sem_t sem_stop;
    sem_t sem_start;
};

#endif