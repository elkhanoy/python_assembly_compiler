
#include "../include/pyas/lecture_fichier.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int lire_fichier_conf(link_t * dictionnaire){
  FILE* fichier = NULL;
  if(NULL==(fichier = fopen("assembleur.conf", "rt"))){
    printf("Erreur à l'ouverture du fichier assembleur.conf");
    return 0;
  }
  if(fichier!="\0"){
    fscanf(fichier,"%s %s",dictionnaire->content->nom,dictionnaire->content->exp_str);
    dictionnaire->content->exp_file=NULL;
  }
  while(fichier!="\0"){
    fscanf(fichier,"%s %s",dicto->nom,dicto->exp_str);
  }
  fclose(fichier);
}
