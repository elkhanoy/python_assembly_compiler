//Structure utile pour la iste des structure de la section .text du fichier assembleur

struct contenu_point_text
{
  int lineno; //Retiens la ligne de la mnémonique
  char*mnemo; //Nom de la mnémonique
  int nb_param; //Nombre de paramètres pour la mnémonique
  struct contenu_point_text * next;
} txt_t, list_txt_t;

list_txt_t enqueue( list_txt_t l);
list_txt_t list_txt_new( void );
