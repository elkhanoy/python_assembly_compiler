#include "../include/pyas/all.h"

int re_match(char *regexp, char *source, char **end){
  if('*'==regexp[1]){
    return re_match_zero_or_more(regexp[0], regexp+2, source, end);
  }
  if('\0'!=*source&&('.'==regexp[0] || *source == regexp[0])){
    return re_match(regexp+1, source+1, end);
  }
  return 0;
}

static int re_match_zero_or_more(char c, char *regexp, char *source, char **end){
  char *t = source;

  while('\0' != *t && (*t == c || '.' == c)){
    t++;
  }
  do {
    if (re_match(regexp, t, end)){
      return 1;
    }
  } while(t-- > source);
  return 0;
}

static int re_match_one_or_more(char c, char *regexp, char *source, char **end){

}

static int re_match_zero_one_or_one(char c, char *regexp, char *source, char **end){

}
