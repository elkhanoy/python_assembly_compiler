
/**
 * @file queue.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  2 19:02:17 2021
 * @brief Queue.
 *
 * Queue.
 */

#include <pyas/all.h>

queue_t queue_new( void ) {
  return NULL;
}

int     queue_empty( queue_t q ) {
  return queue_new() == q;
}

/*queue_t enqueue( queue_t q, void* object ) {
  struct link_t *new = queue_new();
  if(NULL==(new=calloc(1,sizeof(*new)))){
    printf("Erreur a l'allocation dynamique");
    return NULL;
  }
  new->content=object;
  if(!q){
    new->next=new;
    return new;
  }
  new->next=q->next;
  q->next=new;
  return new;
}*/

queue_t enqueue( queue_t q, void* object ) {
  queue_t p=calloc(1,sizeof(*p)); //pour retenir l'adresse du premier maillon
  p->content=object;
  if(queue_empty(q))
    p->next=p;
  else{
      p->next=q->next;
      q->next=p;
  }
  return p;
}

queue_t queue_del_head(queue_t q) {
  if(!q){
    exit(1);
  }
  if(q==q->next){
    //free(q->content->exp_file);
    free(q->content);
    free(q);
    return NULL;
  }
  queue_t p=q->next;
  q->next=p->next;
  //free(p->content->exp_file);
  free(p->content);
  free(p);
  return q;
}

queue_t queue_delete(queue_t q) {
  if(!q){
    printf("Liste vide\n");
    return NULL;
  }
  queue_t p=q->next;
  while(p!=q){
    p=queue_del_head(p);
  }
  p=queue_del_head(p);
  return NULL;
}


list_t  queue_to_list( queue_t q ) {
  list_t l = list_new();
  l=q->next;
  q->next=NULL;
  return l;
}
