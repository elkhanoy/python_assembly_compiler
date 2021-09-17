#include <pyas/all.h>

void main(){
  queue_t * dictionnaire=NULL;
  if(!lire_fichier_conf(dictionnaire)){
    printf("Erreur");
    exit(1);
  }
  queue_print(dictionnaire);
  queue_delete(dictionnaire);
}
