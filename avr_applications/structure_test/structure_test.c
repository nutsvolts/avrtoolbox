#include <stdio.h>

#include "c:\avrtoolbox\libavr\source\driver\usart\usart.h" 

struct date_t 
{
  int year ;
  int month;
  const char *month_text;
  int day;
  const char *day_text;
};

struct time_t 
{
  unsigned int hour;
  unsigned int minute;
  unsigned int second;
};

struct rtc_t 
{
	struct date_t myDate;
	struct time_t myTime;
};

void showDateTime(struct rtc_t *myRtc);

int main()
{
  // Initialize usart for printf
  usart0_init_baud(57600);

  // Declare an instance of rtc_t
  struct rtc_t myRtc;

  // Load it with data
  myRtc.myDate.year = 2012;
  myRtc.myDate.month = 5;
  myRtc.myDate.month_text = "May";   
  myRtc.myDate.day = 21;
  myRtc.myDate.day_text = "Monday";
  myRtc.myTime.hour = 9;
  myRtc.myTime.minute = 27;
  myRtc.myTime.second = 42;

// Send the address-of to show the date and time
  showDateTime(&myRtc);

}

// Take a pointer to an rtc_t structure and show the data
void showDateTime(struct rtc_t *myRtc)
{
  printf("Month: %s\nDay: %s\nYear: %d\n\n",
    myRtc->myDate.month_text,
    myRtc->myDate.day_text,
    myRtc->myDate.year);

  printf("%d\\%d\\%d\n\n",
    myRtc->myDate.month,
    myRtc->myDate.day,
    myRtc->myDate.year);

  printf("%d:%d:%d\n\n",
    myRtc->myTime.hour,
    myRtc->myTime.minute,
    myRtc->myTime.second);
}
