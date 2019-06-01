/*
 * R Jesse Chaney
 */

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// I need to check this on big and little endian systems, with
//   both 32 bit and 64 bit.
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

// I have put a LOT of comments into this code. If you are not using
//   an editor that make comments stand out (such as by color), this
//   may be difficult to read. In any case, you will be wading through
//   a lot of comments to find a few lines of code. I hope the comments
//   are helpful.

// compile with
//     gcc -Wall -o sizeof sizeof.c

//#include <stdio.h>
//#include <values.h>
//#include <limits.h>

// changed for compilation on xv6
#include "types.h"
#include "user.h"

// This will just print a few bits of information about the system it
//   is compiled and run on.

int 
main(int argc, char *argv[])
{
  printf(1, "\n");
  // The __WORDSIZE macro is not 100% guaranteed to be correct.
  printf(1, "This appears to be a %d bit system.\n", __WORDSIZE);

  {
    // There are other ways to accomplish this. It does not check for other
    //   things like middle endian, odd endian, or obtuse endian.
    // Most of the time, the compiler will take care the the endianess for
    //   you. However, in some network programming, endianess becomes
    //   very important.
    //
    // Inspired from:
    //   http://www.ibm.com/developerworks/aix/library/au-endianc/
    //   http://www.geeksforgeeks.org/little-and-big-endian-mystery/

    // This needs to be unsigned.
    unsigned int i = 1;
    // The variable c is a character pointer to the first byte of the integer
    //   value i. We'll use this when we check for big/little endian.
    char *c = (char *) &i;

    if (0 != (*c)) {
      // If the contents of the MSB is non-zero, this is
      // a little endian architecture.
      printf(1, "\tThis system is little endian.\n");
    }
    else {
      printf(1, "\tThis system is big endian.\n");
    }
  }
  printf(1, "\n");

  // The sizeof() operator returns the number of bytes a type (or struct)
  //   requires. The return type of the sizeof() operator is (normalloy) a
  //   size_t, so you need to cast it to print it (without warnings from 
  //   the compiler).
  //
  // The <blaa>BITS values come from the values.h include file. They should
  //   let you know how many bits certain types require. Not all types have
  //   a <blaa>BITS macro in values.h though.
  printf(1, "Size of basic C data types\n");
  printf(1, "                              bytes   bits\n");
  printf(1, "\tsizeof(char)\t\t %d     %d\n", (int) sizeof(char)
	 , (int) CHARBITS);
  printf(1, "\tsizeof(short)\t\t %d    %d\n", (int) sizeof(short)
	 , (int) SHORTBITS);
  printf(1, "\tsizeof(int)\t\t %d    %d\n", (int) sizeof(int)
	 , (int) INTBITS);
  printf(1, "\tsizeof(unsigned)\t %d    %d\n", (int) sizeof(unsigned)
	 // This is not directly supported by a nice macro, so I'm
	 //   calculating it.
	 , (int) (sizeof(unsigned) * CHARBITS));
  printf(1, "\tsizeof(long)\t\t %d    %d\n", (int) sizeof(long)
	 , (int) LONGBITS);
  printf(1, "\tsizeof(long long)\t %d    %d\n", (int) sizeof(long long)
	 // This is not directly supported by a nice macro, sir I'm
	 //   calculating it.
	 , (int) (sizeof(long long) * CHARBITS));
#ifdef NOPE
  // HAHAHAHAHA... Even if the compiler supports __int128_t on the 32-bit 
  // compiles for xv6, i'm not going to tell you about it.
  printf(1, "\tsizeof(__int128_t)\t%d    %d (gcc special 128 bit integer)\n", (int) sizeof(__int128_t)
	 // This is not directly supported by a nice macro, so I'm
	 //   calculating it.
	 , (int) (sizeof(__int128_t) * CHARBITS));
#endif // NOPE
  printf(1, "\tsizeof(float)\t\t %d    %d\n", (int) sizeof(float)
	 , (int) FLOATBITS);
  printf(1, "\tsizeof(double)\t\t %d    %d\n", (int) sizeof(double)
	 , (int) DOUBLEBITS);
  printf(1, "\tsizeof(long double)\t%d    %d\n", (int) sizeof(long double)
	 // This is not directly supported by a nice macro, sci I'm
	 //   calculating it.
	 , (int) (sizeof(long double) * CHARBITS));
  printf(1, "\tsizeof(void *)\t\t %d    %d (aka a pointer)\n"
	 , (int) sizeof(void *), (int) PTRBITS);

  if (argc < 2) {
    // If you put something on the command line after the program name
    //   (anything), then this chunk of code will be skipped. It is just
    //   a bit ugly when it prints and wraps around a couple times on
    //   the screen.
    printf(1, "\n");
    printf(1, "The lower/upper limit of some basic C types\n");
    printf(1, "\tMINSHORT\t\t%d\n", (short) MINSHORT);
    printf(1, "\tMININT\t\t\t%d\n", (int) MININT);
    printf(1, "\tMINLONG\t\t\t%d\n", (long) MINLONG);
    printf(1, "\tMAXSHORT\t\t%d\n", (short) MAXSHORT);
    printf(1, "\tMAXINT\t\t\t%d\n", (int) MAXINT);
    printf(1, "\tMAXLONG\t\t\t%d\n", (long) MAXLONG);

    // I should put some things in here about max values for the various
    //   unsigned types. I don't see many in values.h, though they'd be
    //   pretty easy to calculate. It does not provide a way to print the 
    //   unsigned types.
    // In addition, xv6 does not provide a way to print a long, let alone
    //   a long long. 
    // RJC

#ifdef NOT_NOW
    printf(1, "\tULONG_MAX\t\t%lu\n", ULONG_MAX);
    printf(1, "\tULLONG_MAX\t\t%llu\n", ULLONG_MAX);

    // The values for these don't seem to be easy to generate as bit fields.
    printf(1, "\n");
    printf(1, "\tMINFLOAT\t\t%f\n", MINFLOAT);    // Turns out, this is boring.
    printf(1, "\tMINDOUBLE\t\t%lf\n", MINDOUBLE); // So is this.

    printf(1, "\tMAXFLOAT\t\t%f\n", MAXFLOAT);
    // This is pretty darn long. It will probably wrap a couple
    //   lines.
    printf(1, "\tMAXDOUBLE\t\t%lf\n", MAXDOUBLE);
#endif // NOT_NOW
  }

  // xv6 does not accept an exit value.
  exit();
}
