#include <pyas/all.h>

int re_match_zero_or_more ( queue_t queue_regexp, char*source , char ** end )
{
  char * t=source;

  if(((char_group_t*)queue_regexp->content)->group[(int)*t]==1)
    {      while(('\0' != *t) && (((char_group_t*)queue_regexp->content)->group[(int)*t]==1))
        {
          t++;
        }
        /*return re_match(queue_regexp->next,*end,end);
      }
      */
        /*do{
          if(re_match(queue_regexp,t,end)){
            return 1;
          }
        } while(t-- > source); */
        return re_match(queue_regexp->next,t,end);
      }
      return re_match(queue_regexp->next,t++,end);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int re_match_zero_one_or_one(queue_t queue_regexp, char*source, char**end)
{
    *end=source;
    if(!(((char_group_t*)queue_regexp->content)->group[(int)*(*end)]))
    {
      return re_match(queue_regexp->next,source,end);
    }
    else
    {
      if(((char_group_t*)queue_regexp->content)->group[(int)*(*end+1)])
        {return 0;}
      else
        {
          if(!re_match(queue_regexp->next,source+1,end)){
            return re_match(queue_regexp->next,source,end);
          }
        }
    }
}
///////////////////////////////////////////////////////////////////////////////
int re_match_one_or_more ( queue_t exp_file, char * source , char ** end ){
 if(((char_group_t*)(exp_file->content))->group[(int)*source]){
   *end=source;
   while(((char_group_t*)(exp_file->content))->group[(int)**end]){
     (*end)++;
   }
   return re_match(exp_file->next,*end,end);
 }
 return 0;
}

////////////////////////////////////////////////////////////////////////////////
int re_match(queue_t queue_regexp, char*source, char **end)
{
 if (queue_regexp==NULL)
 {
   *end=source;
   return 1;
 }
 if(*source=='\0')
 {
   while(((char_group_t*)(queue_regexp->content))->occurence==ONE_OR_ZERO || ((char_group_t*)(queue_regexp->content))->occurence==ZERO_OR_MORE){
     if(!(queue_regexp->next)){
       *end=source;
       return 1;
     }
     queue_regexp=queue_regexp->next;
   }
   *end=source;
   return 0;
 }
 //if(*source=='\n'){
//   return 0;
 //}
 if(((char_group_t*)(queue_regexp->content))->occurence==ONE_OR_MORE)
 {
   return re_match_one_or_more(queue_regexp,source,end);
 }
 if(((char_group_t*)(queue_regexp->content))->occurence==ZERO_OR_MORE)
 {
   return re_match_zero_or_more(queue_regexp,source,end);
 }
 if(((char_group_t*)(queue_regexp->content))->occurence==ONE_OR_ZERO)
 {
   return re_match_zero_one_or_one(queue_regexp,source,end);
 }
 if(('\0'!=*source) && (((char_group_t*)(queue_regexp->content))->group[(int)*source]))
 {
   *end=source;
   return re_match(queue_regexp->next,source+1,end);
 }
 return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
