#include <stdlib.h>
#include <string.h>

char* my_strcpy(char *dest, const char *src){
  int size = strlen(src);
  dest = (cahr*)realloc(dest,sizeof(cahr)*size);
  for(int i = 0; i < size; i++){
    dest[i] = src[i];
  }

  return dest;
}

char* my_strncpy(char *dest, const char *src, size_t n){
  dest  = realloc(dest, n);
  for(int i = 0; i < n; i++){
    dest[i] = src[i];
  }
  dest[n] = '\0';
  return dest;
}
