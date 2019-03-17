/* Input: "   -42" */
/* Output: -42 */

/* Input: "4193 with words" */
/* Output: 4193 */

/* Input: "words and 987" */
/* Output: 0 */

/* Input: "-91283472332" */
/* Output: -2147483648 */


#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define INT_MAX 0x7FFFFFFF
#define INT_MIN 0x80000000

int myAtoi(char* str) {
  int ret = 0;
  double r_ret = 0;
  char* p = NULL;
  int negative = 0;
  
  /* if(len == 0) return 0; */
  
  // skip space
  for(p=str; p!='\0'; ++p)
    {
      if(*p != ' ')
	break;
    }

  if( *p == '\0' ) return 0;

  if( *p == '+') {
    ++p;
  } else if( *p == '-') {
    negative = 1;
    ++p;
  } else if( *p > 57 || *p < 48)
    return 0;

  // skip the tail non digit
  unsigned int len = strlen(p);
  unsigned int i = 0;
  for(i=0; i<len; ++i) {
    if(p[i] > 57 || p[i] < 48) {
      break;
    }
  }
  len = i;

  for(i=0; i<len; ++i) {
    r_ret = r_ret*10 + p[i] - 48;
    if( !negative && r_ret > INT_MAX)
      return INT_MAX;
    else if(negative && r_ret > INT_MIN) {
      return -INT_MIN;
    }
  }

  if( negative )
    ret = -r_ret;
  else
    ret = r_ret;

  return ret;
}

void main() {
  int val = 0;
  val = myAtoi("a47");
  printf("%d\r\n", val);
  val = myAtoi("");
  printf("%d\r\n", val);
  val = myAtoi("47");
  printf("%d\r\n", val);
  val = myAtoi("-47");
  printf("%d\r\n", val);
  val = myAtoi("-47with");
  printf("%d\r\n", val);
  val = myAtoi("-91283472332");
  printf("%d\r\n", val);
  return;
}
