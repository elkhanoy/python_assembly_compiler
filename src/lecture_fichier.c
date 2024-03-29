#include <pyas/all.h>

int print_lexeme_conf(void * _lexeme_config){
  struct lexeme_config * lex_conf = _lexeme_config;
  list_print(lex_conf->queue_regexp,regexp_print);
  return printf( "\n%s %s\n",
		 lex_conf->regexp_name,
		 lex_conf->regexp_str );
}

int lexeme_conf_delete(void * _lexeme_config){
  struct lexeme_config * lex_conf = _lexeme_config;
  list_delete(lex_conf->queue_regexp,char_group_delete);
  free(lex_conf);
  return 1;
}

int regexp_print (void * _regexp_q){
  char_group_t * regexp = _regexp_q;
  return printf("\t %d",((regexp->group)[(int)' ']));
}

int char_group_delete(void * _char_group){
  char_group_t * chargrp = _char_group;
  free(chargrp);
  return 1;
}

queue_t lecture_fichier_conf(queue_t lexemes_q, char * config)
{
  char buffer[256];
  char comment_test[256];
  int i=0;

  // 1 - Ouverture du fichier de configuration
  FILE* fichier = NULL;
  fichier = fopen(config, "rt");
  if(NULL==fichier)
  {
    perror("fopen");
    return NULL;
  }

// 2 - Lecture du fichier de configuration et complétion des champs décrivant les lexemes (le nom, l'expression régulière en caractères, l'expression régulière en queue)
  while(!feof(fichier)) // Tant que ce n'est pas la fin du fichier source...
  {
    if(fscanf(fichier,"%s",comment_test)!=EOF)
      {
        if(comment_test[0]!='#' || comment_test[0]!='\n' ) // Si la ligne n'est pas un commentaire ou une ligne vide...
        {
          struct lexeme_config * lexeme_config; // On crée un type lexeme_config
          lexeme_config=calloc(1,sizeof(*lexeme_config)); // On lui alloue de la mémoire
          strcpy(lexeme_config->regexp_name,comment_test); // Et on stock son nom
          fgets(buffer,100,fichier); // ainsi que son expression régulière
          while(buffer[i]==' ' || buffer[i]=='\t'){ // On supprime les espaces.
            i++;
          }
          buffer[strcspn(buffer, "\n")] = 0;
          strcpy(lexeme_config->regexp_str,(buffer+i));
          if(0==(lexeme_config->queue_regexp=re_read(lexeme_config->regexp_str,lexeme_config->queue_regexp))){
            free(lexeme_config);
            list_delete(lexemes_q,lexeme_conf_delete);
            return lexemes_q;
          } // On "transforme" l'expression reg. (qui est en type char*) en type char group.
          //printf("\n %s",lexeme_config->regexp_str);
          //printf("\n %p \t",lexeme_config->queue_regexp);
          lexeme_config->queue_regexp=queue_to_list(lexeme_config->queue_regexp);
          //list_print(lexeme_config->queue_regexp,regexp_print);
          lexemes_q=enqueue(lexemes_q,lexeme_config); // On insère ce lexème dans la file.
          i=0;
        }
        else // Sinon on stock cette ligne dans une variable tampon qu'on n'utilisera pas.
        {
          fgets(buffer,256,fichier);
        }
    }
  }
  fclose(fichier);
  return lexemes_q;
}
