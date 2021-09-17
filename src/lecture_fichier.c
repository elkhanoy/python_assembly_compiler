#include <pyas/all.h>

int lire_fichier_conf(queue_t * dictionnaire){
  FILE* fichier = NULL;
  fichier = fopen("assembleur.conf", "r+");
  if(NULL==fichier){
    printf("Erreur à l'ouverture du fichier assembleur.conf");
    return 0;
  }
  /*if(fichier!="\0"){
    fscanf(fichier,"%s %s",dictionnaire->content->nom,dictionnaire->content->exp_str);
    dictionnaire->content->exp_file=NULL;*/
  struct dico_t * element;
  element->exp_file=NULL;
  while(getc(fichier)!=EOF){
    fscanf(fichier,"%s %s",element->nom,element->exp_str);
    *dictionnaire=enqueue(*dictionnaire,element);
  }
  fclose(fichier);
  return 1;
}
