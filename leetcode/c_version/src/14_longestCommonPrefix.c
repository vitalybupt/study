#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>


int commonPrefixTwoString(char* str1, char* str2) {
    int str1Length = strlen(str1);
    int str2Length = strlen(str2);
    if(str1Length == 0 || str2Length == 0) return 0;

    int matchPace = sizeof(long);
    int length = str1Length < str2Length ? str1Length : str2Length;
    int retLength = 0;

    if(length >= matchPace)
	for(int i = 0; i < length; i+=matchPace) {
	    long *tmp1 = (long*)(str1+i);
	    long *tmp2 = (long*)(str2+i);
	    
	    if((*tmp1)^(*tmp2) != 0) {
		break;
	    } else {
		retLength += matchPace;
	    }
	}

    if(retLength < length){
	for(int i = retLength; i < length; i++) {
	    if(str1[i] == str2[i]) {
		retLength++;
	    } else {
		break;
	    }
	}
    }
    str2[retLength] = '\0';
    return retLength;
}

char * longestCommonPrefix(char ** strs, int strsSize){
    if(strsSize == 0) return "";
    else if(strsSize == 1) return strs[0];
    
    for(int i = 0; i < strsSize - 1; i++) {
	int commonPrefixLength = commonPrefixTwoString(strs[i], strs[i+1]);
	if(commonPrefixLength == 0) return "";
    }
    return strs[strsSize-1];
}

int main() {
  char input[2][16] ={"c", "c"};
  char *raw[2] = {input[0], input[1]};
  char* ret = longestCommonPrefix(raw, 2);
  printf("%s\r\n", ret);
  return 0;
}
