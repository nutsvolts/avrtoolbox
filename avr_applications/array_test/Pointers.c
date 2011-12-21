// Pointers.c Joe Pardue 12/12/11

#include <stdio.h>
#include "c:\avrtoolbox\libavr\source\driver\usart\usart.h" 

void printMyBlock(char *p,int mB);

int main()
{
  // Initialize usart for printf
  usart0_init_baud(57600);

/*  // Declare a variable
  unsigned char a = 0x33;
  // Declare a pointer
  unsigned char *z;

  
  // Show declarations
  printf("Declarations:\n"
  "unsigned char a = 0x33;\n"
  "unsigned char *z;\n\n");

  // Show the z pointer address, contents, and what
  // it points to before being initialized.
  printf("'z' initial state:\n");
  printf("Address of z: &z = 0x%p\n",&z);
  printf("Contents at address of z: "
  "(unsigned int)z = 0x%x\n",(unsigned int)z);
  printf("Contents pointed to by z: *z = 0x%x\n\n",*z);

  // Show the address of the variable a
  printf("Address of a: &a = 0x%p\n\n",&a);

  // Set the z pointer to point to the a variable
  z = &a;

  // Show the z pointer address, contents, and what 
  // it points to after it is intialized to point to a
  printf("'z' state after setting z = &a:\n");
  printf("Address of z: &z = 0x%p\n",&z);
  printf("Contents at address of z: "
  "(unsigned int)z = 0x%x\n",(unsigned int)z);
  printf("Contents pointed to by z: *z = 0x%x\n\n",*z);
*/
  printf("Memory:\n");
  
  volatile char a = 0x11;
  volatile char b = 0x22;
  volatile char c = 0x33;
  volatile char *p;
  volatile char *q;

  q = (volatile char *)0x8ff;
  p = &a;

  printf("Pointer p address: %p\n",&p);
  
  for(int i = 0 ; i < 25 ; i++)
  {
	//printf("Content of memory location %p is: %x\n",p-i,*(p-i));
	printf("Content of memory location %p is: 0x%02x\n",q-i,*(q-i));

  }
/**/
/*const char* p = (const char *)0x80ef;
const char* pEnd = p + 16;

while ( p < pEnd )
{
  printf( "Address: %p Content: %x\n",p, *p );
  ++p;
}
puts("");*/
  // Declare a block of 26 chars
/*  char myBlock[26];
  // Declare a pointer to char
  char *p;

  // Set it to point to the first element of myBlock
  p = &myBlock[0];

  for(int i = 0; i < 26 ; i++)
  {
	*(p+i) = 'a' + i;
  }

  // Print the block
  printMyBlock(p,26);
*/

}

void printMyBlock(char *p,int mB)
{
	for(int i = 0 ; i < mB ; i++)
	{
		printf("myBlock #%d = %c\n",i,*(p+i));
	}
}
