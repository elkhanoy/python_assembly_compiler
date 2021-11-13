#include <pyas/all.h>


/*  sérialiser un objet Python (y compris, donc, de type code –qui devra donc
pouvoir être exécuté par la machine virtuelle Python) */


int pyobj_write( FILE *fp, pyobj_t obj)
{
  fp=fopen("fp","wb"); //ouverture du fichier dans lequel noter le bytecode
  if(NULL==fp) {perror("Erreur ouverture ecriture de bytecode.bin\n"); return -1;}

//////////////////////////////////////////////////////////////////////////
// Header
  //version_pyvm
  char v_pyvm[]={'0','3',' ','f','3'};
  fwrite(v_pyvm,sizeof(char),sizeof(v_pyvm),fp);

  //magic number
  uint32_t lilend_magic;
  lilend_magic=htole32(((((obj->py).codeblock)->binary).header.magic));
  fwrite(&lilend_magic,sizeof(lilend_magic),1,fp);

  //timestamp
  uint32_t lilend_timefile;
  lilend_timefile=htole32((uint32_t)((((obj->py).codeblock)->binary).header.timestamp));
  fwrite(&lilend_timefile,sizeof(lilend_timefile),1,fp);

  //CODE
  char code[]={'6','3'};
  fwrite(code,sizeof(char),1,fp);

  //arg_count
  uint32_t lilend_arg_count;
  lilend_arg_count=htole32(((((obj->py).codeblock)->header).arg_count));
  fwrite(&lilend_arg_count,sizeof(lilend_arg_count),1,fp);

  //local_count
  uint32_t lilend_local_count;
  lilend_local_count=htole32(((((obj->py).codeblock)->header).local_count));
  fwrite(&lilend_local_count,sizeof(lilend_local_count),1,fp);

  //stack_size
  uint32_t lilend_stack_size;
  lilend_stack_size=htole32(((((obj->py).codeblock)->header).stack_size));
  fwrite(&lilend_stack_size,sizeof(lilend_stack_size),1,fp);

  //flags
  uint32_t lilend_flags;
  lilend_flags=htole32(((((obj->py).codeblock)->header).flags));
  fwrite(&lilend_flags,sizeof(lilend_flags),1,fp);

  //////////////////////////////////////////////////////////////////////////
 /// Body
  //string instructions

  fwrite("73",sizeof("73"),1,fp); //marqueur de string
  fwrite((((((obj->py).codeblock)->binary).content.bytecode)->py.string.buffer),sizeof(char),sizeof((((((obj->py).codeblock)->binary).content.bytecode)->py.string.buffer)),fp);

  //tuple consts
    //marqueur de tuple
  fwrite("28",sizeof("28"),1,fp);
    //nombre de consts
  uint32_t lilend_consts;
  lilend_consts=htole32((((((obj->py).codeblock)->binary).content.consts)->py).list.size);
  fwrite(&lilend_consts,sizeof(lilend_consts),1,fp);

    //valeurs de consts
  int i,j;
  uint32_t consts_len;
  uint32_t lilend_consts_len;


  for(i=0;i<((((((obj->py).codeblock)->binary).content.consts)->py).list.size);i++)
  {
    // Le type d'une des valeurs TO DO une fonction sur les types...

    // La taille d'une des valeurs
    consts_len=(((((((((obj->py).codeblock)->binary).content.consts)->py).list.value)[i])->py).string.length);
    lilend_consts_len=htole32(consts_len);
    fwrite(&lilend_consts_len,sizeof(lilend_consts_len),1,fp);
    // La valeur
    for(j=consts_len;j<=0;j--)
    {
      (((((((obj->py).codeblock)->binary).content.consts)->py.list.value)[i])->py.string.buffer)[j]=(int)(((((((obj->py).codeblock)->binary).content.consts)->py.list.value)[i])->py.string.buffer)[j];
      fwrite(&(((((((obj->py).codeblock)->binary).content.consts)->py.list.value)[i])->py.string.buffer)[j],sizeof((((((((obj->py).codeblock)->binary).content.consts)->py.list.value)[i])->py.string.buffer)[j]),1,fp);
    }
  }

  //tuple noms de symboles
  fwrite("28",sizeof("28"),1,fp);

  uint32_t lilend_names;
  lilend_names=htole32((((((obj->py).codeblock)->binary).content.names)->py).list.size);
  fwrite(&lilend_names,sizeof(lilend_names),1,fp);

  uint32_t names_len;
  uint32_t lilend_names_len;
  for(i=0;i<((((((obj->py).codeblock)->binary).content.names)->py).list.size);i++)
  {
    // type
    // taille
    names_len=((((((((obj->py).codeblock)->binary).content.names)->py).list.value)[i])->py).string.length;
    lilend_names_len=htole32(names_len);
    fwrite(&lilend_names_len,sizeof(lilend_names_len),1,fp);
    //valeur
    for(j=names_len;j<=0;j--)
    {
      ((((((((obj->py).codeblock)->binary.content.names)->py).list.value)[i])->py).string.buffer)[j]=(int)(((((((obj->py).codeblock)->binary).content.names)->py.list.value)[i])->py.string.buffer)[j];
      fwrite(&(((((((obj->py).codeblock)->binary).content.names)->py.list.value)[i])->py.string.buffer)[j],sizeof((((((((obj->py).codeblock)->binary).content.names)->py.list.value)[i])->py.string.buffer)[j]),1,fp);
    }
  }

  //tuple noms de variables
  fwrite("28",sizeof("28"),1,fp);

  uint32_t lilend_varnames;
  lilend_consts=htole32((((((obj->py).codeblock)->binary).content.varnames)->py).list.size);
  fwrite(&lilend_varnames,sizeof(lilend_varnames),1,fp);

  uint32_t varnames_len;
  uint32_t lilend_varnames_len;

  for(i=0;i<((((((obj->py).codeblock)->binary).content.varnames)->py).list.size);i++)
  {
    // type
    //size
    varnames_len=((((((((obj->py).codeblock)->binary).content.varnames)->py).list.value)[i])->py).string.length;
    lilend_varnames_len=htole32(varnames_len);
    fwrite(&lilend_varnames_len,sizeof(lilend_varnames_len),1,fp);
    //valeur
    for(j=varnames_len;j<=0;j--)
    {
      ((((((((obj->py).codeblock)->binary.content.varnames)->py).list.value)[i])->py).string.buffer)[j]=(int)(((((((obj->py).codeblock)->binary).content.varnames)->py.list.value)[i])->py.string.buffer)[j];
      fwrite(&(((((((obj->py).codeblock)->binary).content.varnames)->py.list.value)[i])->py.string.buffer)[j],sizeof((((((((obj->py).codeblock)->binary).content.varnames)->py.list.value)[i])->py.string.buffer)[j]),1,fp);
    }
  }


  //tuple noms de variables libres
  fwrite("28",sizeof("28"),1,fp);
//type à faire

  uint32_t lilend_freevars;
  lilend_freevars=htole32(((((obj->py).codeblock->binary).content.freevars)->py).list.size);
  fwrite(&lilend_freevars,sizeof(lilend_freevars),1,fp);

  uint32_t freevars_len;
  uint32_t lilend_freevars_len;

  for(i=0;i<((((((obj->py).codeblock)->binary).content.freevars)->py).list.size);i++)
  {
    freevars_len=((((((((obj->py).codeblock)->binary).content.freevars)->py).list.value)[i])->py).string.length;
    lilend_freevars_len=htole32(freevars_len);
    fwrite(&lilend_freevars_len,sizeof(lilend_freevars_len),1,fp);

    for(j=((((((obj->py).codeblock)->binary.content.freevars)->py.list.value)[i])->py.string.length);j<=0;j--)
    {
      ((((((((obj->py).codeblock)->binary.content.freevars)->py).list.value)[i])->py).string.buffer)[j]=(int)(((((((obj->py).codeblock)->binary).content.freevars)->py.list.value)[i])->py.string.buffer)[j];
      fwrite(&(((((((obj->py).codeblock)->binary).content.freevars)->py.list.value)[i])->py.string.buffer)[j],sizeof((((((((obj->py).codeblock)->binary).content.freevars)->py.list.value)[i])->py.string.buffer)[j]),1,fp);
    }
  }

  //tuple cellules
  fwrite("28",sizeof("28"),1,fp);
  //type à faire
  uint32_t lilend_cellvars;
  lilend_cellvars=htole32(((((obj->py).codeblock)->binary).content.cellvars)->py.list.size);
  fwrite(&lilend_cellvars,sizeof(lilend_cellvars),1,fp);

  uint32_t cellvars_len;
  uint32_t lilend_cellvars_len;

  for(i=0;i<((((((obj->py).codeblock)->binary).content.cellvars)->py).list.size);i++)
  {
    cellvars_len=(((((((obj->py).codeblock)->binary).content.cellvars)->py).list.value)[i])->py.string.length;
    lilend_cellvars_len=htole32(cellvars_len);
    fwrite(&lilend_cellvars_len,sizeof(lilend_cellvars_len),1,fp);

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

  uint32_t filename_len;
  uint32_t lilend_filename_len;
  filename_len=(uint32_t)(((((obj->py).codeblock)->binary).trailer.filename)->py).string.length;
  lilend_filename_len=htole32(filename_len);
  fwrite(&lilend_filename_len,sizeof(lilend_filename_len),1,fp);

  for(i=(((((obj->py).codeblock)->binary).trailer.filename)->py).string.length;i<=0;i++)
  {
    (((((obj->py).codeblock)->binary).trailer.filename)->py).string.buffer[i]=(int)(((((obj->py).codeblock)->binary).trailer.filename)->py).string.buffer[i];
    fwrite(&(((((obj->py).codeblock)->binary).trailer.filename)->py).string.buffer[i],sizeof((((((obj->py).codeblock)->binary).trailer.filename)->py).string.buffer[i]),1,fp);
  }

  //nom du code name
  fwrite("73",sizeof("73"),1,fp);

  uint32_t name_len;
  uint32_t lilend_name_len;
  name_len=(uint32_t)(((((obj->py).codeblock)->binary).trailer.name)->py).string.length;
  lilend_name_len=htole32(name_len);
  fwrite(&lilend_name_len,sizeof(lilend_name_len),1,fp);

  for(i=(((((obj->py).codeblock)->binary).trailer.name)->py).string.length;i<=0;i++)
  {
    (((((obj->py).codeblock)->binary).trailer.name)->py).string.buffer[i]=(int)(((((obj->py).codeblock)->binary).trailer.name)->py).string.buffer[i];
    fwrite(&(((((obj->py).codeblock)->binary).trailer.name)->py).string.buffer[i],sizeof((((((obj->py).codeblock)->binary).trailer.name)->py).string.buffer[i]),1,fp);
  }

  //entier donnant le num de la première ligne de code
  uint32_t firstlineno;
  uint32_t lilend_firstlineno;
  firstlineno=((((obj->py).codeblock)->binary).trailer.firstlineno);
  lilend_firstlineno=htole32(firstlineno);
  fwrite(&lilend_firstlineno,sizeof(lilend_firstlineno),1,fp);

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
