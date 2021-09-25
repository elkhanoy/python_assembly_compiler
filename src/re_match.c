#include <pyas/all.h>


satatic int re_match_zero_or_more ( list_t exp_file,list_t exp_file2, char source , char * end ) {
  char *t = source ;
  while ( ('\0' != *t) && ( ((char_group_t *)(exp_file->content))-> group[*t] || ((char_group_t *)(exp_file->content))->group[46] )) {
    t ++;
  }
  do {
    if ( re_match ( exp_file2 , t, end ) ) {
      return 1;
    }
  } while ( t-- > source ) ;
  return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int re_match_one_or_more ( list_t exp_file,list_t exp_file2, char source , char * end ){
  if (((char_group_t *)(exp_file->content))-> group[source]){
    return re_match_zero_or_more(exp_file,exp_file2,source,end);
  }
  return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int re_match_zero_one_or_one ( list_t exp_file,list_t exp_file2, char source , char * end ){
  if (((char_group_t *)(exp_file->content))-> group[source]){
    if (re_match_one_or_more(exp_file,exp_file2,source+1,end)!=0){
      return 0;
    }
    else {return re_match_zero_or_more(exp_file,exp_file2,source+1,end);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int re_match (queue_t exp_file , char * source , char ** end ) {
  if ( !(exp_file->next) ) {
    * end = source ;
    return 1;
  }

  if (((char_group_t *)((exp_file->next)->content))->group[42]) {
    return re_match_zero_or_more ( exp_file ,(exp_file->next)->next, source ,end );
  }

  if (((char_group_t *)((exp_file->next)->content))->group[43]) {
    return re_match_zero_or_more ( exp_file ,(exp_file->next)->next, source ,end );
  }

  if (((char_group_t *)((exp_file->next)->content))->group[63]) {
    return re_match_zero_or_more ( exp_file ,(exp_file->next)->next, source ,end );
  }

  if ( '\0' != * source && ( ((char_group_t *)(exp_file->content))->group[46] || ((char_group_t *)(exp_file->content))->group[*source] ) ) {
    exp_file=exp_file->next;
    return re_match ( exp_file, source +1 , end );
  }
  return 0;
}

int re_match(queue_t regexp, char*source, char **end)
{
  if(NULL==regexp->next)
  {
    *end=source;
    return 1;
  }
  if('*'==(regexp->content)
  {
    return re_match_one_or_more(regexp[0],regexp+2,source,end);
  }
  if('?'==regexp[1])
  {
    return re_match_zero_or_more(regexp[0],regexp+2,source,end);
  }
  if('+'==regexp[1])
  {
    return re_match_zero_one_or_one(regexp[0],regexp+2,source,end);
  }
  if('\0'!=*source && ('.'==regexp||*source==regexp[]))
  {
    return re_match(regexp->next,source+1,end);
  }
  return 0;
}
