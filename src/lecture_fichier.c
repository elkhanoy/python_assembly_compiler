#include <pyas/all.h>

queue_t lecture_fichier_conf(queue_t lexemes_q, char * config)
{
  char buffer[256];
  char comment_test[256];

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
    fscanf(fichier,"%s",comment_test);
    if(comment_test[0]!='#') // Si la ligne n'est pas un commentaire...
    {
      struct lexeme * lexeme; // On crée un type lexeme
      lexeme=calloc(1,sizeof(*lexeme)); // On lui alloue de la mémoire
      lexeme->regexp_name=comment_test;// Et on stock son nom
      fscanf(fichier,"%s",lexeme->regexp_str); // ainsi que son expression régulière
      lexeme->queue_regexp=re_read(lexeme->regexp_str); // On "transforme" l'expression reg. (qui est en type char*) en type char group.
      lexemes_q=enqueue(lexemes_q,lexeme); // On insère ce lexème dans la file.
    }
    else // Sinon on stock cette ligne dans une variable tampon qu'on n'utilisera pas.
    {
      fgets(buffer,256,fichier);
    }
  }
  fclose(fichier);
  return lexemes_q;
}
