#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool isPalindrome(char * s){
    int head = 0;
    int tail = strlen(s) -1;   
    while(head<tail) {
      if(!isalnum(s[head])) head++;
      else if(!isalnum(s[tail])) tail--;
      else if(tolower(s[head++]) != tolower(s[tail--]))
        return false;
    }
    return true;
}

int main() {
  char input[] = "0P";
  printf("%s palindrome\r\n", isPalindrome(input) ? "is" : "not") ;
  return 0;
}
