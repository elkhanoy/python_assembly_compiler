lexem_t lexem_peek(list_t *lexems);
lexem_t lexem_advance(list_t *lexems);
int next_lexem_is(list_t *lexems, char *type);
void print_parse_error(char *msg, list_t *lexems);
