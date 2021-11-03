#include <pyas/all.h>

list_txt_t enqueue( list_txt_t l) {
  list_txt_t p=calloc(1,sizeof(*p)); //pour retenir l'adresse du premier maillon
  if(queue_empty(q))
    p->next=p;
  else{
      p->next=l->next;
      l->next=p;
  }
  return p;
}

list_txt_t list_txt_new( void ) {
  return NULL;
}
