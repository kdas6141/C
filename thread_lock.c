//Compilation should be done with gcc a.c -lpthread -lrt
#include <semaphore.h>
#include <pthread.h>

#if 0
sem_t mutex;

void *thread(void *arg) {
	sem_wait(&mutex);
	cout << endl << "Entered" << endl;
	sleep(4);
	cout << endl << "Exiting" << endl;
	sem_post(&mutex);
}

int main() {
	sem_init(&mutex, 0, 1);
	pthread_t t1, t2;
	pthread_create(&t1, NULL, thraed, NULL);
	sleep(2);
	pthread_create(&t2, NULL, thraed, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	sem_destroy(&mutex);
	return 0;
}

#else
// counting semphore
sem_t s;
int main() {
  sem_init(&s, 0, 10); // returns -1 (=FAILED) on OS X
  sem_wait(&s); // Could do this 10 times without blocking
  sem_post(&s); // Announce that we've finished (and one more resource item is available; increment count)
  sem_destroy(&s); // release resources of the semaphore
} 

//pthread mutex
pthread_t tid[2];
int counter;
pthread_mutex_t lock;
void *try_this(void *arg) {
	pthread_mutex_lock(&lock);
	unsigned long i=0;
	counter += 1;
	for (i=0; i<0xffffffff; i++)
		;
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main(void) {
	int i=0;
	int error;
	if (pthred_mutex_init(&lock, NULL) != NULL)
		return 1;
	while (i<2) {
		error = pthread_create(&tid[i], 
			NULL, &try_this, NULL);
		if (error !=0) {
			printf("\nThread can't be created");
			i++;
		}
	}
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_mutex_destroy(&lock);
}

pthread_mutex_t count_mutex;
long long count;

void increment_count() {
	pthread_mutex_lock(&count_mutex);
	count += 1;
	pthread_mutex_unlock(&count_mutex);
}

long long get_count() {
	long long c;
	pthread_mutex_lock(&count_mutex);
	c = count;
	pthread_mutex_unlock(&count_mutex);
	return c;
}
#endif

#if 0
//kernel spinlock
spinlock_t my_lock = SPIN_LOCK_UNLOCKED;
unsigned long flags
spin_lock_irqsave(&my_lock, flags);
spin_lock_irqrestore(&my_lock, flags);
//kernel semaphore
struct semaphore my_sem;
sema_init(&my_sem, 1);
if (down_interruptiable(&my_sem))
	//critical section
up(&my_sem);
#endif