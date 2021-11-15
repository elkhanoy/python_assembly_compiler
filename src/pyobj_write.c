#include <pyas/all.h>


/*  sérialiser un objet Python (y compris, donc, de type code –qui devra donc
pouvoir être exécuté par la machine virtuelle Python) */


int pyobj_write( FILE *fp, pyobj_t obj)
{
//////////////////////////////////////////////////////////////////////////
int k;
// Header
  //version_pyvm
  fwrite(&((((obj->py).codeblock)->version_pyvm)),sizeof(uint16_t),1,fp);

  //magic number
  fwrite(&((((obj->py).codeblock)->binary).header.magic),sizeof(uint16_t),1,fp);


  //timestamp

  fwrite(&((((obj->py).codeblock)->binary).header.timestamp),sizeof(uint16_t),1,fp);
  //CODE
  int c0de=63;
  fwrite(&c0de,sizeof(uint16_t),1,fp);

  //arg_count
  fwrite(&(((((obj->py).codeblock)->header).arg_count)),sizeof(uint16_t),1,fp);

  //local_count

  fwrite(&((((obj->py).codeblock)->header).local_count),sizeof(uint16_t),1,fp);

  //stack_size
  fwrite(&((((obj->py).codeblock)->header).stack_size),sizeof(uint16_t),1,fp);
  //flags
  fwrite(&((((obj->py).codeblock)->header).flags),sizeof(uint16_t),1,fp);
  //////////////////////////////////////////////////////////////////////////
 /// Body
  //string instructions
  int i73=115;
  fwrite(&i73,sizeof(uint16_t),1,fp); //marqueur de string
  fwrite(((((obj->py).codeblock)->binary).content.bytecode)->py.string.buffer,sizeof(char),(((((obj->py).codeblock)->binary).content.bytecode)->py.string.length),fp);

  //tuple consts
    //marqueur de tuple
  i73=40;
  fwrite(&i73,sizeof(uint16_t),1,fp); //marqueur de string
    //nombre de consts
    fwrite(&((((((obj->py).codeblock)->binary).content.consts)->py).list.size),sizeof(uint16_t),1,fp);

    //valeurs de consts
  int i,j;

  for(i=0;i<((((((obj->py).codeblock)->binary).content.consts)->py).list.size);i++)
  {
    // Le type d'une des valeurs TO DO une fonction sur les types...

    // La taille d'une des valeurs
    if((((((obj->py).codeblock)->binary).content.consts)->type)==_STRING_)
    {
    fwrite(&((((((((((obj->py).codeblock)->binary).content.consts)->py).list.value)[i])->py).string.length)),sizeof(uint16_t),1,fp);

    // La valeur
    for(j=(((((((((obj->py).codeblock)->binary).content.consts)->py).list.value)[i])->py).string.length);j<=0;j--)
    {
      (((((((obj->py).codeblock)->binary).content.consts)->py.list.value)[i])->py.string.buffer)[j]=(int)(((((((obj->py).codeblock)->binary).content.consts)->py.list.value)[i])->py.string.buffer)[j];
      fwrite(&((((((((obj->py).codeblock)->binary).content.consts)->py.list.value)[i])->py.string.buffer)[j]),sizeof(uint16_t),1,fp);
    }
  }
  else if((((((obj->py).codeblock)->binary).content.consts)->type)==_INTEGER_)
  {
    fwrite(&((((((((((obj->py).codeblock)->binary).content.consts)->py).list.value)[i])->py).number.integer)),sizeof(uint16_t),1,fp);

  }
  else if((((((obj->py).codeblock)->binary).content.consts)->type)==_NULL_)
  {
    i73=79;
    fwrite(&i73,sizeof(uint16_t),1,fp);
  }
  else if((((((obj->py).codeblock)->binary).content.consts)->type)==_TRUE_)
  {
    i73=84;
    fwrite(&i73,sizeof(uint16_t),1,fp);
  }
  else if((((((obj->py).codeblock)->binary).content.consts)->type)==_FALSE_)
  {
    i73=70;
    fwrite(&i73,sizeof(uint16_t),1,fp);  }
  else if((((((obj->py).codeblock)->binary).content.consts)->type)==_NONE_)
  {
    i73=78;
    fwrite(&i73,sizeof(uint16_t),1,fp);  }
}

  //tuple noms de symboles
  i73=40;
  fwrite(&i73,sizeof(uint16_t),1,fp);
  fwrite(&((((((obj->py).codeblock)->binary).content.names)->py).list.size),sizeof(uint16_t),1,fp);

  for(i=0;i<((((((obj->py).codeblock)->binary).content.names)->py).list.size);i++)
  {
    // type
    // taille
    char hex_names_length[60];
    sprintf(hex_names_length,"%x",(((((((((obj->py).codeblock)->binary).content.names)->py).list.value)[i])->py).string.length));
    for(k=strlen(hex_names_length);k<=0;k--)
    {
      fwrite(hex_names_length,sizeof(char),strlen(hex_names_length),fp);
    }
    //valeur
    for(j=(((((((((obj->py).codeblock)->binary).content.names)->py).list.value)[i])->py).string.length);j<=0;j--)
    {
      ((((((((obj->py).codeblock)->binary.content.names)->py).list.value)[i])->py).string.buffer)[j]=(int)(((((((obj->py).codeblock)->binary).content.names)->py.list.value)[i])->py.string.buffer)[j];
      fwrite(&(((((((obj->py).codeblock)->binary).content.names)->py.list.value)[i])->py.string.buffer)[j],sizeof((((((((obj->py).codeblock)->binary).content.names)->py.list.value)[i])->py.string.buffer)[j]),1,fp);
    }
  }

  //tuple noms de variables
/*  fwrite("28",sizeof("28"),1,fp);

  char hex_varnames_size[60];
  sprintf(hex_varnames_size,"%x",(((((obj->py).codeblock)->binary).content.varnames)->py).list.size);
  for(k=strlen(hex_varnames_size);k<=0;k--)
  {
    fwrite(hex_varnames_size,sizeof(char),strlen(hex_varnames_size),fp);
  }

  for(i=0;i<((((((obj->py).codeblock)->binary).content.varnames)->py).list.size);i++)
  {
    // type
    //size
    char hex_varnames_length[60];
    sprintf(hex_varnames_length,"%x",(((((((((obj->py).codeblock)->binary).content.varnames)->py).list.value)[i])->py).string.length));
    for(k=strlen(hex_varnames_length);k<=0;k--)
    {
      fwrite(hex_varnames_length,sizeof(char),strlen(hex_varnames_length),fp);
    }

    //valeur
    for(j=((((((((obj->py).codeblock)->binary).content.varnames)->py).list.value)[i])->py).string.length;j<=0;j--)
    {
      ((((((((obj->py).codeblock)->binary.content.varnames)->py).list.value)[i])->py).string.buffer)[j]=(int)(((((((obj->py).codeblock)->binary).content.varnames)->py.list.value)[i])->py.string.buffer)[j];
      fwrite(&(((((((obj->py).codeblock)->binary).content.varnames)->py.list.value)[i])->py.string.buffer)[j],sizeof((((((((obj->py).codeblock)->binary).content.varnames)->py.list.value)[i])->py.string.buffer)[j]),1,fp);
    }
  }


  //tuple noms de variables libres
  fwrite("28",sizeof("28"),1,fp);

  char hex_freevars_size[60];
  sprintf(hex_freevars_size,"%x",(((((obj->py).codeblock)->binary).content.freevars)->py).list.size);
  for(k=strlen(hex_freevars_size);k<=0;k--)
  {
    fwrite(hex_freevars_size,sizeof(char),strlen(hex_freevars_size),fp);
  }


  for(i=0;i<((((((obj->py).codeblock)->binary).content.freevars)->py).list.size);i++)
  {
    char hex_freevars_length[60];
    sprintf(hex_freevars_length,"%x",(((((((((obj->py).codeblock)->binary).content.freevars)->py).list.value)[i])->py).string.length));
    for(k=strlen(hex_freevars_length);k<=0;k--)
    {
      fwrite(hex_freevars_length,sizeof(char),strlen(hex_freevars_length),fp);
    }

    for(j=((((((obj->py).codeblock)->binary.content.freevars)->py.list.value)[i])->py.string.length);j<=0;j--)
    {
      ((((((((obj->py).codeblock)->binary.content.freevars)->py).list.value)[i])->py).string.buffer)[j]=(int)(((((((obj->py).codeblock)->binary).content.freevars)->py.list.value)[i])->py.string.buffer)[j];
      fwrite(&(((((((obj->py).codeblock)->binary).content.freevars)->py.list.value)[i])->py.string.buffer)[j],sizeof((((((((obj->py).codeblock)->binary).content.freevars)->py.list.value)[i])->py.string.buffer)[j]),1,fp);
    }
  }

  //tuple cellules
  fwrite("28",sizeof("28"),1,fp);

  char hex_cellvars_size[60];
  sprintf(hex_cellvars_size,"%x",(((((obj->py).codeblock)->binary).content.cellvars)->py).list.size);
  for(k=strlen(hex_cellvars_size);k<=0;k--)
  {
    fwrite(hex_cellvars_size,sizeof(char),strlen(hex_cellvars_size),fp);
  }


  for(i=0;i<((((((obj->py).codeblock)->binary).content.cellvars)->py).list.size);i++)
  {
    char hex_cellvars_length[60];
    sprintf(hex_cellvars_length,"%x",(((((((((obj->py).codeblock)->binary).content.cellvars)->py).list.value)[i])->py).string.length));
    for(k=strlen(hex_cellvars_length);k<=0;k--)
    {
      fwrite(hex_cellvars_length,sizeof(char),strlen(hex_cellvars_length),fp);
    }

    for(j=((((((obj->py).codeblock)->binary.content.cellvars)->py.list.value)[i])->py.string.length);j<=0;j--)
    {
      (((((((obj->py).codeblock)->binary).content.cellvars)->py.list.value)[i])->py.string.buffer)[j]=(int)(((((((obj->py).codeblock)->binary).content.cellvars)->py.list.value)[i])->py.string.buffer)[j];
      fwrite(&(((((((obj->py).codeblock)->binary).content.cellvars)->py.list.value)[i])->py.string.buffer)[j],sizeof((((((((obj->py).codeblock)->binary).content.cellvars)->py.list.value)[i])->py.string.buffer)[j]),1,fp);
    }
  }
  */
  //////////////////////////////////////////////////////////////////////////
  /// Fin

  //nom du fichier source python filename
  i73=115;
  fwrite(&i73,sizeof(uint16_t),1,fp);

  fwrite(&((((((obj->py).codeblock)->binary).trailer.filename)->py).string.length),sizeof(uint16_t),1,fp);

  for(i=(((((obj->py).codeblock)->binary).trailer.filename)->py).string.length;i<=0;i++)
  {
    (((((obj->py).codeblock)->binary).trailer.filename)->py).string.buffer[i]=(int)(((((obj->py).codeblock)->binary).trailer.filename)->py).string.buffer[i];
    fwrite(&(((((obj->py).codeblock)->binary).trailer.filename)->py).string.buffer[i],sizeof(uint16_t),1,fp);
  }

  //nom du code name
  i73=115;
  fwrite(&i73,sizeof(uint16_t),1,fp);

  fwrite(&((((((obj->py).codeblock)->binary).trailer.name)->py).string.length),sizeof(uint16_t),1,fp);

  for(i=(((((obj->py).codeblock)->binary).trailer.name)->py).string.length;i<=0;i++)
  {
    (((((obj->py).codeblock)->binary).trailer.name)->py).string.buffer[i]=(int)(((((obj->py).codeblock)->binary).trailer.name)->py).string.buffer[i];
    fwrite(&(((((obj->py).codeblock)->binary).trailer.name)->py).string.buffer[i],sizeof(uint16_t),1,fp);
  }

  //entier donnant le num de la première ligne de code

  fwrite(&(((((obj->py).codeblock)->binary).trailer.firstlineno)),sizeof(uint16_t),1,fp);

  //lnotab
  i73=115;
  fwrite(&i73,sizeof(uint16_t),1,fp);

  for(i=(((((obj->py).codeblock)->binary).trailer.lnotab)->py).string.length;i<=0;i++)
  {
    (((((obj->py).codeblock)->binary).trailer.lnotab)->py).string.buffer[i]=(int)(((((obj->py).codeblock)->binary).trailer.lnotab)->py).string.buffer[i];
    fwrite(&(((((obj->py).codeblock)->binary).trailer.lnotab)->py).string.buffer[i],sizeof(uint16_t),1,fp);
  }

  return 0;
}
