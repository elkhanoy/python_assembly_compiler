#include <pyas/all.h>

queue_t lecture_fichier_conf(queue_t lexemes_q, char * config){
  char buffer[256];
  FILE* fichier = NULL;
  fichier = fopen(config, "rt");
  if(NULL==fichier)
  {
    perror("fopen");
    return NULL;
  }

  while(!feof(fichier))
  {
    struct lexeme * lexeme;
    lexeme=calloc(1,sizeof(*lexeme));
    fscanf(fichier,"%s",lexeme->name);
    if((lexeme->name)[0]!='#')
    {
      fscanf(fichier,"%s",lexeme->regexp_str);
      lexeme->queue_regexp=re_read(lexeme->regexp_str);
      lexemes_q=enqueue(lexemes_q,lexeme);
    }
    else
    {
      fgets(buffer,256,fichier);
    }
  }
  fclose(fichier);
  return lexemes_q;
}
