#include <pyas/all.h>

int main(){
  queue_t lexeme=NULL;
  //dictionnaire=calloc(1,sizeof(*dictionnaire));
  //dictionnaire->next=dictionnaire;
  lexeme=lecture_fichier_conf(lexeme, "assembleur.conf");
  if(!lexeme){
    printf("Erreur");
    exit(1);
  }
  lexeme=queue_to_list(lexeme);
  list_print(lexeme,print_lexeme_conf);
  list_delete(lexeme,lexeme_conf_delete);
}
