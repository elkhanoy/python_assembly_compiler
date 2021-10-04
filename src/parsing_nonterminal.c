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
    return 0;
  }
  return 0;
}
//〈set-version-pyvm〉: :=  {‘dir::set’}{‘blank’}{‘version_pyvm’}{‘blank’}{‘integer::dec’}〈eol〉
int parse_set_version_pyvm(list_t * lexems)
{
  printf("Parsing set-version-pyvm \n");
  if(next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "version_pyvm"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "integer::dec"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems))
  {
    return -1;
  }
  return 0;
  }

}
//〈set-flags〉: :=  {‘dir::set’} {‘blank’} {‘flags’} {‘blank’} {‘integer::hex’}〈eol〉
int parse_set_flags(list_t * lexems)
{
  if(next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "flags"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "integer::hex"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems))
  {
    return -1;
  }
  return 0;
}
//〈set-filename〉: :=  {‘dir::set’} {‘blank’} {‘filename’} {‘blank’} {‘string’}〈eol〉
int parse_set_filename(list_t * lexems)
{
  if(next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "filename"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "string"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems))
  {
    return -1;
  }
  return 0;
}
//〈set-name〉: :=  {‘dir::set’} {‘blank’} {‘name’} {‘blank’} {‘string’}〈eol〉
int parse_set_names(list_t * lexems)
{
  if(next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "name"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "string"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems))
  {
    return -1;
  }
  return 0;
}
//〈set-source-size〉: :=  {‘dir::set’}{‘blank’}{‘source_size’}{‘blank’}{‘integer::dec’}〈eol〉
int parse_set_source_size(list_t * lexems)
{
  if(next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "source_size"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "integer::dec"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems))
  {
    return -1;
  }
  return 0;
}
//〈set-stack-size〉: :=  {‘dir::set’}{‘blank’}{‘stack_size’}{‘blank’}{‘integer::dec’}〈eol〉
int parse_set_stack_size(list_t * lexems)
{
  if(next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "stack_size"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "integer::dec"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems))
  {
    return -1;
  }
  return 0;
}
//〈set-arg-count〉: :=  {‘dir::set’}{‘blank’}{‘arg_count’}{‘blank’}{‘integer::dec’}〈eol〉
int parse_set_arg_count(list_t*lexems)
{
  if(next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "arg_count"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "integer::dec"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems))
  {
    return -1;
  }
  return 0;
}
//〈set-kwonly-arg-count〉: :=  {‘dir::set’}{‘blank’}{‘kwonly_arg_count’}{‘blank’} {‘integer::dec’}〈eol〉
int parse_set_kwonly_arg_count(list_t*lexems)
{
  if(next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "kwonly_arg_count"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "integer::dec"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems))
  {
    return -1;
  }
  return 0;
}
//〈set-posonly-arg-count〉: :=  {‘dir::set’}{‘blank’}{‘posonly_arg_count’}{‘blank’} {‘integer::dec’}〈eol〉
int parse_set_posonly_arg_count(list_t*lexems)
{
  if(next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "posonly_arg_count"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "blank"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(next_lexem_is(lexems, "integer::dec"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems))
  {
    return -1;
  }
  return 0;
}
//〈interned-strings〉: :=  {‘dir::interned’}〈eol〉( {‘string’}〈eol〉)*
int parse_interned_strings(list_t*lexems)
{
  if(next_lexem_is(lexems, "dir::interned"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  while(next_lexem_is(lexems,"string"))
  {
    lexem_advance(lexems);
    if(-1==parse_eol(lexems))
    {
      return -1;
    }
  }
  return 0;
}
//〈constants〉: :=  {‘dir::consts’}〈eol〉(〈constant〉〈eol〉)*
int parse_constants(list_t*lexems)
{
  printf("Parsing Constants\n");
  if(next_lexem_is(lexems, "dir::consts"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems))
  {
    return -1;
  }
  lexem_advance(lexems);
  while(parse_constant(lexems))
  {
    lexem_advance(lexems);
    if(-1==parse_eol(lexems))
    {
      return -1;
    }
  }
  return 0;
}
//〈constant〉: :=  {‘integer’} | {‘float’} | {‘string’} | {‘pycst’} |〈list〉|〈tuple〉
int parse_set_source_size()
{

}

int parse_
