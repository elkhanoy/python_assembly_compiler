#include <pyas/all.h>

int main(int argc,char*argv[]) //Les noms des fichiers source et configuration seront placés en paramètre (config en argument 1 et source en 2)
{
  if(argc<4) //Le nombre de paramètres ajoutés doit être de 2
  {
    printf("Entrer 3 paramètres\n");
    exit(EXIT_FAILURE);
  }
  // 1 - Récupération des noms des fichiers placés en paramètre dans le terminal
  queue_t queue_lexemes_identifies=NULL;
  char config_name[1024]; //Nom du fichier de configuration
  char source_name[1024]; //Nom du fichier source
  strcpy(config_name,argv[1]); //Copie du nom du fichier de configuration pris en paramètre lors de la compilation, dans le tableau
  strcpy(source_name,argv[2]); //Copie du nom du fichier source pris en paramètre lors de la compilation, dans le tableau
  if((queue_lexemes_identifies=lex(config_name,source_name,queue_lexemes_identifies))){
    queue_lexemes_identifies=queue_to_list(queue_lexemes_identifies);
    pyobj_t code_a=construction_pyobj(&queue_lexemes_identifies);
    pyasm(queue_lexemes_identifies,code_a);
    FILE * ptr=fopen(argv[3],"w");
    pyobj_write( ptr, code_a);
    fclose(ptr);
    return 0;

  }
  else{
    queue_lexemes_identifies=queue_to_list(queue_lexemes_identifies);
    list_delete(queue_lexemes_identifies,lexem_delete);
    return 1;
  }
  // list_t *lexems=calloc(1,sizeof(*lexems));
  // *lexems=queue_lexemes_identifies;
  //
  //   codeblock code=construction_codeblock(lexems);
  //   int a=(code->binary.content.consts)->py.list.size;
  //   printf("la taille est %d\n",a);
  //   return 0;

  //}
  // printf("Not ok");
  // return 0;
}
