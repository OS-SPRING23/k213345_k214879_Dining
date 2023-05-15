#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
sem_t chopstick[5];
void *philos(void *n);
void eat(int ph);
int main()
 {
         int i,n[5];
         pthread_t T[5];
         for(i=0;i<5;i++)
         sem_init(&chopstick[i],0,1);
         for(i=0;i<5;i++){
                 n[i]=i;
                 pthread_create(&T[i],NULL,philos,(void *)&n[i]);
                 }
         for(i=0;i<5;i++)
                 pthread_join(T[i],NULL);
         for(i=0;i<5;i++)
                 sem_destroy(&chopstick[i]);
         return 0;
 }
void *philos(void *n)
 {
         int ph=*(int *)n;
         printf("Philosopher %d wants to eat\n",ph);
         syscall(335,ph," wants to eat\n");
         printf("Philosopher %d tries to pick left chopstick\n",ph);
         syscall(335,ph," tries to pick the left chopstick\n");
         sem_wait(&chopstick[ph]);
         printf("Philosopher %d picks the left chopstick\n",ph);
         syscall(335,ph," picks the left chopstick\n");
         printf("Philosopher %d tries to pick the right chopstick\n",ph);
         syscall(335,ph," tries to pick the right chopstick\n");
         sem_wait(&chopstick[(ph+1)%5]);
         printf("Philosopher %d picks the right chopstick\n",ph);
         syscall(335,ph," picks the right chopstick\n");
         eat(ph);
         sleep(2);
         printf("Philosopher %d has finished eating\n",ph);
         syscall(335,ph," has finished eating\n");
         sem_post(&chopstick[(ph+1)%5]);
         printf("Philosopher %d leaves the right chopstick\n",ph);
         syscall(335,ph," leaves the right chopstick\n");
         sem_post(&chopstick[ph]);
         printf("Philosopher %d leaves the left chopstick\n",ph);
         syscall(335,ph," leaves the left chopstick\n");
         pthread_exit(NULL);
         return NULL;
 }
 void eat(int ph)
 {
         printf("Philosopher %d begins to eat\n",ph);
         syscall(335,ph," begins to eat\n");
 }