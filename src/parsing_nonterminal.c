#include <pyas/all.h>

//〈pys〉: :=〈eol〉〈prologue〉〈code〉
int parse_pys(list_t * lexems )
{
  printf("Parsing pys expression \n");
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_prologue(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_code(lexems ))
  {
    return -1;
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
//〈prologue〉: :=〈set-directives〉 〈interned-strings〉 〈constants〉 〈names〉〈varnames〉〈freevars〉〈cellvars〉
int parse_prologue(list_t * lexems )
{
  printf("Parsing prologue expression \n");
  if(-1==parse_set_directives(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_interned_strings(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_constants(lexems ))
  {
    return -1;
  }
  if(-1==parse_names(lexems ))
  {
    return -1;
  }
  if(-1==parse_constants(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_names(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_varnames(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_freevars(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_cellvars(lexems ))
  {
    return -1;
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
//〈set-directives〉: :=〈set-version-pyvm〉 〈set-flags〉 〈set-filename〉 〈set-name〉[〈set-source-size〉]〈set-stack-size〉 〈set-arg-count〉[set-kwonly-arg-count][set-posonly-arg-count]
int parse_set_directives(list_t * lexems )
{
  if(-1==parse_set_version_pyvm(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_set_flags(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_set_filename(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_set_name(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(0==parse_set_source_size(lexems ))
  {
    lexem_advance(lexems);
  }
  if(-1==parse_set_stack_size(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==parse_set_arg_count(lexems ))
  {
    return -1;
  }
  if(0==parse_set_kwonly_arg_count(lexems ))
  {
    return 0;
  }
  return 0;
}
//〈set-version-pyvm〉: :=  {‘dir::set’}{‘blank’}{‘version_pyvm’}{‘blank’}{‘integer::dec’}〈eol〉
int parse_set_version_pyvm(list_t * lexems )
{
  printf("Parsing set-version-pyvm \n");
  if(0==next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "version_pyvm"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "integer::dec"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  return 0;
}
//〈set-flags〉: :=  {‘dir::set’} {‘blank’} {‘flags’} {‘blank’} {‘integer::hex’}〈eol〉
int parse_set_flags(list_t * lexems )
{
  if(0==next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "flags"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "integer::hex"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  return 0;
}
//〈set-filename〉: :=  {‘dir::set’} {‘blank’} {‘filename’} {‘blank’} {‘string’}〈eol〉
int parse_set_filename(list_t * lexems )
{
  if(0==next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "filename"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "string"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
return 0;
}
//〈set-name〉: :=  {‘dir::set’} {‘blank’} {‘name’} {‘blank’} {‘string’}〈eol〉
int parse_set_name(list_t * lexems )
{
  if(0==next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "name"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "string"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  return 0;
}
//〈set-source-size〉: :=  {‘dir::set’}{‘blank’}{‘source_size’}{‘blank’}{‘integer::dec’}〈eol〉
int parse_set_source_size(list_t * lexems )
{
  if(0==next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "source_size"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "integer::dec"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  return 0;
}
//〈set-stack-size〉: :=  {‘dir::set’}{‘blank’}{‘stack_size’}{‘blank’}{‘integer::dec’}〈eol〉
int parse_set_stack_size(list_t * lexems )
{
  if(0==next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "stack_size"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "integer::dec"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  return 0;
}
//〈set-arg-count〉: :=  {‘dir::set’}{‘blank’}{‘arg_count’}{‘blank’}{‘integer::dec’}〈eol〉
int parse_set_arg_count(list_t*lexems )
{
  if(0==next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "arg_count"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "integer::dec"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  return 0;
}
//〈set-kwonly-arg-count〉: :=  {‘dir::set’}{‘blank’}{‘kwonly_arg_count’}{‘blank’} {‘integer::dec’}〈eol〉
int parse_set_kwonly_arg_count(list_t*lexems )
{
  if(0==next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "kwonly_arg_count"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "integer::dec"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  return 0;
}
//〈set-posonly-arg-count〉: :=  {‘dir::set’}{‘blank’}{‘posonly_arg_count’}{‘blank’} {‘integer::dec’}〈eol〉
int parse_set_posonly_arg_count(list_t*lexems )
{
  if(0==next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "posonly_arg_count"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "integer::dec"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  return 0;
}

int parse_set(list_t * lexems ) {
  if(0==next_lexem_is(lexems, "dir::set"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(0==next_lexem_is(lexems, "posonly_arg_count"))
  {
    lexem_advance(lexems);
    return 0;
  }
  if(0==next_lexem_is(lexems, "arg_count"))
  {
    lexem_advance(lexems);
    return 0;
  }
  return 0;
}


//〈interned-strings〉: :=  {‘dir::interned’}〈eol〉( {‘string’}〈eol〉)*
int parse_interned_strings(list_t*lexems )
{
  if(0==next_lexem_is(lexems, "dir::interned"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  while(0==next_lexem_is(lexems,"string"))
  {
    lexem_advance(lexems);
    if(-1==parse_eol(lexems ))
    {
      return -1;
    }
  }
  return 0;
}
//〈constants〉: :=  {‘dir::consts’}〈eol〉(〈constant〉〈eol〉)*
int parse_constants(list_t*lexems )
{
  printf("Parsing Constants\n");
  if(0==next_lexem_is(lexems, "dir::consts"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  while(parse_constant(lexems )==0)
  {
    lexem_advance(lexems);
    if(-1==parse_eol(lexems ))
    {
      return -1;
    }
  }
  return 0;
}
//〈constant〉: :=  {‘integer’} | {‘float’} | {‘string’} | {‘pycst’} |〈list〉|〈tuple〉
int parse_constant(list_t*lexems )
{
  printf("Parsing Constant\n");
  if(next_lexem_is(lexems, "integer")||next_lexem_is(lexems,"float"))
  {
    return 0;
  }
  if(next_lexem_is(lexems, "string")||next_lexem_is(lexems,"pycst"))
  {
    return 0;
  }
  if(parse_list(lexems )==0)
  {
    return 0;
  }
  if(parse_tuple(lexems )==0)
  {
    return 0;
  }
  return -1;
}
//〈list〉: :=  {‘brack::left’}〈constant〉* {‘brack::right’}
int parse_list(list_t*lexems )
{
  printf("Parsing List\n");
  if(0==next_lexem_is(lexems, "brack::left"))
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  while(parse_constant(lexems )==0)
  {
    lexem_advance(lexems);
  }
  if(-1==next_lexem_is(lexems,"brack::right"))
  {
    return -1;
  }
  return 0;
}
//〈tuple〉: :=  {‘paren::left’}〈constant〉* {‘paren::right’}
int parse_tuple(list_t*lexems )
{
  printf("Parsing tuple\n");
  if(next_lexem_is(lexems,"left")==0)
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  while(parse_constant(lexems )==0)
  {
    lexem_advance(lexems);
  }
  if(-1==next_lexem_is(lexems,"paren::right"))
  {
    return -1;
  }
  return 0;
}
//〈names〉: :=  {‘dir::names’}〈eol〉( {‘string’}〈eol〉)*
int parse_names(list_t*lexems )
{
  printf("Parsing names\n");
  if(next_lexem_is(lexems,"dir::names")==0)
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  while(next_lexem_is(lexems,"string")==0)
  {
    lexem_advance(lexems);
    if(parse_eol(lexems )==-1)
    {
      return -1;
    }
  }
  return 0;
}
//〈varnames〉: :=  {‘dir::varnames’}〈eol〉( {‘string’}〈eol〉)*
int parse_varnames(list_t*lexems )
{
  printf("Parsing varnames\n");
  if(next_lexem_is(lexems,"dir::varnames")==0)
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  while(next_lexem_is(lexems,"string")==0)
  {
    lexem_advance(lexems);
    if(parse_eol(lexems )==-1)
    {
      return -1;
    }
  }
  return 0;
}
//〈freevars〉: :=  {‘dir::freevars’}〈eol〉( {‘string’}〈eol〉)*
int parse_freevars(list_t*lexems )
{
  printf("Parsing freevars\n");
  if(next_lexem_is(lexems,"dir::freevars")==0)
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  while(next_lexem_is(lexems,"string")==0)
  {
    lexem_advance(lexems);
    if(parse_eol(lexems )==-1)
    {
      return -1;
    }
  }
  return 0;
}
//〈cellvars〉: :=  {‘dir::cellvars’}〈eol〉( {‘string’}〈eol〉)*
int parse_cellvars(list_t*lexems )
{
  printf("Parsing cellvars\n");
  if(next_lexem_is(lexems,"dir::cellvars")==0)
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  while(next_lexem_is(lexems,"string")==0)
  {
    lexem_advance(lexems);
    if(parse_eol(lexems )==-1)
    {
      return -1;
    }
  }
  return 0;
}
//〈code〉: :=  {‘dir::text’}〈eol〉(〈assembly-line〉〈eol〉)*
int parse_code(list_t*lexems )
{
  printf("Parsing code\n");
  if(next_lexem_is(lexems,"dir::text")==0)
  {
    lexem_advance(lexems);
  }
  else
  {
    return -1;
  }
  if(-1==parse_eol(lexems ))
  {
    return -1;
  }
  lexem_advance(lexems);
  while(parse_assembly_line(lexems )==0)
  {
    lexem_advance(lexems);
    if(parse_eol(lexems )==-1)
    {
      return -1;
    }
  }
  return 0;
}
//〈assembly-line〉: :=〈insn〉|〈source-lineno〉|〈label〉
int parse_assembly_line(list_t*lexems )
{
  printf("Parsing assembly line\n");
  if(parse_insn(lexems )==0)
  {
    return 0;
  }
  if(parse_source_lineno(lexems )==0)
  {
    return 0;
  }
  if(parse_label(lexems )==0)
  {
    return 0;
  }
  return -1;
}
//〈label〉: :=  {‘symbol’} {‘blank’} {‘colon’}
int parse_label(list_t*lexems )
{
  printf("Parsing Label\n");
  if(-1==next_lexem_is(lexems,"symbol"))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==next_lexem_is(lexems,"blank"))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==next_lexem_is(lexems,"colon"))
  {
    return -1;
  }
  return 0;
}
//〈source-lineno〉: :=  {‘dir::line’} {‘blank’} {‘integer::dec’}
int parse_source_lineno(list_t*lexems )
{
  printf("Parsing Lineno\n");
  if(-1==next_lexem_is(lexems,"dir::line"))
  {
    return -1;
  }
  lexem_advance(lexems);
  if(-1==next_lexem_is(lexems,"integer::dec"))
  {
    return -1;
  }
  return 0;
}
//〈insn〉: :=  {‘insn::0’}|    {‘insn::1’} ( {‘integer::dec’} | {‘symbol’} )
int parse_insn(list_t*lexems )
{
  printf("Parsing insn \n");
  if(-1==next_lexem_is(lexems,"insn::"))
  {
    return -1;
  }
  lexem_advance(lexems);
  if((-1==next_lexem_is(lexems,"integer::dec"))||(-1==next_lexem_is(lexems,"symbol")))
  {
    return -1;
  }
  return 0;
}
//〈eol〉: :=  ([{‘blank’}] [{‘comment’}] {‘newline’})* [{‘blank’}]
int parse_eol(list_t*lexems )
{
  printf("Parsing eol\n");
  if(-1==next_lexem_is(lexems,"newline"))
  {
    return -1;
  }
  while ( next_lexem_is( lexems, "newline" ) ) {
      lexem_advance(lexems);
  }
  return 0;
}
