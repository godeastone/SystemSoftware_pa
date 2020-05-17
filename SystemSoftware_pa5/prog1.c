#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t thread_cond = PTHREAD_COND_INITIALIZER;
int count = 1;

void *function1(void *data)
{
  char *thread_name = (char*)data;

  while(1) {
    pthread_mutex_lock(&mutex_lock);
    if(count > 11) break;
    else if (count < 4 || count > 7 && count < 11) {
      fprintf(stdout, "[%s]  By function1, count value : %d\n", thread_name, count);
      count++;
      pthread_cond_signal(&thread_cond);
    }
    else {
      pthread_cond_wait(&thread_cond, &mutex_lock);
    }
   pthread_mutex_unlock(&mutex_lock);
  }
  pthread_mutex_unlock(&mutex_lock);
}

void *function2(void *data)
{
  char *thread_name = (char*)data;

  while(1) {
    pthread_mutex_lock(&mutex_lock);
    if(count > 11) break;
    else if(3 < count && count < 8 || count > 10) {
      fprintf(stdout, "[%s]  By function2, count value : %d\n", thread_name, count);
      count++;
      pthread_cond_signal(&thread_cond);
    }
    else {
      pthread_cond_wait(&thread_cond, &mutex_lock);
    }
    pthread_mutex_unlock(&mutex_lock);
  }
  pthread_mutex_unlock(&mutex_lock);
}

int main()
{
  pthread_t p_thread[2];
  int thread_id;
  int status;

  //thread creation
  thread_id = pthread_create(&p_thread[0], NULL, function1, (void *)"thread1");
  if(thread_id != 0) {
    fprintf(stderr, "thread creation failed.]n");
  }

  thread_id = pthread_create(&p_thread[1], NULL, function2, (void *)"thread2");
  if(thread_id != 0) {
    fprintf(stderr, "thread creation failed.]n");
  }

  pthread_join(p_thread[0], (void **)&status);
  pthread_join(p_thread[1], (void **)&status);

  return 0;
}
