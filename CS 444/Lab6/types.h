#ifndef __TYPES_H
# define __TYPES_H

#ifndef NULL
#define NULL 0
#endif // NULL

#ifndef TRUE
#define TRUE 1
#endif // TRUE

#ifndef FALSE
#define FALSE 0
#endif // FALSE

#define PGSIZE          4096    // bytes mapped by a page

typedef unsigned int   uint;
typedef unsigned long  ulong;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;

#endif // __TYPES_H
