#include <pyas/all.h>
// Renvoyer le prochain lexeme sans l'enlever de la liste
lexem_t lexem_peek(list_t *lexems)
{
  list_t lex_l=*lexems;
  while(!strcmp(((struct lexem*)(lex_l->next->content))->type,"blank") || !strcmp(((struct lexem*)(lex_l->next->content))->type,"comment")){
    lex_l=lex_l->next;
  }
  return (lex_l->next)->content;
}

// Renvoyer le type du lexem
int lexem_type ( lexem_t lex , char * type ) {
 return lex -> type == strstr ( lex ->type , type );
}


////////////////////////////////////////////////////////////////////////////////
// Renvoyer le prochain lexeme en l'enlevant de la liste
lexem_t lexem_advance(list_t *lexems)
{
  lexem_t first_prev_list_p=((*lexems)->next)->content; // Pointeur retenant l'ancien premier élément de la liste
  while(!strcmp(((struct lexem*)((*lexems)->next->content))->type,"blank") || !strcmp(((struct lexem*)((*lexems)->next->content))->type,"comment")){
    *lexems=(*lexems)->next; //Nouvelle tête de liste
  }
  *lexems=(*lexems)->next;
  return first_prev_list_p;
}
////////////////////////////////////////////////////////////////////////////////
// Déterminer si le prochain lexème utile est bien du type demandé
 // int next_lexem_is(list_t *lexems, char *type)
 // {
 //   lexem_t lex_l=lexem_peek(lexems);
 //   if (lexem_type(lex_l,type)){
 //     return 0;
 //   }
 //   return -1;
 // }


int next_lexem_type_is(list_t *lexems, char *type)
{
  while(!strcmp((((struct lexem*)((*lexems)->next->content))->type),"blank") || !strcmp((((struct lexem*)((*lexems)->next->content))->type),"comment")){
    *lexems=(*lexems)->next;
  }
  if(!strcmp(( (struct lexem*)((*lexems)->next->content) )->type, type))
  {
    return 0;
  }
  else {
    return -1;
  }
}

int next_lexem_value_is(list_t *lexems, char *value)
{
  while(!strcmp((((struct lexem*)((*lexems)->next->content))->type),"blank") || !strcmp((((struct lexem*)((*lexems)->next->content))->type),"comment")){
    *lexems=(*lexems)->next;
  }
  if(!strcmp(( (struct lexem*)((*lexems)->next->content) )->value, value))
  {
    return 0;
  }
  else {
    return -1;
  }
}
////////////////////////////////////////////////////////////////////////////////
// Affichager le message d'erreur msg et les coordonnées du lexème en tête de *lexems
void print_parse_error(char *msg, list_t *lexems)
{
  printf("%s \n",msg);
  printf("Les coordonnées du lexème en tête de liste sont: ligne: %d et colonne: %d \n", ( (struct lexem*)((*lexems)->content) )->line,( (struct lexem*)((*lexems)->content) )->column);
}
