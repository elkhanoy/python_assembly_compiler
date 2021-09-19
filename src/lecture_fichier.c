#include <pyas/all.h>

int lire_fichier_conf(queue_t * dictionnaire){
  FILE* fichier = NULL;
  fichier = fopen("/home/yassine/Documents/projetinfo/proj1/elamrans_elkhanoy_jouidij/tests/assembleur.conf", "rt");
  if(NULL==fichier){
    perror("fopen");
    return 0;
  }
  /*if(fichier!="\0"){
    fscanf(fichier,"%s %s",dictionnaire->content->nom,dictionnaire->content->exp_str);
    dictionnaire->content->exp_file=NULL;*/
  // element->exp_file=NULL;
  while(!feof(fichier)){
    struct dico_t * element;
    element=calloc(1,sizeof(*element));
    fscanf(fichier,"%s %s",element->nom,element->exp_str);
    dictionnaire=enqueue(dictionnaire,element);
    printf("loooooooooooool %s",((*dictionnaire)->content)->nom);
  }
  fclose(fichier);
  printf("ici ca marche");
  return 1;
}
