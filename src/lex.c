#include <pyas/all.h>

  queue_t lex(char * config_name, char * source_name, queue_t queue_lexemes_identifies){
    // 1 - Déclaration des variables utilisées pour les fonctions définies dans les fichiers .c
      char ** end=NULL;
      end=calloc(1,sizeof(*end));
      *end=NULL;
      char * ligne_source;
      char * ligne_source_ori;
      ligne_source=calloc(20000,sizeof(*ligne_source));
      ligne_source_ori=ligne_source;
      queue_t queue_lexemes=NULL; //Queue de lexemes créée par la lecture du fichier de configuration
      char * lexem_value;
    // 2 - Création de la liste des lexemes

      queue_lexemes=lecture_fichier_conf(queue_lexemes, config_name); //Appel de la fonction re_read dans la fonction lecture_fichier_conf
      if(NULL==queue_lexemes){
        free(end);
        free(ligne_source);
        return queue_lexemes;
      }
      list_t list_lexemes=NULL;
      lexem_t lexem_a_ajouter=NULL;
      list_lexemes=queue_to_list(queue_lexemes); // On converti la queue en liste.
      list_t debut_list_lexemes=list_lexemes;
      if(!list_lexemes)
      {
        printf("Erreur");
        exit(1);
      }

     // 4 - Ouverture du fichier source dont le nom est placé en paramètre dans le terminal
      FILE* source_f=fopen(source_name, "rt");
      if(NULL==source_f)
      {
        perror("fopen");
        return 0;
      }

      // 5 - Copie du fichier source dans un tableau alloué de char
      // 5.1 - Détermination de la longueur du fichier source*

      //################## DEBUT VERSION YASSINE ###############################
      // Initialisation de variables servant a extraire le Nº de ligne et colonne.
      int ligne=0;
      int colonne=0;
      int sortir=0;
      while(!feof(source_f)){
        ligne++; // On incrémente le compteur ligne au fur et à mesure qu'on lit une nouvelle ligne.
        colonne=0; // On remet le compteur colonne à zéro.
        fgets(ligne_source,20000,source_f); // On lit une ligne de source_f et on la stock dans la variable ligne_source
          while(*ligne_source!='\0'){ // Tant qu'on est pas a la fin de la ligne...
            //On test ensuite si on est pas arrivé à la fin des lexemes ou si on a trouvé un lexeme correspondant.
            /*
            while(*ligne_source==' '){
              queue_lexemes_identifies=enqueue(queue_lexemes_identifies,lexem_new("blank"," ",ligne,colonne));
              colonne++;
              ligne_source++;
            }
            */
            while(list_lexemes && !sortir){
                if(!re_match(((struct lexeme_config*)(list_lexemes->content))->queue_regexp,ligne_source,end)){
                  list_lexemes=list_lexemes->next;
                }
                else{sortir=1;}
            }
            // Si on est arrivé à la fin de la liste des lexemes c'est qu'on a pas trouvé de lexème et on informe l'utilisateur.
            if(!list_lexemes){
              printf("\nErreur, lexeme non identifié ligne %d colonne %d\n",ligne,colonne);
              fclose(source_f);
              free(end);
              free(ligne_source_ori);
              list_delete(list_lexemes,lexeme_conf_delete);
              return NULL;
            }
            // Sinon, on stock ce lexeme dans la liste des lexemes identifiés.
            lexem_value=copie_n_caracteres(ligne_source,(*end-ligne_source));
            lexem_a_ajouter=lexem_new(((struct lexeme_config*)(list_lexemes->content))->regexp_name,lexem_value,ligne,colonne);
            queue_lexemes_identifies=enqueue(queue_lexemes_identifies,lexem_a_ajouter);
            free(lexem_value);
            colonne+=(*end-ligne_source);
            ligne_source = (*end);
            list_lexemes=debut_list_lexemes;
            /*
            while(*ligne_source==' '){
              queue_lexemes_identifies=enqueue(queue_lexemes_identifies,lexem_new("blank"," ",ligne,colonne));
              colonne++;
              ligne_source++;
            }
            */
            sortir=0;
          }
          ligne_source=ligne_source_ori;
        //queue_lexemes_identifies=enqueue(queue_lexemes_identifies,lexem_new("newline","\n",ligne,colonne));
      }
      fclose(source_f);
      free(ligne_source_ori);
      free(end);
      list_delete(list_lexemes,lexeme_conf_delete);
      return queue_lexemes_identifies;
    }

char * copie_n_caracteres(char * src, int n){
  if(*src=='\\' && *(src+1)=='n'){
    char * dst = calloc(4,sizeof(*dst));
    src="\\n";
    return dst;
  }
  char * dst = calloc(n+1,sizeof(*dst));
  int i;
  for(i=0;i<n;i++){
    *(dst+i)=*(src+i);
  }
  *(dst+i)='\0';
  return dst;
}
