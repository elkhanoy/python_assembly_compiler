#include <pyas/all.h>

int main(int argc,char*argv[]) //Les noms des fichiers source et configuration seront placés en paramètre (config en argument 1 et source en 2)
{
  if(argc<3) //Le nombre de paramètres ajoutés doit être de 2
  {
    printf("Entrer deux paramètres\n");
    exit(EXIT_FAILURE);
  }

// 1 - Déclaration des variables utilisées pour les fonctions définies dans les fichiers .c
  char ** end=NULL;
  char * ligne_source;
  ligne_source=calloc(256,sizeof(*ligne_source));
  char lexem_value[256];
  queue_t queue_lexemes=NULL; //Queue de lexemes créée par la lecture du fichier de configuration
  queue_t queue_lexemes_identifies=NULL;
  char config_name[80]; //Nom du fichier de configuration
  char source_name[80]; //Nom du fichier source

// 2 - Récupération des noms des fichiers placés en paramètre dans le terminal
  strcpy(config_name,argv[1]); //Copie du nom du fichier de configuration pris en paramètre lors de la compilation, dans le tableau
  strcpy(source_name,argv[2]); //Copie du nom du fichier source pris en paramètre lors de la compilation, dans le tableau

// 3 - Création de la liste des lexemes
  queue_lexemes=lecture_fichier_conf(queue_lexemes, config_name); //Appel de la fonction re_read dans la fonction lecture_fichier_conf
  list_t list_lexemes=NULL;
  list_lexemes=queue_to_list(queue_lexemes); // On converti la queue en liste.
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
  // 5.1 - Détermination de la longueur du fichier source

  //################## DEBUT VERSION YASSINE ###############################
  // Initialisation de variables servant a extraire le Nº de ligne et colonne.
  int ligne=0;
  int colonne=0;
  while(feof(source_f)){
    ligne++; // On incrémente le compteur ligne au fur et à mesure qu'on lit une nouvelle ligne.
    colonne=0; // On remet le compteur colonne à zéro.
    fgets(ligne_source,256,source_f); // On lit une ligne de source_f et on la stock dans la variable ligne_source

      while(*ligne_source!='\0'){ // Tant qu'on est pas a la fin de la ligne...
        //On test ensuite si on est pas arrivé à la fin des lexemes ou si on a trouvé un lexeme correspondant.
        while(list_lexemes && !re_match(((struct lexeme_config*)(list_lexemes->content))->queue_regexp,ligne_source,end)){
            list_lexemes=list_lexemes->next;
        }
        colonne+=(*end-ligne_source);
        // Si on est arrivé à la fin de la liste des lexemes c'est qu'on a pas trouvé de lexème et on informe l'utilisateur.
        if(!list_lexemes){
          printf("Erreur, lexeme non identifié ligne %d colonne %d",ligne,colonne);
          list_delete(queue_lexemes_identifies,lexem_delete);
          fclose(source_f);
          list_delete(list_lexemes,lexeme_conf_delete);
          exit(1);
        }
        // Sinon, on stock ce lexeme dans la liste des lexemes identifiés.
        strncpy(lexem_value,ligne_source,(*end-ligne_source));
        queue_lexemes_identifies=enqueue(queue_lexemes_identifies,lexem_new(((struct lexeme_config*)(list_lexemes->content))->regexp_name,lexem_value,ligne,colonne));
        ligne_source = (*end);
      }
  }

  queue_lexemes_identifies=queue_to_list(queue_lexemes_identifies);
  list_print(queue_lexemes_identifies,lexem_print);
  list_delete(queue_lexemes_identifies,lexem_delete);

  fclose(source_f);
  list_delete(list_lexemes,lexeme_conf_delete);
}
