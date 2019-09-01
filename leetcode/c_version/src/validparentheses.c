
bool isValid(char * s) {
  int len = strlen(s);
  char* tmp = malloc(sizeof(char)*len);
  memcpy(tmp, s, len);

  char token[6] = {')', '}', ']', '(', '{', '['};
  for(int i = 0; i <len; ++i) {
    for(int pos = 0; pos < 3; ++pos) {    
      if(tmp[i] == token[pos]) {        
	for(int j = i-1; j >= 0; j--) {
	  if(tmp[j] == 0) continue;
	  else if(tmp[j] != token[pos+3]) {return false;}
	  else {
	    tmp[i] = 0;
	    tmp[j] = 0;
	    break;
	  }
	}
	break;
      }
    }
  }
  for(int i = 0; i< len; i++) 
    if(tmp[i] != 0) return false;
  return true;
}


