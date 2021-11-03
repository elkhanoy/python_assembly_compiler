#include <pyas/all.h>


list_t list_interned(list_t *lexem_list){
  // vérification qu'on se trouve au bon endroit
  if (!list_empty(*lexem_list) && lexem_type(list_first(*lexem_list), "dir::interned")){
    *lexem_list = list_del_first(*lexem_list, lexem_delete);
    parse_eol(lexem_list);
  }
  else{
    printf(".interned missing");
    return(NULL);
  }
  // création de la liste de pyobj
  list_t list_interned = list_new();
  while(!list_empty(*lexem_list) && !lexem_type(list_first(*lexem_list), "dir::consts")){
    pyobj_t obj = pyobj_new_string(((lexem_t)list_first(*lexem_list))->value);
    list_interned = list_add_first(list_interned, obj);
    *lexem_list = list_del_first(*lexem_list, lexem_delete);
    parse_eol(lexem_list);
  }
  return list_interned;
}



list_t list_consts(list_t *lexem_list){
  // vérification qu'on se trouve au bon endroit
  if (!list_empty(*lexem_list) && lexem_type(list_first(*lexem_list), "dir::consts")){
    *lexem_list = list_del_first(*lexem_list, lexem_delete);
    parse_eol(lexem_list);
  }
  else{
    printf(".consts missing");
    return(NULL);
  }
  // création de la liste de pyobj
  list_t list_consts = list_new();
  while(!list_empty(*lexem_list) && !lexem_type(list_first(*lexem_list), "dir::names")){
		if(lexem_type(list_first(*lexem_list),"string")){

		pyobj_t obj = pyobj_new_string(((lexem_t)list_first(*lexem_list))->value);
    list_consts = list_add_first(list_consts, obj);
    *lexem_list = list_del_first(*lexem_list, lexem_delete);
    parse_eol(lexem_list);
	}
	if(lexem_type(list_first(*lexem_list),"real")){

	pyobj_t obj = pyobj_new_float(((lexem_t)list_first(*lexem_list))->value);
	list_consts = list_add_first(list_consts, obj);
	*lexem_list = list_del_first(*lexem_list, lexem_delete);
	parse_eol(lexem_list);
}
if(lexem_type(list_first(*lexem_list),"integer")){

pyobj_t obj = pyobj_new_int(((lexem_t)list_first(*lexem_list))->value);
list_consts = list_add_first(list_consts, obj);
*lexem_list = list_del_first(*lexem_list, lexem_delete);
parse_eol(lexem_list);
}
if(lexem_type(list_first(*lexem_list),"pycst")){

pyobj_t obj = pyobj_new_pycst(((lexem_t)list_first(*lexem_list))->value);
list_consts = list_add_first(list_consts, obj);
*lexem_list = list_del_first(*lexem_list, lexem_delete);
parse_eol(lexem_list);
}

  }
  return list_consts;
}



list_t list_names(list_t *lexem_list){
  // vérification qu'on se trouve au bon endroit
  if (!list_empty(*lexem_list) && lexem_type(list_first(*lexem_list), "dir::names")){
    *lexem_list = list_del_first(*lexem_list, lexem_delete);
    parse_eol(lexem_list);
  }
  else{
    printf(".consts missing");
    return(NULL);
  }
  // création de la liste de pyobj
  list_t list_names = list_new();
  while(!list_empty(*lexem_list) && !lexem_type(list_first(*lexem_list), "dir::varnames") && !lexem_type(list_first(*lexem_list), "dir::freevars") && !lexem_type(list_first(*lexem_list), "dir::cellvars") && !lexem_type(list_first(*lexem_list), "dir::text")){
    pyobj_t obj = pyobj_new_string(((lexem_t)list_first(*lexem_list))->value);
    list_names = list_add_first(list_names, obj);
    *lexem_list = list_del_first(*lexem_list, lexem_delete);
    parse_eol(lexem_list);
  }
  return list_names;
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
	if(strcmp(str,"None")){
		obj_pycst->type=_NONE_;
	}
	if(strcmp(str,"NULL")){
		obj_pycst->type=_NULL_;
	}
	if(strcmp(str,"True")){
		obj_pycst->type=_TRUE_;
	}
	if(strcmp(str,"False")){
		obj_pycst->type=_FALSE_;
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




pyobj_t pyobj_interned(list_t *lexems){

//Allocation dynamique
	pyobj_t obj_interned = calloc(1,sizeof(pyobj_t));
	obj_interned->py.list.size = list_length(*lexems);
	obj_interned->py.list.value = calloc(obj_interned->py.list.size,sizeof(pyobj_t));

//Ajout dans value de interned le value de l'objet python présent dans la liste
	obj_interned->py.list.value = pyobj_new_list(*lexems)->py.list.value;

	obj_interned->type = _LIST_;


	return obj_interned;
}


pyobj_t pyobj_consts(list_t *list_obj_pyth){

		pyobj_t pyobj_consts = calloc(1,sizeof(pyobj_t));
		pyobj_consts->py.list.size = list_length(*list_obj_pyth);
		pyobj_consts->py.list.value = calloc(pyobj_consts->py.list.size,sizeof(pyobj_t));

		pyobj_consts->py.list.value = pyobj_new_list(*list_obj_pyth)->py.list.value;

		pyobj_consts->type = _LIST_;


		return pyobj_consts;
	}


pyobj_t pyobj_names(list_t *lexem_str){

	pyobj_t pyobj_names = calloc(1,sizeof(pyobj_t));
	pyobj_names->py.list.size = list_length(*lexem_str);
	pyobj_names->py.list.value = calloc(pyobj_names->py.list.size,sizeof(pyobj_t));

	pyobj_names->py.list.value = pyobj_new_list(*lexem_str)->py.list.value;

	pyobj_names->type = _LIST_;


	return pyobj_names;
	}



//remplissage du codeblock
codeblock fill_codeblock(pyobj_t interned,pyobj_t consts,pyobj_t names){
	codeblock py_code= calloc(1,sizeof(codeblock));


	// //En-tête de l'objet python

	// py_code.header.arg_count = ;
	// py_code.header.local_count = ;
	// py_code.header.stack_size = ;
	// py_code.header.flags = ;

	// Corps de l'objet python

	py_code->binary.content.interned = interned;
	py_code->binary.content.consts = consts;
	py_code->binary.content.names = names;

	// //Fin de l'objet python
	// py_code.trailer.filename = ;
	// py_code.trailer.name = ;
	// py_code.trailer.firstlineno = ;
	// py_code.trailer.lnotab = ;

	return py_code;
}



int construction_codeblock(list_t *liste_lexems){
	//remplissage interned
	while(!lexem_type(list_first(*liste_lexems),"dir::interned")){
		*liste_lexems=list_del_first(*liste_lexems,lexem_delete);
	}
  list_t inter_int=list_interned(liste_lexems);
	pyobj_t interned=pyobj_interned(&inter_int);

	//remplissage consts
  list_t inter_consts=list_consts(liste_lexems);
	pyobj_t consts=pyobj_consts(&inter_consts);

	//remplissage names
  list_t inter_names=list_names(liste_lexems);
	pyobj_t names=pyobj_names(&inter_names);

  //remplissage du codeblock
  fill_codeblock(interned,consts,names);


	return 0;

}
