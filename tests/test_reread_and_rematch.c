#include <pyas/all.h>

int main(int argc,char*argv[]) //La source et la regexp en chaine de caractères
{
  if(argc<3) //Le nombre de paramètres ajoutés doit être de 2
  {
    printf("Entrer deux paramètres\n");
    exit(EXIT_FAILURE);
  }
  char ** end=NULL;
  end=calloc(1,sizeof(*end));
  *end=NULL;
  char source[80]; //Nom du fichier de configuration
  char regexp[80]; //Nom du fichier source
  strcpy(source,argv[1]); //Copie du nom du fichier de configuration pris en paramètre lors de la compilation, dans le tableau
  strcpy(regexp,argv[2]); //Copie du nom du fichier source pris en paramètre lors de la compilation, dans le tableau
  queue_t regexp_queue=NULL;
  regexp_queue=re_read(regexp,regexp_queue);
  regexp_queue=queue_to_list(regexp_queue);
  if(re_match(regexp_queue,source,end)){
    printf("\n %s correspond avec %s\n",source,regexp);
  }
  else{
    printf("\n %s ne correspond pas avec %s\n",source,regexp);
  }
  free(end);
  list_delete(regexp_queue,lexeme_conf_delete);
  return 1;
}
