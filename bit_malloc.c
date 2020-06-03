#include <bits/stdc++.h> 
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <thread>

//swap bits of an integer
int swap_bit(int a, int i, int j) {
    int mask1 = ((a & 0x1<<i) >> i) << j;
    int mask2 = ((a & 0x1<<j) >> j) << i;
    a &= ~(0x1<<i);
    a &= ~(0x1<<j);
    a |= mask1;
    a |= mask2;
 
    return a;   
}

//swap values
void swap_val(int *a, int *b) {
  //a 11
  //b 100
  *a = *a ^ *b; //111  
  *b = *b ^ *a; //11
  *a = *a ^ *b; //100
}

//detect if host is little or beg endian processor
void big_little_endian() {
  int a =1;
  char *aptr=(char *) & a;
  if (*aptr==1)
    printf("Little endian\n");
  else
    printf("Big endian\n");
}

//create own malloc and free
typedef char ALIGN[16];
union header {
	struct {
		size_t size;
		unsigned is_free;
		union header *next;
	} s;
	ALIGN stub;
};

typedef union header header_t;
header_t *head, *tail;
pthread_mutex_t global_malloc_lock;

header_t *get_free_block(size_t size) {
  header_t *curr = head;
  while (curr) {
    if (curr->s.is_free && curr->s.size >= size)
      return curr;
    curr = curr->s.next;
  }
  return NULL;
}

void *malloc(size_t size) {
	size_t total_size;
  void *block;
  header_t *header;
  if (!size)
    return NULL;
  pthread_mutex_lock(&global_malloc_lock);
  header = get_free_block(size);
  if (header) {
    header->s.is_free = 0;
    pthread_mutex_unlock(&global_malloc_lock);
    return (void *) (header+1);
  }
  total_size = sizeof(header_t) + size;
  block = sbrk(total_size);
  if (block == (void*) -1) {
    pthread_mutex_unlock(&global_malloc_lock);
    return NULL;    
  }
  header = block;
  header->s.size = size;
  header->s.is_free = 0;
  header->s.next = NULL;
  if (!head)
    head = header;
  if (tail)
    tail->s.next = header;
  tail =header;
  pthread_mutex_unlock(&global_malloc_lock);
  return (void *) (header+1);
}

void free(void *block) {
  header_t *header, *tmp;
  void *programbreak;
  if (!block)
    return;
  pthread_mutex_lock(&global_malloc_lock);
  header = (header_t *) block-1;
  programbreak = sbrk(0);
  if ((char*) block + header->s.size == programbreak) {
    if (head==tail)
      head = tail = NULL;
    else {
      tmp = head;
      while (tmp) {
        if (tmp->s.next == tail) {
          tmp->s.next = NULL;
          tail = tmp;
        }
        tmp = tmp->s.next;
      }
    }
    sbrk(0 - sizeof(header_t) - header->s.size);
    pthread_mutex_unlock(&global_malloc_lock);
    return;    
  } 
  header->s.is_free = 1;
  pthread_mutex_unlock(&global_malloc_lock);
}

int main() {
  return 0;
}