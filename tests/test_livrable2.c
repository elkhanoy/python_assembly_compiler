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
  if((queue_lexemes_identifies=lex(config_name,source_name,queue_lexemes_identifies))){
    queue_lexemes_identifies=queue_to_list(queue_lexemes_identifies);
    list_t * plist_lex_id=calloc(1,sizeof(*plist_lex_id));
    *plist_lex_id=queue_lexemes_identifies;
    if(-1==parse_pys(plist_lex_id)){
      printf("Le parse n'est pas bon");
      free(plist_lex_id);
      list_delete(queue_lexemes_identifies,lexem_delete);
      return 0;
    }
    printf("Le parse est bon");
    codeblock code=construction_codeblock(&queue_lexemes_identifies);
    int a=(code->binary.content.interned)->py.list.size;
    printf("%d\n",a );
    free((code->binary.content.interned)->py.list.value);
    free((code->binary.content.consts)->py.list.value);
    free((code->binary.content.names)->py.list.value);
    free(code);
    list_delete(queue_lexemes_identifies,lexem_delete);
    return 1;
  }
  else{
    queue_lexemes_identifies=queue_to_list(queue_lexemes_identifies);
    list_delete(queue_lexemes_identifies,lexem_delete);
    return 0;
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
