struct lexeme_config
{
  char regexp_name[256]; //Nom du lexeme
  char regexp_str[256]; //Expression regulière sous forme de chaine de caractères
  struct link_t * queue_regexp; //Expression regulière est en forme de queue de char_group
};

queue_t lecture_fichier_conf(queue_t lexemes_q, char * config);
int print_lexeme_conf(void * _lexeme_config);
int lexeme_conf_delete(void * _lexeme_config);
int char_group_delete(void * _char_group);
int regexp_print (void * _regexp_q);
