#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

enum FSM_STATE {
    STATE_START,
    STATE_DIGIT,
    STATE_SIGN,
    STATE_BLANK,
    STATE_EXPONENT,
    STATE_ACCEPT1,
    STATE_SIGN_AFTER_EXPONENT,
    STATE_DOT,
    STATE_ACCEPT2,
    STATE_ACCEPT3,
    STATE_REJECT,
    STATE_NUMBER
};


typedef enum FSM_STATE (*State_Handler)(char symbol);

enum FSM_STATE handler_start(char symbol) {
    if(symbol <='9' && symbol >= '0') {
	return STATE_DIGIT;
    } else if(symbol == '+' || symbol == '-') {
	return STATE_SIGN;
    } else if(symbol == ' ') {
	return STATE_BLANK;
    } else if(symbol == '.') {
	return STATE_DOT;
    } else
	return STATE_REJECT;
}

enum FSM_STATE handler_digit(char symbol) {
    if(symbol <='9' && symbol >= '0') {
	return STATE_DIGIT;
    } else if(symbol == '.') {
	return STATE_ACCEPT2;
    } else if(symbol == 'e') {
	return STATE_EXPONENT;
    } else if(symbol == '.'){
	return STATE_ACCEPT3;
    }else
	return STATE_REJECT;
}

enum FSM_STATE handler_sign(char symbol) {
    if(symbol <='9' && symbol >= '0') {
	return STATE_DIGIT;
    } else
	return STATE_REJECT;
}

enum FSM_STATE handler_blank(char symbol) {
    if(symbol <='9' && symbol >= '0') {
	return STATE_DIGIT;
    } else if(symbol == '+' || symbol == '-') {
	return STATE_SIGN;
    } else if(symbol == ' ') {
	return STATE_BLANK;
    } else
	return STATE_REJECT;
}

enum FSM_STATE handler_exponent(char symbol) {
    if(symbol <='9' && symbol >= '0') {
	return STATE_ACCEPT1;
    } else if(symbol == '+' || symbol == '-') {
	return STATE_SIGN_AFTER_EXPONENT;
    } else
	return STATE_REJECT;
}

enum FSM_STATE handler_accept1(char symbol) {
    if(symbol <='9' && symbol >= '0') {
	return STATE_ACCEPT1;
    } else
	return STATE_REJECT;
}

enum FSM_STATE handler_sign_after_exponent(char symbol) {
    if(symbol <='9' && symbol >= '0') {
	return STATE_ACCEPT1;
    } else
	return STATE_REJECT;
}

enum FSM_STATE handler_dot(char symbol) {
    if(symbol <='9' && symbol >= '0') {
	return STATE_ACCEPT2;
    } else
	return STATE_REJECT;
}

enum FSM_STATE handler_accept2(char symbol) {
    if(symbol <='9' && symbol >= '0') {
	return STATE_ACCEPT2;
    } else if(symbol == 'e') {
	return STATE_EXPONENT;
    }
    else
	return STATE_REJECT;
}

enum FSM_STATE handler_accept3(char symbol) {
    if(symbol == ' ') {
	return STATE_ACCEPT3;
    }
    else
	return STATE_REJECT;
}

State_Handler FSM[10] = { handler_start, handler_digit, handler_sign, handler_blank, handler_exponent, handler_accept1, handler_sign_after_exponent, handler_dot, handler_accept2, handler_accept3 };

bool isNumber(char * s){
    enum FSM_STATE current_state = STATE_START;
    int len = strlen(s);
    if(len == 0) return false;
    for(int i = 0; i < len; i++) {
	printf("%d\r\n", current_state);
	enum FSM_STATE next_state = FSM[current_state](s[i]);
	current_state = next_state;
	if(current_state == STATE_REJECT) break;
    }
    if(current_state == STATE_DIGIT || current_state == STATE_ACCEPT1 || current_state == STATE_ACCEPT2 || current_state == STATE_ACCEPT3 ) return true;
    else return false;
}

int main() {
    bool ret = isNumber("4");
    printf("%s number\r\n", ret ? "is":"not");
    return 0;
}
