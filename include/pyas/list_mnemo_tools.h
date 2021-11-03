//Structure utile pour la iste des structure de la section .text du fichier assembleur

struct contenu_point_text
{
  int lineno; //Retiens la ligne de la mnémonique
  char*mnemo; //Nom de la mnémonique
  int param; //paramètre pour la mnémonique: -1 si pas de paramètre
  struct contenu_point_text * next;
} txt_t, *list_txt_t;




list_txt_t enqueue( list_txt_t l);

list_txt_t list_txt_new( void );

int     list_txt_empty( list_txt_t l );

list_txt_t text_section_list(FILE*file_conf,list_txt_t list_section_text)
