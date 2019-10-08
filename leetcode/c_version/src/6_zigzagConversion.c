#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

char * convert(char * s, int numRows){
    char **stock = malloc(sizeof(char*)*numRows);
    char *ret = malloc(sizeof(char)*strlen(s));
    for(int i= 0; i < numRows; i++) {
	char* tmp = malloc(sizeof(char)*strlen(s));
	memset(tmp, 0, strlen(s));
	stock[i] = (char*)tmp;
    }
    int row = 0; int direction = 1;
    for(int i = 0; i < strlen(s); i++) {
	int pos = strlen(stock[row]);
	stock[row][pos] = s[i];
	if(row == 0) direction = 1;
	else if(row == (numRows - 1)) direction = -1;
	row += direction;
    }
    int pos = 0;
    for(int i = 0; i < numRows; i++) {
	for(int j = 0; j < strlen(stock[i]); j++) {
	    ret[pos] = stock[i][j];
	    pos++;
	}
	free(stock[i]);
    }
    free(stock);
    return ret;
}

int main() {
    char* ret = convert("PAYPALISHIRING", 3);
    printf("%s\r\n", ret);
    free(ret);
    return 0;
}
