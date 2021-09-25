struct lexeme
{
  char regexp_name[64]; //Nom du lexeme
  char regexp_str[256]; //Expression regulière sous forme de chaine de caractères
  struct link_t * queue_regexp; //Expression regulière est en forme de queue de char_group
};

struct lexem_source
{
  char *type;
  char *value;
  int line;
  int column;
};

queue_t lecture_fichier_conf(queue_t lexemes_q, char * config);
