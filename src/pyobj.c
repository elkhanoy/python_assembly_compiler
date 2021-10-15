#include <pyas/all.h>
// À partir d'une chaine de caractères, créer, allouer de la mémoire et retourner un type pyobj_t contenant cette chaine de caractères
pyobj_t pyobj_new_string(char *str){
	pyobj_t obj_string = calloc(1,sizeof(pyobj_t));
	obj_string->py.string.buffer = calloc(strlen(str),sizeof(char));
	strcpy(obj_string->py.string.buffer, str);
	obj_string->py.string.length = strlen(str);
	return obj_string;
}


// À partir d'une chaine de caractères, créer, allouer de la mémoire et retourner un type pyobj_t contenant cette chaine de caractères

pyobj_t pyobj_new_int(char *str){
	pyobj_t obj_int = calloc(1,sizeof(pyobj_t));
	sscanf(str, "%d", &obj_int->py.number.integer);
	return obj_int;
}

pyobj_t pyobj_new_float(char *str){
	pyobj_t obj_float = calloc(1,sizeof(*pyobj_t));
	sscanf(str, "%f", &obj_float->py.number.real);
	return obj_float;
}

pyobj_t pyobj_new_complex(char *str){
	pyobj_t obj_complex = calloc(1,sizeof(*pyobj_t));
	sscanf(str, "%f", &obj_complex->py.number.complex.real);
	sscanf(str, "%f", &obj_complex->py.number.complex.imag);
	return obj_complex;
}


pyobj_t pyobj_new_list(list_t list_obj_pyth){ // Une liste d'object python
	pyobj_t obj_list = calloc(1,sizeof(*pyobj_t));
	obj_list->py.list.size = list_length(list_obj_pyth);
	obj_list->py.list.value = calloc(obj_list->py.string.size,sizeof(obj_list->py.list.value));
	int k = 0;
	while(!(list_empty(list_obj_pyth))){
		obj_list->py.list.value[k] = list_first(list_obj_pyth);
		list_obj_pyth=list_obj_pyth->next;
		k++;
	}
	return obj_list;
}

pyobj_t pyobj_interned(list_t lexem_str){ // Une liste de valeurs de lexem reconnu dans interned strings

	queue_t objs_pyth = NULL;
	while(((lexem_t*)(lexem_peek(lexem_str)))->type=="string"){
		objs_pyth = enqueue(objs_pyth , pyobj_new_string(list_first(lexem_str)));
		lexem_str = list_next(lexem_str);
	}
	objs_pyth=queue_to_list(objs_pyth);

	pyobj_t obj_interned = pyobj_new_list(objs_pyth);
	return obj_interned;
}

pyobj_t pyobj_consts(list *lexem_str){ // Une liste de valeurs de lexem reconnu dans consts

	queue_t objs_pyth = NULL;
	while(((lexem_t*)(lexem_peek(lexem_str)))->type=="number::integer" || ((lexem_t*)(lexem_peek(lexem_str)))->type=="number::float"){
		if(((lexem_t*)(lexem_peek(lexem_str)))->type=="number::integer")
		{
			objs_pyth = enqueue(objs_pyth , pyobj_new_int(list_first(lexem_str)));
			lexem_str = list_next(lexem_str);
		}
		if(((lexem_t*)(lexem_peek(lexem_str)))->type=="number::float")
		{
			objs_pyth = enqueue(objs_pyth , pyobj_new_float(list_first(lexem_str)));
			lexem_str = list_next(lexem_str);
		}
	}
	objs_pyth=queue_to_list(objs_pyth);

	pyobj_t obj_const = pyobj_new_list(objs_pyth);
	return obj_const;
}

pyobj_t pyobj_names(list *lexem_str){ // Une liste de valeurs de lexem reconnu dans interned strings

		queue_t objs_pyth = NULL;
		while(((lexem_t*)(lexem_peek(lexem_str)))->type=="string"){
			objs_pyth = enqueue(objs_pyth , pyobj_new_string(list_first(lexem_str)));
			lexem_str = list_next(lexem_str);
		}
		objs_pyth=queue_to_list(objs_pyth);

		pyobj_t obj_name = pyobj_new_list(objs_pyth);
		return obj_name;
}


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
