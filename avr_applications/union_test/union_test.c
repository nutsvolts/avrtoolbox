#include <stdio.h>

#include "c:\avrtoolbox\libavr\source\driver\usart\usart.h" 

// Set aside a block of memory to hold data
// that can be char, int, or long data types
// Since a long requires the same space as two ints
// and an int requires the same space as two char
// these arrays occupy the same amount of memory.
union array_t
{
  char cArray[64];
  int iArray[32];
  long lArray[16];
}myArray;

enum{CHAR, INT, LONG};

void show_array(void *p, int type);

int main(void) {
  int i;
  //float f = 123.456;
  long l = 1234567;

  void *vPtr;

  // Initialize usart for printf
  usart0_init_baud(57600);


// Load memory with 64 char
  for(i = 0; i < 64; i++)
  {
    myArray.cArray[i] = '!' + (char)i;
  }
  // Point global void pointer to array
  vPtr = myArray.cArray;
  // Show the characters
  show_array(vPtr,CHAR);
   
// Load memory with 32 ints
  for(i = 0; i < 32; i++)
  {
    myArray.iArray[i] = i+10;
  }
  // Point global void pointer to array
  vPtr = myArray.iArray;
  // Show the characters
  show_array(vPtr,INT);

// Load memory with 16 floats
  for(i = 0; i < 16; i++)
  {
    myArray.lArray[i] = l + (long)i;
  }
  // Point global void pointer to array
  vPtr = myArray.lArray;
  // Show the characters
  show_array(vPtr,LONG);

  return 0;
}

void show_array(void *p, int type)
{
  char c;
  int i,j;
  long l;
  char *cPtr;
  int *iPtr;
  long *lPtr;

  switch(type)
  {
    case CHAR:
      cPtr = p;
      printf("Show char array:\n ");
      for(i = 0; i < 64; i++)
      {
        c = (char)*(cPtr+i);
        printf("%c,",c);
      }
      printf("\n");
      break;
    case INT:
      iPtr = p;
      printf("Show int array:\n ");
      for(i = 0; i < 32; i++)
      {
        j = (int)*(iPtr+i);
        printf("%3d,",j);
      }
      printf("\n");
      break; 
     case LONG:
      lPtr = p;
      printf("Show long array:\n ");
      for(i = 0; i < 16; i++)
      {
        l = (long)*(lPtr+i);
        printf("%ld,",l);
      }
      printf("\n");
      break;   
  }
}


