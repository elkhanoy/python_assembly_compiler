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

  //tuple constantes
  fwrite("28",sizeof("28"),1,fp); //marqueur de interned
  uint32_t lilend_consts;
  lilend_consts=htole32(((((obj->py).codeblock)->content).consts)->list.size);
  fwrite(&lilend_consts,sizeof(lilend_consts),1,fp);

  int i;
  uint32_t consts_len;
  uint32_t lilend_consts_len;

  uint32_t consts_val;
  uint32_t lilend_consts_val;
  char ptr2;
  for(i=0;i<((((obj->py).codeblock)->content).consts)->list.size);i++)
  {
    consts_len=((((((obj->py).codeblock)->content).consts)->list.size)[i])->py.string.length;
    lilend_consts_len=htole32(consts_len);
    fwrite(&lilend_consts_len,sizeof(consts_len),1,fp);

    consts_val=strtoumax((((((((obj->py).codeblock)->content).consts)->list.size)[i])->py.string.buffer),&ptr1,16);
    lilend_consts_val=htole32(consts_val);
    fwrite(&lilend_consts_val,sizeof(lilend_consts_val),1,fp);
  }

  //tuple noms de symboles
  fwrite("28",sizeof("28"),1,fp);
  uint32_t lilend_names;
  lilend_consts=htole32(((((obj->py).codeblock)->content).names)->list.size);
  fwrite(&lilend_names,sizeof(lilend_names),1,fp);

  uint32_t names_val;
  uint32_t lilend_names_val;
  char ptr3;
  for(i=0;i<((((obj->py).codeblock)->content).names)->list.size);i++)
  {
    names_len=((((((obj->py).codeblock)->content).names)->list.size)[i])->py.string.length;
    lilend_names_len=htole32(names_len);
    fwrite(&lilend_names_len,sizeof(names_len),1,fp);

    names_val=strtoumax((((((((obj->py).codeblock)->content).names)->list.size)[i])->py.string.buffer),&ptr3,16);
    lilend_names_val=htole32(names_val);
    fwrite(&lilend_names_val,sizeof(lilend_names_val),1,fp);
  }

  //tuple noms de variables
  fwrite("28",sizeof("28"),1,fp);
  uint32_t lilend_varnames;
  lilend_consts=htole32(((((obj->py).codeblock)->content).varnames)->list.size);
  fwrite(&lilend_varnames,sizeof(lilend_varnames),1,fp);

  uint32_t varnames_val;
  uint32_t lilend_varnames_val;
  char ptr4;
  for(i=0;i<((((obj->py).codeblock)->content).varnames)->list.size);i++)
  {
    varnames_len=((((((obj->py).codeblock)->content).varnames)->list.size)[i])->py.string.length;
    lilend_varnames_len=htole32(varnames_len);
    fwrite(&lilend_varnames_len,sizeof(varnames_len),1,fp);

    varnames_val=strtoumax((((((((obj->py).codeblock)->content).varnames)->list.size)[i])->py.string.buffer),&ptr4,16);
    lilend_varnames_val=htole32(varnames_val);
    fwrite(&lilend_varnames_val,sizeof(lilend_varnames_val),1,fp);
  }


  //tuple noms de variables libres
  fwrite("28",sizeof("28"),1,fp);
  uint32_t lilend_freevars;
  lilend_consts=htole32(((((obj->py).codeblock)->content).freevars)->list.size);
  fwrite(&lilend_freevars,sizeof(lilend_freevars),1,fp);

  uint32_t freevars_val;
  uint32_t lilend_freevars_val;
  char ptr5;
  for(i=0;i<((((obj->py).codeblock)->content).freevars)->list.size);i++)
  {
    names_len=((((((obj->py).codeblock)->content).freevars)->list.size)[i])->py.string.length;
    lilend_freevars_len=htole32(freevars_len);
    fwrite(&lilend_freevars_len,sizeof(freevars_len),1,fp);

    freevars_val=strtoumax((((((((obj->py).codeblock)->content).freevars)->list.size)[i])->py.string.buffer),&ptr5,16);
    lilend_freevars_val=htole32(freevars_val);
    fwrite(&lilend_freevars_val,sizeof(lilend_freevars_val),1,fp);
  }

  //tuple cellules
  fwrite("28",sizeof("28"),1,fp);
  uint32_t lilend_cellvars;
  lilend_consts=htole32(((((obj->py).codeblock)->content).cellvars)->list.size);
  fwrite(&lilend_cellvars,sizeof(lilend_cellvars),1,fp);

  uint32_t cellvars_val;
  uint32_t lilend_cellvars_val;
  char ptr6;
  for(i=0;i<((((obj->py).codeblock)->content).cellvars)->list.size);i++)
  {
    cellvars_len=((((((obj->py).codeblock)->content).cellvars)->list.size)[i])->py.string.length;
    lilend_cellvars_len=htole32(cellvars_len);
    fwrite(&lilend_cellvars_len,sizeof(cellvars_len),1,fp);

    cellvars_val=strtoumax((((((((obj->py).codeblock)->content).cellvars)->list.size)[i])->py.string.buffer),&ptr6,16);
    lilend_cellvars_val=htole32(cellvars_val);
    fwrite(&lilend_cellvars_val,sizeof(lilend_cellvars_val),1,fp);
  }

  //////////////////////////////////////////////////////////////////////////
  /// Fin

  //nom du fichier source python filename
  fwrite("73",sizeof("73"),1,fp); //marqueur de string
  uint32_t filename_len;
  uint32_t lilend_filename_len;
  filename_len=((((obj->py).codeblock)->trailer).filename)->string.length;
  lilend_filename_len=htole32(filename_len);
  fwrite(&lilend_filename_len,sizeof(lilend_filename_len),1,fp);

  char*ptr;
  uint32_t filename;
  uint32_t lilend_filename;
  filename=strtoumax(((((obj->py).codeblock)->trailer).filename)->string.buffer,&ptr,16);
  lilend_filename=htole32(filename);
  fwrite(&lilend_filename,sizeof(lilend_filename),1,fp);

  //nom du code name
  fwrite("73",sizeof("73"),1,fp);
  uint32_t name_len;
  uint32_t lilend_name_len;
  name_len=((((obj->py).codeblock)->trailer).name)->string.length;
  lilend_name_len=htole32(filename_len);
  fwrite(&lilend_name_len,sizeof(lilend_name_len),1,fp);

  char*ptr;
  uint32_t name;
  uint32_t lilend_name;
  name=strtoumax(((((obj->py).codeblock)->trailer).filename)->string.buffer,&ptr,16);
  lilend_name=htole32(name);
  fwrite(&lilend_name,sizeof(lilend_name),1,fp);

  //entier donnant le num de la première ligne de code
  uint32_t firstlineno;
  uint32_t lilend_firstlineno;
  firstlineno=((((obj->py).codeblock)->trailer).firstlineno);
  lilend_firstlineno=htole32(firstlineno);
  fwrite(&lilend_firstlineno,sizeof(lilend_firstlineno),1,fp);

  //lnotab
  fwrite("73",sizeof("73"),1,fp);
  char*ptr1;
  uint32_t lnotab;
  uint32_t lilend_lnotab;
  lnotab=strtoumax(((((obj->py).codeblock)->trailer).lnotab)->string.buffer,&ptr1,16);
  lilend_lnotab=htole32(lnotab);
  fwrite(&lilend_lnotab,sizeof(lilend_lnotab),1,fp);


  fclose(fp);
  return 0;
}
