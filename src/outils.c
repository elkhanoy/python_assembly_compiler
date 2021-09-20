#include "../include/pyas/all.h"

static int re_match_zero_or_more ( char c, char * regexp , char *source , char ** end ) {
  char *t = source ;
  while ( '\0' != *t && ( *t == c || '.'== c ) ) {
    t ++;
  }
  do {
    if ( re_match ( regexp , t, end ) ) {
      return 1;
    }
  } while ( t-- > source ) ;
  return 0;
}

static int re_match_one_or_more ( char c, char *regexp, char *source, char **end){
  if (*source==c){
    return re_match_zero_or_more(c,regexp,source,end);
  }
  return 0;
}

static int re_match_zero_one_or_one ( char c, char *regexp, char *source, char **end){
  if (*source==c){
    if (re_match_one_or_more(c,regexp,source+1,end)!=0){
      return 0;
    }
    else {return re_match_zero_or_more(c,regexp,source+1,end);
    }
  }
}

int re_match ( char * regexp , char * source , char ** end ) {
  if ( '\0' == regexp [ 0 ] ) {
    * end = source ;
    return 1;
  }

  if ( '*' == regexp [ 1 ] ) {
    return re_match_zero_or_more ( regexp [ 0 ] , regexp +2 , source ,end );
  }

  if('+'==regexp[1]){
    return re_match_one_or_more(regexp[0], regexp+2, source, end);
  }

  if('?'==regexp[1]){
    return re_match_zero_one_or_one(regexp[0], regexp+2, source, end);
  }

  if ( '\0' != * source && ( '.' == regexp [ 0 ] || * source == regexp [ 0 ] ) ) {
    return re_match ( regexp +1 , source +1 , end );
  }
  return 0;
}
