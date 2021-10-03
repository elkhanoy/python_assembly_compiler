// Renvoyer le prochain lexeme sans l'enlever de la liste
lexem_t lexem_peek(list_t *lexems)
{
  return (*lexems)->next;
}
////////////////////////////////////////////////////////////////////////////////
// Renvoyer le prochain lexeme en l'enlevant de la liste
lexem_t lexem_advance(list_t *lexems)
{
  lexem_t first_prev_list_p=(*lexem); // Pointeur retenant l'ancien premier élément de la liste
  first_prev_list_p->next=NULL;
  (*lexems)=(*lexems)->next; //Nouvelle tête de liste
  return first_prev_list_p;
}
////////////////////////////////////////////////////////////////////////////////
// Déterminer si le prochain lexème utile est bien du type demandé
int next_lexem_is(list_t *lexems, char *type)
{
  
}
////////////////////////////////////////////////////////////////////////////////
// Affichager le message d'erreur msg et les coordonnées du lexème en tête de *lexems
void print_parse_error(char *msg, list_t *lexems)
{

}
