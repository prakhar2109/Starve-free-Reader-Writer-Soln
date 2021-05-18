#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int val = 0, readers_count = 0;
sem_t seq_mutex, write_mutex, r_mutex;

void *reader(void *id)
{

  //Entry Section
  sem_wait(&seq_mutex); //Remeber the order of arrival (wait for turn)
  sem_wait(&r_mutex);   //preventing more than one access to below segment
  readers_count++;

  if (readers_count == 1)
    sem_wait(&write_mutex); // if it is the first reader then get the access to the reader for accessing the critical section and block the writer from accessing it

  sem_post(&seq_mutex);
  sem_post(&r_mutex);
  printf("val read by the reader%d is %d\n", *((int *)id), val);

  //EXIT SECTION
  sem_wait(&r_mutex);
  readers_count--;
  if (readers_count == 0)
    sem_post(&write_mutex); // if it is the last reader then release the access to the critical section so that it can be used by any waiting writer

  sem_post(&r_mutex);
  return id;
}

void *writer(void *id)
{
  sem_wait(&seq_mutex);   //to maintain request order in fifo manner.
  sem_wait(&write_mutex); //get the access to the writer for accessing the critical section and block the readers from accessing it
  sem_post(&seq_mutex);   // release the semaphore to get the next reader/ writer to be serviced
  val = val * 3 + 6;
  printf("val written by the writer%d is %d\n", *((int *)id), val);
  sem_post(&write_mutex);
  return id;
}

int main()
{

  pthread_t readers[5], writers[5];

  sem_init(&seq_mutex, 0, 1);
  sem_init(&r_mutex, 0, 1);
  sem_init(&write_mutex, 0, 1);

  int pt = 0;
  while (pt <= 4)
  {
    pthread_create(&writers[pt], NULL, writer, (void *)&pt);
    pthread_create(&readers[pt], NULL, reader, (void *)&pt);
    pt++;
  }

  pt = 0;
  while (pt <= 4)
  {

    pthread_join(writers[pt], NULL);
    pthread_join(readers[pt], NULL);
    pt++;
  }
  return 0;
}