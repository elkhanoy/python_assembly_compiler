//〈pys〉: :=〈eol〉〈prologue〉〈code〉
int parse_pys(list_t * lexems)
{
  printf("Parsing pys expression \n");
  if(-1==parse_eol(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_prologue(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_code(lexems))
  {
    return -1;
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
//〈prologue〉: :=〈set-directives〉 〈interned-strings〉 〈constants〉 〈names〉〈varnames〉〈freevars〉〈cellvars〉
int parse_prologue(list_t * lexems)
{
  printf("Parsing prologue expression \n");
  if(-1==parse_set_directives(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_interned_strings(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_constants(lexems))
  {
    return -1;
  }
  if(-1==parse_names(lexems))
  {
    return -1;
  }
  if(-1==parse_constants(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_names(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_varnames(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_freevars(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_cellevars(lexems))
  {
    return -1;
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
//〈set-directives〉: :=〈set-version-pyvm〉 〈set-flags〉 〈set-filename〉 〈set-name〉[〈set-source-size〉]〈set-stack-size〉 〈set-arg-count〉[set-kwonly-arg-count][set-posonly-arg-count]
int parse_set_directives(list_t * lexems)
{
  if(-1==parse_set_version_pyvm(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_set_flags(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_set_filename(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_set_name(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(0==parse_set_source_size(lexems))
  {
    lexem_advance(lexems);
  }
  if(-1==parse_set_stack_size(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_set_arg_count(lexems))
  {
    return -1;
  }
  if(0==parse_set_kwonly_arg_count(lexems))
  {
    lexem_advance(lexems);
  }
  return 0;
}

int parse_code(list_t * lexems)
{

}

int parse_set_directives(list_t * lexems)
{

}

int parse_interned_strings(list_t * lexems)
{

}

int parse_constants(list_t * lexems)
{

}

int parse_names(list_t * lexems)
{

}

int parse_prologue(list_t * lexems)
{

}

int parse_set_directives()
{

}

int parse_set_version_pyvm()
{

}

int parse_set_flags()
{

}

int set_filename()
{

}

int parse_set_name()
{

}

int parse_set_source_size()
{

}

int parse_
