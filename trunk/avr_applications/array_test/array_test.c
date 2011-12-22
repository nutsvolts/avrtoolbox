#include <stdio.h>
#include "c:\avrtoolbox\libavr\source\driver\usart\usart.h" 

void load_array(char *);

// We do this so that it is easy for us
// to change the array size in one place
#define MAX_SIZE 10

int main()
{
  // Initialize usart for printf
  usart0_init_baud(57600);
  
  int i = 0;

  // Create an empty array
  char myArray[MAX_SIZE];

  // Initialize myArray to all 0
  for(i = 0; i < MAX_SIZE ; i++)
  {
    myArray[i] = 0;
  }

  // Show the data on the console before loading it
  printf("Before loading:\n");
  for(i = 0; i < MAX_SIZE ; i++)
  {
    printf("myArray[%d] = %d\n",i,myArray[i]);
  }

  // Send it to a function to load it with data
  load_array(myArray);

  // Show the data on the console after loading it
  printf("After loading:");
  for(i = 0; i < MAX_SIZE ; i++)
  {
    printf("myArray[%d] = %d\n",i,myArray[i]);
  }
}


void load_array(char *thisArray)
{
  int i = 0;

  for(i=0;i<MAX_SIZE;i++)
  {	
    // load it with ASCII codes for '0' to '9'
    thisArray[i] = i + 48; 
  }
}




