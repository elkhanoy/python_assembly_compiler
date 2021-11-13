#include <pyas/all.h>


list_t list_interned(list_t *lexem_list){
  // vérification qu'on se trouve au bon endroit
  if (!list_empty(*lexem_list) && lexem_type(list_first(*lexem_list), "dir::interned")){
    *lexem_list = list_del_first(*lexem_list, lexem_delete);
    while(lexem_type(list_first(*lexem_list), "blank")||lexem_type(list_first(*lexem_list), "newline")){
      *lexem_list=list_del_first(*lexem_list, lexem_delete);
    }
  }
  else{
    printf(".interned is missing");
    return(NULL);
  }
  // création de la liste de pyobj
  list_t list_interned = list_new();
  while(!list_empty(*lexem_list) && !lexem_type(list_first(*lexem_list), "dir::consts")){
    pyobj_t obj = pyobj_new_string(((lexem_t)list_first(*lexem_list))->value);
    list_interned = list_add_first(list_interned, obj);
    *lexem_list = list_del_first(*lexem_list, lexem_delete);
    while(lexem_type(list_first(*lexem_list), "blank")||lexem_type(list_first(*lexem_list), "newline")){
  *lexem_list=list_del_first(*lexem_list, lexem_delete);}
  }
  return list_invers(list_interned);
}



list_t list_consts(list_t *lexem_list){
  // vérification qu'on se trouve au bon endroit
  if (!list_empty(*lexem_list) && lexem_type(list_first(*lexem_list), "dir::consts")){
    *lexem_list = list_del_first(*lexem_list, lexem_delete);
    while(lexem_type(list_first(*lexem_list), "blank")||lexem_type(list_first(*lexem_list), "newline")){
  *lexem_list=list_del_first(*lexem_list, lexem_delete);}
  }
  else{
    printf(".consts is missing");
    return(NULL);
  }

  // création de la liste de pyobj
  list_t list_consts = list_new();
  while(!list_empty(*lexem_list) && !lexem_type(list_first(*lexem_list), "dir::names")){
		if(lexem_type(list_first(*lexem_list),"string")){
		pyobj_t obj = pyobj_new_string(((lexem_t)list_first(*lexem_list))->value);
    list_consts = list_add_first(list_consts, obj);
    *lexem_list = list_del_first(*lexem_list, lexem_delete);
    while(lexem_type(list_first(*lexem_list), "blank")||lexem_type(list_first(*lexem_list), "newline")){
     *lexem_list=list_del_first(*lexem_list, lexem_delete);}
   }

  if(lexem_type(list_first(*lexem_list),"number::float")){
	pyobj_t obj = pyobj_new_float(((lexem_t)list_first(*lexem_list))->value);
	list_consts = list_add_first(list_consts, obj);
	*lexem_list = list_del_first(*lexem_list, lexem_delete);
	while(lexem_type(list_first(*lexem_list), "blank")||lexem_type(list_first(*lexem_list), "newline")){
  *lexem_list=list_del_first(*lexem_list, lexem_delete);}
}

if(lexem_type(list_first(*lexem_list),"number::integer")){
pyobj_t obj = pyobj_new_int(((lexem_t)list_first(*lexem_list))->value);
list_consts = list_add_first(list_consts, obj);
*lexem_list = list_del_first(*lexem_list, lexem_delete);
while(lexem_type(list_first(*lexem_list), "blank")||lexem_type(list_first(*lexem_list), "newline")){
  *lexem_list=list_del_first(*lexem_list, lexem_delete);}
}
if(lexem_type(list_first(*lexem_list),"none")||lexem_type(list_first(*lexem_list),"null")||lexem_type(list_first(*lexem_list),"true")||lexem_type(list_first(*lexem_list),"false")){
pyobj_t obj = pyobj_new_pycst(((lexem_t)list_first(*lexem_list))->value);
list_consts = list_add_first(list_consts, obj);
*lexem_list = list_del_first(*lexem_list, lexem_delete);
while(lexem_type(list_first(*lexem_list), "blank")||lexem_type(list_first(*lexem_list), "newline")){
  *lexem_list=list_del_first(*lexem_list, lexem_delete);}
}

  }
  return list_invers(list_consts);
}



list_t list_names(list_t *lexem_list){
  // vérification qu'on se trouve au bon endroit
  if (!list_empty(*lexem_list) && lexem_type(list_first(*lexem_list), "dir::names")){
    *lexem_list = list_del_first(*lexem_list, lexem_delete);
    while(lexem_type(list_first(*lexem_list), "blank")||lexem_type(list_first(*lexem_list), "newline")){
  *lexem_list=list_del_first(*lexem_list, lexem_delete);}
  }
  else{
    printf(".names is missing");
    return(NULL);
  }
  // création de la liste de pyobj
  list_t list_names = list_new();
  while(!list_empty(*lexem_list) && !lexem_type(list_first(*lexem_list), "dir::varnames") && !lexem_type(list_first(*lexem_list), "dir::freevars") && !lexem_type(list_first(*lexem_list), "dir::cellvars") && !lexem_type(list_first(*lexem_list), "dir::text")){
    pyobj_t obj = pyobj_new_string(((lexem_t)list_first(*lexem_list))->value);
    list_names = list_add_first(list_names, obj);
    *lexem_list = list_del_first(*lexem_list, lexem_delete);
    while(lexem_type(list_first(*lexem_list), "blank")||lexem_type(list_first(*lexem_list), "newline")){
      *lexem_list=list_del_first(*lexem_list, lexem_delete);}
  }
  return list_invers(list_names);
}



// À partir d'une chaine de caractères, créer, allouer de la mémoire et retourner un type pyobj_t contenant cette chaine de caractères
pyobj_t pyobj_new_string(char *str){

//Allocation dynamique
	pyobj_t obj_string = calloc(1,sizeof(pyobj_t));
	obj_string->py.string.buffer = calloc(strlen(str),sizeof(char));

//Ajout de la chaîne de caractères
	strcpy(obj_string->py.string.buffer , str);
	obj_string->py.string.length = strlen(str);
	obj_string->type = _STRING_;

	return obj_string;
}

// À partir d'une chaine de caractères, créer, allouer de la mémoire et retourner un type pyobj_t contenant cette chaine de caractères

pyobj_t pyobj_new_int(char *str){
	pyobj_t obj_int=calloc(1,sizeof(pyobj_t));
	sscanf(str, "%d", &obj_int->py.number.integer);
	obj_int->type= _INTEGER_;
	return obj_int;
}

pyobj_t pyobj_new_float(char *str){
	pyobj_t obj_float=calloc(1,sizeof(pyobj_t));
	sscanf(str, "%lf", &obj_float->py.number.real);
	obj_float->type=_FLOAT_;
	return obj_float;
}

pyobj_t pyobj_new_pycst(char *str){
	pyobj_t obj_pycst=calloc(1,sizeof(pyobj_t));

	if(strcmp(str,"null")==0){
		obj_pycst->type=_NULL_;
	}
	if(strcmp(str,"True")==0){
		obj_pycst->type=_TRUE_;
	}

	if(strcmp(str,"Fulse")==0){
		obj_pycst->type=_FALSE_;
	}
  if(strcmp(str,"None")==0){
		obj_pycst->type=_NONE_;
	}
	return obj_pycst;
}

/*pyobj_t pyobj_new_complex(char *str){

	sscanf(str, "%lf", &obj_complex->py.number.complex.real);
	sscanf(str, "%lf", &obj_complex->py.number.complex.imag);
	return obj_complex;
}
*/

pyobj_t pyobj_new_list(list_t list_obj_pyth){
	pyobj_t obj_list = calloc(1,sizeof(pyobj_t));
	obj_list->py.list.size = list_length(list_obj_pyth);
	obj_list->py.list.value = calloc(obj_list->py.list.size,sizeof(obj_list->py.list.value));
	int k = 0;
	while(!(list_empty(list_obj_pyth))){
		obj_list->py.list.value[k] = list_first(list_obj_pyth);
		list_obj_pyth=list_obj_pyth->next;
		k++;
	}
	obj_list->type=_LIST_;
	return obj_list;
}


pyobj_t pyobj_interned(list_t list_obj_pyth){

//Allocation dynamique
	pyobj_t pyobj_interned = calloc(1,sizeof(pyobj_t));
	pyobj_interned->py.list.size = list_length(list_obj_pyth);
	pyobj_interned->py.list.value = calloc(pyobj_interned->py.list.size,sizeof(pyobj_t));

//Ajout dans value de interned le value de l'objet python présent dans la liste
	pyobj_interned->py.list.value = pyobj_new_list(list_obj_pyth)->py.list.value;

	pyobj_interned->type = _LIST_;


	return pyobj_interned;
}


pyobj_t pyobj_consts(list_t list_obj_pyth){

		pyobj_t pyobj_consts = calloc(1,sizeof(pyobj_t));
		pyobj_consts->py.list.size = list_length(list_obj_pyth);
		pyobj_consts->py.list.value = calloc(pyobj_consts->py.list.size,sizeof(pyobj_t));

		pyobj_consts->py.list.value = pyobj_new_list(list_obj_pyth)->py.list.value;

		pyobj_consts->type = _LIST_;


		return pyobj_consts;
	}


pyobj_t pyobj_names(list_t list_obj_pyth){

	pyobj_t pyobj_names = calloc(1,sizeof(pyobj_t));
	pyobj_names->py.list.size = list_length(list_obj_pyth);
	pyobj_names->py.list.value = calloc(pyobj_names->py.list.size,sizeof(pyobj_t));

	pyobj_names->py.list.value = pyobj_new_list(list_obj_pyth)->py.list.value;

	pyobj_names->type = _LIST_;


	return pyobj_names;
	}



//remplissage du codeblock
codeblock fill_codeblock(pyobj_t interned,pyobj_t consts,pyobj_t names,int version_pyvm,uint32_t flags,pyobj_t filename,pyobj_t name,uint32_t stack_size,uint32_t arg_count){
	codeblock py_code= calloc(1,sizeof(codeblock));


	// //En-tête de l'objet python
  py_code->version_pyvm=version_pyvm;
	py_code->header.arg_count = arg_count;
	py_code->header.local_count = 0;
	py_code->header.stack_size = stack_size;
	py_code->header.flags = flags;

	// Corps de l'objet python
  py_code->binary.header.magic=2573;
  py_code->binary.header.timestamp=time(NULL);
  py_code->binary.header.source_size=0;

	py_code->binary.content.interned = interned;
	py_code->binary.content.consts = consts;
	py_code->binary.content.names = names;

	py_code->binary.trailer.filename =filename ;
	py_code->binary.trailer.name = name;
	py_code->binary.trailer.firstlineno = 1;


	return py_code;
}



codeblock construction_codeblock(list_t *liste_lexems){
  //remplissage En-tête
  while(!lexem_type(list_first(*liste_lexems),"number::integer")){
		*liste_lexems=list_del_first(*liste_lexems,lexem_delete);
	}
  int version_pyvm;
  sscanf((((lexem_t)list_first(*liste_lexems))->value),"%d",&version_pyvm);

  while(!lexem_type(list_first(*liste_lexems),"number::hex")){
		*liste_lexems=list_del_first(*liste_lexems,lexem_delete);
	}
  uint32_t flags;
  sscanf((((lexem_t)list_first(*liste_lexems))->value),"%x",&flags);

  while(!lexem_type(list_first(*liste_lexems),"string")){
		*liste_lexems=list_del_first(*liste_lexems,lexem_delete);
	}
  pyobj_t filename;
  filename=pyobj_new_string(((lexem_t)list_first(*liste_lexems))->value);

  while(!lexem_type(list_first(*liste_lexems),"name")){
		*liste_lexems=list_del_first(*liste_lexems,lexem_delete);
	}
  pyobj_t name;
  name=pyobj_new_string(((lexem_t)list_first(*liste_lexems))->value);

  while(!lexem_type(list_first(*liste_lexems),"number::integer")){
		*liste_lexems=list_del_first(*liste_lexems,lexem_delete);
	}
  uint32_t stack_size;
  sscanf((((lexem_t)list_first(*liste_lexems))->value),"%d",&stack_size);
  *liste_lexems=list_del_first(*liste_lexems,lexem_delete);

  while((!lexem_type(list_first(*liste_lexems),"number::integer") && !lexem_type(list_first(*liste_lexems),"dir::interned"))){
		*liste_lexems=list_del_first(*liste_lexems,lexem_delete);
  }

  uint32_t arg_count=0;
  if(lexem_type(list_first(*liste_lexems),"number::integer")){
    sscanf((((lexem_t)list_first(*liste_lexems))->value),"%d",&arg_count);
  }


	//remplissage interned
	while(!lexem_type(list_first(*liste_lexems),"dir::interned")){
		*liste_lexems=list_del_first(*liste_lexems,lexem_delete);
	}
  list_t inter_int=list_interned(liste_lexems);
  pyobj_t interned=pyobj_interned(inter_int);

	//remplissage consts
  list_t inter_consts=list_consts(liste_lexems);
  pyobj_t consts=pyobj_consts(inter_consts);

	//remplissage names
  list_t inter_names=list_names(liste_lexems);
	pyobj_t names=calloc(1,sizeof(pyobj_t));
  names=(pyobj_t)realloc(pyobj_names(inter_names),sizeof(pyobj_t));

  //remplissage du codeblock
   codeblock py_code=fill_codeblock(interned, consts,names, version_pyvm,flags, filename, name, stack_size, arg_count);

   return py_code;

}

pyobj_t construction_pyobj(list_t *liste_lexems){
  pyobj_t pyobj = calloc(1,sizeof(pyobj_t));
  codeblock py_code;
  py_code=construction_codeblock(liste_lexems);
  pyobj->py.codeblock=py_code;
  return pyobj;
}

int affichage_pyobj(pyobj_t code){
  printf("version_pyvm %d\n",((code->py).codeblock)->version_pyvm);
  printf("flags %08x\n", ((code->py).codeblock)->header.flags);
  printf("filename %s\n", (((code->py).codeblock)->binary.trailer.filename)->py.string.buffer);
  printf("name %s\n", (((code->py).codeblock)->binary.trailer.name)->py.string.buffer);
  printf("stack_size %d\n",((code->py).codeblock)->header.stack_size);
  printf("arg_count %d\n",((code->py).codeblock)->header.arg_count);
  printf("timestamp %ld\n",((code->py).codeblock)->binary.header.timestamp);
  printf("magic %d\n",((code->py).codeblock)->binary.header.magic);
  printf("firstlineno %d\n", (((code->py).codeblock)->binary.trailer.firstlineno));
  int in;
  in=(((code->py).codeblock)->binary.content.interned)->py.list.size;
  printf("interned contient %d elements\n", in);
  int i;
  for (i=0;i<in;i++){
    printf("%s\n",((((code->py).codeblock)->binary.content.interned)->py.list.value[i])->py.string.buffer );
    printf("de langeur %d\n",((((code->py).codeblock)->binary.content.interned)->py.list.value[i])->py.string.length );
  }

  int co;
  co=(((code->py).codeblock)->binary.content.consts)->py.list.size;
  printf("consts contient %d elements\n", co);
  for (i=0;i<co;i++){
    if(((((code->py).codeblock)->binary.content.consts)->py.list.value[i])->type==_STRING_){
    printf("%s\n",((((code->py).codeblock)->binary.content.consts)->py.list.value[i])->py.string.buffer );
    printf("de langeur %d\n",((((code->py).codeblock)->binary.content.consts)->py.list.value[i])->py.string.length );
    }

    if(((((code->py).codeblock)->binary.content.consts)->py.list.value[i])->type==_INTEGER_){
    printf("%d\n",((((code->py).codeblock)->binary.content.consts)->py.list.value[i])->py.number.integer );
     }
    if(((((code->py).codeblock)->binary.content.consts)->py.list.value[i])->type==_FLOAT_){
     printf("%f\n",((((code->py).codeblock)->binary.content.consts)->py.list.value[i])->py.number.real );
   }


    if(((((code->py).codeblock)->binary.content.consts)->py.list.value[i])->type==_NULL_){
      printf("Null\n");
    }
    if(((((code->py).codeblock)->binary.content.consts)->py.list.value[i])->type==_TRUE_){
      printf("True\n");
    }
    if(((((code->py).codeblock)->binary.content.consts)->py.list.value[i])->type==_FALSE_){
      printf("False\n");
    }
    if(((((code->py).codeblock)->binary.content.consts)->py.list.value[i])->type==_NONE_){
      printf("None\n");
    }
  }

  int na;
  na=(((code->py).codeblock)->binary.content.names)->py.list.size;
  printf("names contient %d elements\n", na);
  for (i=0;i<na;i++){
    printf("%s\n",((((code->py).codeblock)->binary.content.names)->py.list.value[i])->py.string.buffer );
    printf("de langeur %d\n",((((code->py).codeblock)->binary.content.names)->py.list.value[i])->py.string.length );
  }
  return 0;
}
