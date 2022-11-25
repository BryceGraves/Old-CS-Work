#define SetBit(j,k)     ( j |= (1 << (k%32)) )
#define ClearBit(j,k)   ( j &= ~(1 << (k%32)) )
#define TestBit(j,k)    ( j & (1 << (k%32)) )

typedef struct BitBlock_s {
  uint32_t bits;
  pthread_mutex_t mutex;
} BitBlock_t;

void *nullifyBitsOfMultiple(void *);
