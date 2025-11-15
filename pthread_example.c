#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int mail = 0;
int iteration = 100000;

void *routine() {
    for(int i=0; i<iteration; i++)
    {
        pthread_mutex_lock(&mutex);
        mail++;    
        pthread_mutex_unlock(&mutex);
    }   
}
void *routine2() {
    for(int i=0; i<iteration; i++)
    {
        pthread_mutex_lock(&mutex);
        mail++;    
        pthread_mutex_unlock(&mutex);
    }   
}

int main() {
    pthread_t t1,t2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, routine, NULL);
    pthread_create(&t2, NULL, routine, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex);
    
    printf("Number of mail: %d\n", mail);
    return 0;
}
