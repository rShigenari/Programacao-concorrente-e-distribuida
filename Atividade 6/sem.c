#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

char string[100];
pthread_t thr_id_rd;
pthread_t thr_id_wr;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond, cond1;
int read = 0;

void *Reader_thread()
{
    while (1) {
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&cond, &lock);
        printf("Escrito: %s\n", string);
        pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&lock);
    }
}

void *Writer_thread()
{
    while (1) {
        pthread_mutex_lock(&lock);
        printf("Escreva: ");
        scanf("%s", string);
        pthread_cond_signal(&cond);
        pthread_cond_wait(&cond1, &lock);
        pthread_mutex_unlock(&lock);
    }
}

int main(int argc, char *argv[])
{
    pthread_create(&thr_id_rd, NULL, Reader_thread, NULL);
    pthread_create(&thr_id_wr, NULL, Writer_thread, NULL);

    pthread_join(thr_id_rd, NULL);
    pthread_join(thr_id_wr, NULL);

    return 0;
}
