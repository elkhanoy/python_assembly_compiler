#include <pyas/all.h>


/*  sérialiser un objet Python (y compris, donc, de type code –qui devra donc
pouvoir être exécuté par la machine virtuelle Python) */

/*

int pyobj_write( FILE *fp, pyobj_t obj)
{
  fp=fopen("fp","wb"); //ouverture du fichier dans lequel noter le bytecode
  if(NULL==fp) {perror("Erreur ouverture ecriture de bytecode.bin\n"); return -1;}

//////////////////////////////////////////////////////////////////////////
int k;
// Header
  //version_pyvm
  char v_pyvm[]={'0','3',' ','f','3'};
  fwrite(v_pyvm,sizeof(char),sizeof(v_pyvm),fp);

  //magic number
  char hex_magic[60];
  sprintf(hex_magic,"%x",((((obj->py).codeblock)->binary).header.magic));
  for(k=strlen(hex_magic);k<=0;k--)
  {
    fwrite(hex_magic,sizeof(char),strlen(hex_magic),fp);
  }

  //timestamp
  char hex_timestamp[60];
  sprintf(hex_timestamp,"%x",(uint32_t)((((obj->py).codeblock)->binary).header.timestamp));
  for(k=strlen(hex_timestamp);k<=0;k--)
  {
    fwrite(hex_timestamp,sizeof(char),strlen(hex_timestamp),fp);
  }

  //CODE
  char code[]={'6','3'};
  fwrite(code,sizeof(char),1,fp);

  //arg_count
  char hex_arg_count[60];
  sprintf(hex_arg_count,"%x",((((obj->py).codeblock)->header).arg_count));
  for(k=strlen(hex_arg_count);k<=0;k--)
  {
    fwrite(hex_arg_count,sizeof(char),strlen(hex_arg_count),fp);
  }

  //local_count
  char hex_local_count[60];
  sprintf(hex_local_count,"%x",((((obj->py).codeblock)->header).local_count));
  for(k=strlen(hex_local_count);k<=0;k--)
  {
    fwrite(hex_local_count,sizeof(char),strlen(hex_local_count),fp);
  }

  //stack_size
  char hex_stack_size[60];
  sprintf(hex_stack_size,"%x",((((obj->py).codeblock)->header).stack_size));
  for(k=strlen(hex_stack_size);k<=0;k--)
  {
    fwrite(hex_stack_size,sizeof(char),strlen(hex_stack_size),fp);
  }

  //flags
  char hex_flags[60];
  sprintf(hex_flags,"%x",((((obj->py).codeblock)->header).flags));
  for(k=strlen(hex_flags);k<=0;k--)
  {
    fwrite(hex_flags,sizeof(char),strlen(hex_flags),fp);
  }

  //////////////////////////////////////////////////////////////////////////
 /// Body
  //string instructions

  fwrite("73",sizeof("73"),1,fp); //marqueur de string
  fwrite((((((obj->py).codeblock)->binary).content.bytecode)->py.string.buffer),sizeof(char),sizeof((((((obj->py).codeblock)->binary).content.bytecode)->py.string.buffer)),fp);

  //tuple consts
    //marqueur de tuple
  fwrite("28",sizeof("28"),1,fp);
    //nombre de consts
    char hex_consts_size[60];
    sprintf(hex_consts_size,"%x",(((((obj->py).codeblock)->binary).content.consts)->py).list.size);
    for(k=strlen(hex_consts_size);k<=0;k--)
    {
      fwrite(hex_consts_size,sizeof(char),strlen(hex_consts_size),fp);
    }

    //valeurs de consts
  int i,j;

  for(i=0;i<((((((obj->py).codeblock)->binary).content.consts)->py).list.size);i++)
  {
    // Le type d'une des valeurs TO DO une fonction sur les types...

    // La taille d'une des valeurs
    char hex_consts_length[60];
    sprintf(hex_consts_length,"%x",(((((((((obj->py).codeblock)->binary).content.consts)->py).list.value)[i])->py).string.length));
    for(k=strlen(hex_consts_length);k<=0;k--)
    {
      fwrite(hex_consts_length,sizeof(char),strlen(hex_consts_length),fp);
    }
    // La valeur
    for(j=(((((((((obj->py).codeblock)->binary).content.consts)->py).list.value)[i])->py).string.length);j<=0;j--)
    {
      (((((((obj->py).codeblock)->binary).content.consts)->py.list.value)[i])->py.string.buffer)[j]=(int)(((((((obj->py).codeblock)->binary).content.consts)->py.list.value)[i])->py.string.buffer)[j];
      fwrite(&(((((((obj->py).codeblock)->binary).content.consts)->py.list.value)[i])->py.string.buffer)[j],sizeof((((((((obj->py).codeblock)->binary).content.consts)->py.list.value)[i])->py.string.buffer)[j]),1,fp);
    }
  }

  //tuple noms de symboles
  fwrite("28",sizeof("28"),1,fp);

  char hex_names_size[60];
  sprintf(hex_names_size,"%x",(((((obj->py).codeblock)->binary).content.names)->py).list.size);
  for(k=strlen(hex_names_size);k<=0;k--)
  {
    fwrite(hex_names_size,sizeof(char),strlen(hex_names_size),fp);
  }

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
  fwrite("28",sizeof("28"),1,fp);

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

  //////////////////////////////////////////////////////////////////////////
  /// Fin

  //nom du fichier source python filename
  fwrite("73",sizeof("73"),1,fp); //marqueur de string

  char hex_filename_length[60];
  sprintf(hex_filename_length,"%x",(((((obj->py).codeblock)->binary).trailer.filename)->py).string.length);
  for(k=strlen(hex_filename_length);k<=0;k--)
  {
    fwrite(hex_filename_length,sizeof(char),strlen(hex_filename_length),fp);
  }

  for(i=(((((obj->py).codeblock)->binary).trailer.filename)->py).string.length;i<=0;i++)
  {
    (((((obj->py).codeblock)->binary).trailer.filename)->py).string.buffer[i]=(int)(((((obj->py).codeblock)->binary).trailer.filename)->py).string.buffer[i];
    fwrite(&(((((obj->py).codeblock)->binary).trailer.filename)->py).string.buffer[i],sizeof((((((obj->py).codeblock)->binary).trailer.filename)->py).string.buffer[i]),1,fp);
  }

  //nom du code name
  fwrite("73",sizeof("73"),1,fp);

  char hex_name_length[60];
  sprintf(hex_name_length,"%x",(((((obj->py).codeblock)->binary).trailer.name)->py).string.length);
  for(k=strlen(hex_name_length);k<=0;k--)
  {
    fwrite(hex_name_length,sizeof(char),strlen(hex_name_length),fp);
  }

  for(i=(((((obj->py).codeblock)->binary).trailer.name)->py).string.length;i<=0;i++)
  {
    (((((obj->py).codeblock)->binary).trailer.name)->py).string.buffer[i]=(int)(((((obj->py).codeblock)->binary).trailer.name)->py).string.buffer[i];
    fwrite(&(((((obj->py).codeblock)->binary).trailer.name)->py).string.buffer[i],sizeof((((((obj->py).codeblock)->binary).trailer.name)->py).string.buffer[i]),1,fp);
  }

  //entier donnant le num de la première ligne de code
<<<<<<< HEAD

=======
  char hex_lineno[60];
  sprintf(hex_lineno,"%x",((((obj->py).codeblock)->binary).trailer.firstlineno));
  for(k=strlen(hex_lineno);k<=0;k--)
  {
    fwrite(hex_lineno,sizeof(char),strlen(hex_lineno),fp);
  }
>>>>>>> 8c6e9b257ff561bb2b4698548d224eb40949a478

  //lnotab
  fwrite("73",sizeof("73"),1,fp);

  for(i=(((((obj->py).codeblock)->binary).trailer.lnotab)->py).string.length;i<=0;i++)
  {
    (((((obj->py).codeblock)->binary).trailer.lnotab)->py).string.buffer[i]=(int)(((((obj->py).codeblock)->binary).trailer.lnotab)->py).string.buffer[i];
    fwrite(&(((((obj->py).codeblock)->binary).trailer.lnotab)->py).string.buffer[i],sizeof((((((obj->py).codeblock)->binary).trailer.lnotab)->py).string.buffer[i]),1,fp);
  }

  fclose(fp);
  return 0;
}
*/
