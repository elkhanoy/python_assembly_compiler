#include <pyas/all.h>

int main(){
  queue_t dictionnaire=NULL;
  //dictionnaire=calloc(1,sizeof(*dictionnaire));
  //dictionnaire->next=dictionnaire;
  dictionnaire=lire_fichier_conf(dictionnaire, "config/assembleur.conf");
  if(!dictionnaire){
    printf("Erreur");
    exit(1);
  }
  queue_print(dictionnaire);
  queue_delete(dictionnaire);
}
