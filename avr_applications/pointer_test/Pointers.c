#include <stdio.h>
#include "c:\avrtoolbox\libavr\source\driver\usart\usart.h" 

void printMyBlock(char *p,int mB);

int main()
{
  // Initialize usart for printf
  usart0_init_baud(57600);
  
  char a = 'A';
  char b = 'B';
  char c = 'C';
  char *p;
  char *q;

  // Point to top of SRAM
  q = (char *)0x8ff;
  // Point to the char a;
  p = &a;

  printf("Pointer p address: &p = %p\n",&p);
  printf("Points to content *p = %c\n",*p);

  printf("\nContent of top 16 memory locations:\n");
  printf("Address   Content\n");

  printMyBlock(q,16);
}

void printMyBlock(char *p,int mB)
{
  for(int i = 0 ; i < mB ; i++)
  {
	printf(" %p       0x%02x\n",p-i,*(p-i));
  }
}

