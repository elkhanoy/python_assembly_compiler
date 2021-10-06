#include <pyas/all.h>

int main(int argc,char*argv[]) //Les noms des fichiers source et configuration seront placés en paramètre (config en argument 1 et source en 2)
{
  if(argc<3) //Le nombre de paramètres ajoutés doit être de 2
  {
    printf("Entrer deux paramètres\n");
    exit(EXIT_FAILURE);
  }
  // 1 - Récupération des noms des fichiers placés en paramètre dans le terminal
  queue_t queue_lexemes_identifies=NULL;
  char config_name[80]; //Nom du fichier de configuration
  char source_name[80]; //Nom du fichier source
  strcpy(config_name,argv[1]); //Copie du nom du fichier de configuration pris en paramètre lors de la compilation, dans le tableau
  strcpy(source_name,argv[2]); //Copie du nom du fichier source pris en paramètre lors de la compilation, dans le tableau
  if(lex(config_name,source_name,queue_lexemes_identifies)){
    queue_lexemes_identifies=queue_to_list(queue_lexemes_identifies);
    list_print(queue_lexemes_identifies,lexem_print);
    list_delete(queue_lexemes_identifies,lexem_delete);
    return 1;
  }
  queue_lexemes_identifies=queue_to_list(queue_lexemes_identifies);
  list_delete(queue_lexemes_identifies,lexem_delete);
  return 0;
}
