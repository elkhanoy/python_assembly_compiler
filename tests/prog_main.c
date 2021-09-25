#include <pyas/all.h>

int main(int argc,char*argv[]) //Les noms des fichiers source et configuration seront placés en paramètre (config en argument 1 et source en 2)
{
  if(argc<3) //Le nombre de paramètres ajoutés doit être de 2
  {
    printf("Entrer deux paramètres\n");
    exit(EXIT_FAILURE);
  }

// 1 - Déclaration des variables utilisées pour les fonctions définies dans les fichiers .c
  char * end=NULL;
  queue_t queue_lexemes=NULL; //Queue de lexemes créée par la lecture du fichier de configuration
  char config_name[80]; //Nom du fichier de configuration
  char source_name[80]; //Nom du fichier source

// 2 - Récupération des noms des fichiers placés en paramètre dans le terminal
  strcpy(config_name,argv[1]); //Copie du nom du fichier de configuration pris en paramètre lors de la compilation, dans le tableau
  strcpy(source_name,argv[2]); //Copie du nom du fichier source pris en paramètre lors de la compilation, dans le tableau

// 3 - Création de la liste des lexemes
  queue_lexemes=lecture_fichier_conf(queue_lexemes, config_name); //Appel de la fonction re_read dans la fonction lecture_fichier_conf

  if(!queue_lexemes)
  {
    printf("Erreur");
    exit(1);
  }

 // 4 - Ouverture du fichier source dont le nom est placé en paramètre dans le terminal
  FILE* source_f= NULL;
  source_f = fopen(source_f, "rt");
  if(NULL==source)
  {
    perror("fopen");
    return 0;
  }

  // 5 - Copie du fichier source dans un tableau alloué de char
  // 5.1 - Détermination de la longueur du fichier source
    int longueur_f=0;
    char c;
    while(fscanf(source_f,"%c",&c) != EOF)
    {
      longueur_f++;
    }
  // 5.2 - Copie du contenu du fichier source dans un tableau alloué
    char *tableau_source = (char *)malloc(longueur_f*sizeof(char)); //Allocation de la bonne longueur
    if(NULL==tableau_source)
    {
      perror("fopen");
      return 0;
    }
    int i=0;
    char c;
    while(fscanf(source_f,"%c",&c) != EOF)
    {
      tableau_source[i]=c;
      i++;
    }
    // 6 - Comparaison entre le contenu du fichier source et les lexemes possibles
    while(( !re_match((queue_lexemes, tableau_source, end) ) && ( lexeme->next != lexeme_first ) )
    {
        lexeme=lexeme->next;
    }
    // On part du principe que quelque soit le mot dans source, on trouve toujours un lexeme associé, mais on ajoute un if par précaution.
    if(re_match(((struct lexeme*)(lexeme->content))->regexp_name,word_source,end))
    {
      list_lexem=enqueue(list_lexem,lexem_new(((struct lexeme*)(lexeme->content))->regexp_name,word_source,0,0)); // Pour l'instant on sait pas donner la ligne et colonne, donc on donne 0 0
    }
  }

  list_lexem=queue_to_list(list_lexem);
  list_print(list_lexem,lexem_print);
  list_delete(list_lexem,lexem_delete);

  fclose(source);
  queue_delete(lexeme);
}
