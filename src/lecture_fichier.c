#include <pyas/all.h>

queue_t lire_fichier_conf(queue_t dictionnaire, char * config){
  char buffer[256];
  FILE* fichier = NULL;
  fichier = fopen(config, "rt");
  if(NULL==fichier){
    perror("fopen");
    return NULL;
  }
  while(!feof(fichier)){
    struct dico_t * element;
    element=calloc(1,sizeof(*element));
    fscanf(fichier,"%s",element->nom);
    if((element->nom)[0]!='#'){
      fscanf(fichier,"%s",element->exp_str);
      element->exp_file=split_regexp(element->exp_str,element->exp_file);
      dictionnaire=enqueue(dictionnaire,element);
    }
    else{
      fgets(buffer,256,fichier);
    }
  }
  fclose(fichier);
  return dictionnaire;
}
