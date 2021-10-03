#include <pyas/all.h>

int re_match_zero_or_more ( queue_t queue_regexp, char*source , char ** end )
{
    *end=source;
    while(('\0' != **end) && (((char_group_t*)queue_regexp->content)->group[(int)**end]==1))
    {
      (*end)++;
    }
    do
    {
      if(re_match(queue_regexp,*end,end))
      return 1;
    } while(*end-- > source);
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int re_match_zero_one_or_one(queue_t queue_regexp, char*source, char**end)
{
    *end=source;
    if(!(((char_group_t*)queue_regexp->content)->group[(int)*(*end)]))
    {
      return re_match(queue_regexp->next,source+1,end);
    }
    else
    {
      if(((char_group_t*)queue_regexp->content)->group[(int)*(*end+1)])
        {return 0;}
      else
        {return re_match(queue_regexp->next,source+1,end);}
    }
}
///////////////////////////////////////////////////////////////////////////////
int re_match_one_or_more ( queue_t exp_file, char * source , char ** end ){
 if(((char_group_t*)(exp_file->content))->group[(int)*source]){
   *end=source;
   while(((char_group_t*)(exp_file->content))->group[(int)**end]){
     end++;
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
 if(((char_group_t*)(queue_regexp->content))->occurence==ONE_OR_MORE)
 {
   return re_match_one_or_more(queue_regexp,source,end);
 }
 if(((char_group_t*)(queue_regexp->content))->occurence==ZERO_OR_MORE)
 {
   return re_match_zero_or_more(queue_regexp,source,end);
 }
 if(((char_group_t*)(queue_regexp->content))->occurence==EXACTLY_ONE)
 {
   return re_match_zero_one_or_one(queue_regexp,source,end);
 }
 if(('\0'!=*source) && (((char_group_t*)(queue_regexp->content))->group[(int)*source]))
 {
   return re_match(queue_regexp->next,source+1,end);
 }
 return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
