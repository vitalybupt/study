int strStr(char * haystack, char * needle){
  int len1 = strlen(haystack);
  int len2 = strlen(needle);
  if(len2 == 0) return 0;
  for(int index = 0; index < len1-len2+1; ++index) {
    if(haystack[index] != needle[0]) continue;
    else if(strncmp(&haystack[index], needle, len2) != 0) continue;
    else return index;
  }
  return -1;
}
