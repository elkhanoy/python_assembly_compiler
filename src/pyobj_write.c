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

  //CODE??? 63?

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
  ////écriture du nombre en lui même

  //tuple noms de symboles
  fwrite("28",sizeof("28"),1,fp);
  uint32_t lilend_names;
  lilend_consts=htole32(((((obj->py).codeblock)->content).names)->list.size);
  fwrite(&lilend_names,sizeof(lilend_names),1,fp);
  ////écriture du nombre en lui même

  //tuple noms de variables
  fwrite("28",sizeof("28"),1,fp);
  uint32_t lilend_varnames;
  lilend_consts=htole32(((((obj->py).codeblock)->content).varnames)->list.size);
  fwrite(&lilend_varnames,sizeof(lilend_varnames),1,fp);
  ////écriture du nombre en lui même


  //tuple noms de variables libres
  fwrite("28",sizeof("28"),1,fp);
  uint32_t lilend_freevars;
  lilend_consts=htole32(((((obj->py).codeblock)->content).lilend_freevars)->list.size);
  fwrite(&lilend_freevars,sizeof(lilend_freevars),1,fp);
  ////écriture du nombre en lui même

  //tuple cellules
  fwrite("28",sizeof("28"),1,fp);
  uint32_t lilend_cellvars;
  lilend_consts=htole32(((((obj->py).codeblock)->content).lilend_cellvars)->list.size);
  fwrite(&lilend_cellvars,sizeof(lilend_cellvars),1,fp);
  ////écriture du nombre en lui même

  //////////////////////////////////////////////////////////////////////////
  /// Fin

  //nom du fichier source python
  fwrite("73",sizeof("73"),1,fp); //marqueur de string

  fwrite()

  //nom du code
  fwrite("73",sizeof("73"),1,fp);

  //entier donnant le num de la première ligne de code
  

  //lnotab
  fwrite("73",sizeof("73"),1,fp);


fclose(fp);
return 0;
}
