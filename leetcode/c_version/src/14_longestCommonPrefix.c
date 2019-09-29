#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>


int commonPrefixTwoString(char* str1, char* str2) {
    int length = strlen(str1) < strlen(str2) ? strlen(str1) : strlen(str2);
    int retLength = 0;
    if(length == 0) return 0;
    if(length <4) {
	for(int i = 0; i < 4; i++) {
	    if(str1[i] == str2[i]) {
		retLength++;
	    } else {
		str2[retLength] = '\0';
		return retLength;
	    }
	}
    }
    for(int i = 0; i < length; i+=4) {
	int *tmp1 = (int*)(str1+i);
	int *tmp2 = (int*)(str2+i);
	
	if((*tmp1)^(*tmp2) != 0) {
	    for(int j = i; j < i+4; j++) {
		if(str1[j] == str2[j]) {
		    retLength++;
		} else {
		    str2[retLength] = '\0';
		    return retLength;
		}
	    }
	} else {
	    retLength += 4;
	}
    }
    str2[retLength] = '\0';
    return retLength;
}

char * longestCommonPrefix(char ** strs, int strsSize){
    if(strsSize == 0) return "";
    for(int i = 0; i < strsSize - 1; i++) {
	int commonPrefixLength = commonPrefixTwoString(strs[i], strs[i+1]);
	if(commonPrefixLength == 0) return "";
    }
    return strs[strsSize-1];
}

int main() {
  char input[2][16] ={"a", "b"};
  char *raw[2] = {input[0], input[1]};
  char* ret = longestCommonPrefix(raw, 2);
  printf("%s\r\n", ret);
  return 0;
}
