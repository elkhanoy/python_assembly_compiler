#include <pyas/all.h>


static int re_match_zero_or_more ( list_t exp_file,list_t exp_file2, char source , char * end ) {
  char *t = source ;
  while ( '\0' != *t && ( (()(exp_file->content))-> group[*t] || (exp_file->content)->group[.] )) {
    t ++;
  }
  do {
    if ( re_match ( exp_file2 , t, end ) ) {
      return 1;
    }
  } while ( t-- > source ) ;
  return 0;
}

static int re_match_one_or_more ( list_t exp_file,list_t exp_file2, char source , char * end ){
  if ((exp_file->content)-> group[*source]){
    return re_match_zero_or_more(exp_file,exp_file2,source,end);
  }
  return 0;
}

static int re_match_zero_one_or_one ( list_t exp_file,list_t exp_file2, char source , char * end ){
  if ((exp_file->content)-> group[*source]){
    if (re_match_one_or_more(exp_file,exp_file2,source+1,end)!=0){
      return 0;
    }
    else {return re_match_zero_or_more(exp_file,exp_file2,source+1,end);
    }
  }
}

int re_match (list_t exp_file , char * source , char * end ) {
  if ( !(exp_file->next) ) {
    * end = source ;
    return 1;
  }

  if (((exp_file->next)->content->)group[*]) {
    return re_match_zero_or_more ( exp_file ,(exp_file->next)->next, source ,end );
  }

  if (((exp_file->next)->content->)group[+]) {
    return re_match_zero_or_more ( exp_file ,(exp_file->next)->next, source ,end );
  }

  if (((exp_file->next)->content->)group[?]) {
    return re_match_zero_or_more ( exp_file ,(exp_file->next)->next, source ,end );
  }

  if ( '\0' != * source && ( (exp_file->content)->group[.] || (exp_file->content)->group[*source] ) ) {
    exp_file=exp_file->next;
    return re_match ( exp_file, source +1 , end );
  }
  return 0;
}
