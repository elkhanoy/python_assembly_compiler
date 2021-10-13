#include <pyas/all.h>

pyobj_t pyobj_new_string(char *str){
	pyobj_t obj_string = calloc(1,sizeof(pyobj_t));
	obj_string->py.string.buffer = calloc(strlen(str),sizeof(char));
	strcpy(obj_string->py.string.buffer, str);
	obj_string->py.string.length = strlen(str);
	return obj_string;
}



pyobj_t pyobj_new_int(char *str){
	pyobj_t obj_int = calloc(1,sizeof(pyobj_t));
	(int32_t)(obj_int->py.number.integer) = calloc(1,sizeof(int32_t));
	sscanf(str, "%d", &obj_int->py.number.integer);
	return obj_int;
}
/*
pyobj_t pyobj_new_float(char *str){
	pyobj_t obj_float = calloc(1,sizeof(*pyobj_t));
	obj_float->py.number = calloc(1,sizeof(obj_float->py.number));
	obj_float->py.number.real = calloc(1,sizeof(obj_float->py.number.real));
	sscanf(str, "%f", &obj_float->py.number.real);
	return obj_float;
}

pyobj_t pyobj_new_complex(char *str){
	pyobj_t obj_complex = calloc(1,sizeof(*pyobj_t));
	obj_complex->py.number = calloc(1,sizeof(obj_complex->py.number));
	obj_complex->py.number.complex = calloc(1,sizeof(obj_complex->py.number.complex));
	obj_complex->py.number.complex.real = calloc(1,sizeof(obj_complex->py.number.complex.real));
	obj_complex->py.number.complex.imag = calloc(1,sizeof(obj_complex->py.number.complex.imag));
	sscanf(str, "%f", &obj_complex->py.number.complex.real);
	sscanf(str, "%f", &obj_complex->py.number.complex.imag);
	return obj_complex;
}


pyobj_t pyobj_new_list(list_t *list_obj_pyth){ // Une liste d'object python
	pyobj_t obj_list = calloc(1,sizeof(*pyobj_t));
	obj_list->py.list = calloc(1,sizeof(obj_list->py.list));
	obj_list->py.list.size = calloc(1,sizeof(int));
	obj_list->py.list.size = list_length(*list_value);
	obj_list->py.list.value = calloc(obj_list->py.string.size,sizeof(obj_list->py.list.value));
	int k = 0;
	while(!(list_empty(*liste_lexems_string))){
		obj_list->py.list.value[k] = list_first(*list_obj_pyth);
		obj_list->py.list.value[k] = list_next(*list_obj_pyth);
		k = k+1;
	}
	return obj_list;
}

pyobj_t pyobj_interned(list *lexem_str){ // Une liste de valeurs de lexem reconnu dans interned strings

	pyobj_t obj_interned = calloc(1,sizeof(*pyobj_t));
	list_t objs_pyth = list_new();
	while(!(list_empty(*lexem_str))){
		objs_pyth = list_add_first(objs_pyth , pyobj_new_string(list_first(*lexem_str)));
		*lexem_str = list_next(*lexem_str);
	}

	obj_interned->py.list = pyobj_new_list(&objs_pyth);
	return obj_interned;
}

pyobj_t pyobj_consts(list *lexem_str){ // Une liste de valeurs de lexem reconnu dans consts
	pyobj_t obj_consts = calloc(1,sizeof(*pyobj_t));
	list_t objs_pyth = list_new();
	while(!(list_empty(*lexem_str))){

		objs_pyth = list_add_first(objs_pyth , pyobj_new_string(list_first(*lexem_str)));



		*lexem_str = list_next(*lexem_str);
	}
	obj_consts->py.list = pyobj_new_list(&objs_pyth);
	return obj_consts;
}

pyobj_t pyobj_names(list *lexem_str){ // Une liste de valeurs de lexem reconnu dans interned strings
	pyobj_t obj_names = calloc(1,sizeof(*pyobj_t));
	list_t objs_pyth = list_new();
	while(!(list_empty(*lexem_str))){
		objs_pyth = list_add_first(objs_pyth , pyobj_new_string(list_first(*lexem_str)));
		*lexem_str = list_next(*lexem_str);
	}
	obj_names->py.list = pyobj_new_list(&objs_pyth);
	return obj_names;
}
*/

/*pyobj_t pyobj_codeblock(****){
	pyobj_t obj_code = calloc(1,sizeof(*pyobj_t));
	obj_code->py.py_codeblock = calloc(1,sizeof(*obj_code->py.py_codeblock));

	//En-tête de l'objet python
	obj_code->py.py_codeblock.header = calloc(1,sizeof(*obj_code->py.py_codeblock.header));
	obj_code->py.py_codeblock.header.arg_count = ;
	obj_code->py.py_codeblock.header.local_count = ;
	obj_code->py.py_codeblock.header.stack_size = ;
	obj_code->py.py_codeblock.header.flags = ;

	// Corps de l'objet python
	obj_code->py.py_codeblock.binary = calloc(1,sizeof(*obj_code->py.py_codeblock.binary));
	obj_code->py.py_codeblock.binary.content = calloc(1,sizeof(*obj_code->py.py_codeblock.binary.content));
	obj_code->py.py_codeblock.binary.content.interned = pyobj_interned(*****);
	obj_code->py.py_codeblock.binary.content.consts = pyobj_consts(*****);
	obj_code->py.py_codeblock.binary.content.interned = pyobj_names(*****);

	//Fin de l'objet python
	obj_code->py.py_codeblock.trailer = calloc(1,sizeof(*obj_code->py.py_codeblock.trailer));
	obj_code->py.py_codeblock.trailer.filename = ;
	obj_code->py.py_codeblock.trailer.name = ;
	obj_code->py.py_codeblock.trailer.firstlineno = ;
	obj_code->py.py_codeblock.trailer.lnotab = ;

	return obj_code;
}
*/
