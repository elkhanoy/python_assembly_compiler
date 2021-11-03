#include <pyas/all.h>

list_txt_t enqueue( list_txt_t l) {
  list_txt_t p=calloc(1,sizeof(*p)); //pour retenir l'adresse du premier maillon
  if(list_txt_empty(l))
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

int     list_txt_empty( list_txt_t l ) {
  return queue_new() == l;
}
