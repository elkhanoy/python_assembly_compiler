#include <pyas/all.h>

void main(){
  queue_t dictionnaire=NULL;
  dictionnaire=calloc(1,sizeof(*dictionnaire));
  printf("\n%s\n",dictionnaire->content->nom);
  if(!lire_fichier_conf(dictionnaire)){
    printf("Erreur");
    exit(1);
  }
  printf("\n%s\n",dictionnaire->content->nom);
  queue_print(dictionnaire);
  queue_delete(dictionnaire);
}
