#include <pyas/all.h>

int main(){
  char ** end=NULL;
  queue_t dictionnaire=NULL;
  queue_t list_lexem=NULL;
  //dictionnaire=calloc(1,sizeof(*dictionnaire));
  //dictionnaire->next=dictionnaire;
  dictionnaire=lire_fichier_conf(dictionnaire);
  if(!dictionnaire){
    printf("Erreur");
    exit(1);
  }
  /*
  ICI CONVERTIR LES EXPRESSIONS RÉGULIÈRES QUI SONT EN TYPE CHAR EN TYPE LIST
  CAD REMPLIR EXP_FILE À PARTIR DE EXP_STR
  */
  FILE* source = NULL;
  source = fopen("source.txt", "rt");
  if(NULL==source){
    perror("fopen");
    return NULL;
  }
  char word_source[256];
  queue_t debut_dictionnaire=dictionnaire;
  while(!feof(source)){ // Pour chaque "mot" du fichier source, on fait une comparaison avec les mots du dictionnaire
    fscanf(source,"%s",word_source);
    while(( !re_match(((struct dico_t*)(dictionnaire->content))->exp_file,word_source,end) ) && ( dictionnaire->next != debut_dictionnaire ) ){
        dictionnaire=dictionnaire->next;
    }
    // On part du principe que quelque soit le mot dans source, on trouve toujours un lexem associé, mais on ajoute un if par précaution.
    if(re_match(((struct dico_t*)(dictionnaire->content))->exp_file,word_source,end)){
      list_lexem=enqueue(list_lexem,lexem_new(((struct dico_t*)(dictionnaire->content))->nom,word_source,0,0)); // Pour l'instant on sait pas donner la ligne et colonne, donc on donne 0 0
    }
  }
  list_lexem=queue_to_list(list_lexem);
  list_print(list_lexem,lexem_print);
  list_delete(list_lexem,lexem_delete);
  fclose(source);
  queue_delete(dictionnaire);
}
