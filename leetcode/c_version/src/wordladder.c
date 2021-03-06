#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct pair{
  char ** list;
  int size;
} pair, *ppair;

void push_word (ppair node, char* word) {
  char *tmp = malloc(strlen(word)+1);
  memset(tmp,0, strlen(word)+1);
  memcpy(tmp, word, strlen(word));
  
  if(node->list == NULL) {
    node->list = malloc(sizeof(char*));
    node->list[0] = tmp;
    node->size = 1;
  } else {
    node->list = realloc(node->list, sizeof(char*)*(++node->size));
    node->list[node->size-1] = tmp;
  }
  memset(word, 0, strlen(word));
}

bool word_distance_one(char *s1, char*s2) {
  int distance = 0; int len = strlen(s1);
  for(int i = 0; i < len; i++) {
    if(s1[i] != s2[i])
      ++distance;
  }
  return distance == 1;
}

bool in_wordlist(char* word, char **wordList, int wordListSize) {
  int length = strlen(word);
  for(int i = 0; i < wordListSize; ++i) {
    if(strncmp(word, wordList[i], length) == 0) {
      return true;
    }
  }
  return false;
}

void free_pair(ppair node) {
  for(int i = 0; i < node->size; ++i) {
    free(node->list[i]);
  }
  return;
}
int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize){
  ppair head = malloc(sizeof(pair)); memset(head, 0, sizeof(pair)); push_word(head, beginWord);
  ppair tail = malloc(sizeof(pair)); memset(tail, 0, sizeof(pair)); 
  for(int i = 0; i < wordListSize; ++i) {
    if(strncmp(endWord, wordList[i], strlen(endWord)) == 0) {
      push_word(tail, wordList[i]);
    }
  }
  if(tail->size == 0) return 0;
  int length = 1;

  while(head->size != 0 && tail->size !=0) {
    /* swap for optimization */ 
    if(head->size > tail->size) {
      ppair tmp = head;
      head = tail;
      tail = tmp;
    }
    ppair intermediate = malloc(sizeof(pair)); memset(intermediate, 0, sizeof(pair));
    for(int i = 0; i < head->size; ++i) {
      char *word = head->list[i];
      for(int j = 0; j < tail->size; j++) {
	if(word_distance_one(word, tail->list[j]))
	  return ++length;
      }
      for(int j = 0; j < wordListSize; j++) {
	if(strlen(wordList[j]) != 0 && word_distance_one(head->list[i], wordList[j])) {
	  push_word(intermediate, wordList[j]);
	}
      }
    }
    length += 1;
    free_pair(head);
    head = intermediate;
  }
  
  return 0;
}

int main() {
  char begin[] = "hit"; char end[] = "cog";
  char dict[5][4] = {"hot", "dot", "dog", "lot", "log"};
  char* rawdict[5]= {dict[0], dict[1], dict[2], dict[3], dict[4]};
  int length = ladderLength(begin, end, rawdict, 5);
}
