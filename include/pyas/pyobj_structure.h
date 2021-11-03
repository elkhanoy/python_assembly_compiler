

typedef unsigned int pyobj_type;

struct pyobj_t ;
typedef struct pyobj * pyobj_t ;

typedef struct py_codeblock *codeblock;



struct pyobj {
  pyobj_type type ;
  unsigned int refcount ;
  union {
    struct {
      pyobj_t * value ;
      int32_t size ;
    } list ;

    struct {
      char * buffer ;
      int length ;
    } string ;
    struct py_codeblock * codeblock ;

    union {
      int32_t integer ;
      int64_t integer64 ;
      double real ;
      struct {
        double real ;
        double imag ;
      } complex ;
    } number ;
  } py;
};

struct py_codeblock {
  int version_pyvm ;
  struct {
    int32_t arg_count ;
    uint32_t local_count ;
    uint32_t stack_size ;
    uint32_t flags ;
  } header ;
  pyobj_t parent ;
  struct {
    struct {
      uint32_t magic ;
      time_t timestamp ;
      uint32_t source_size ;
    } header ;
    struct {
      pyobj_t interned ;
      pyobj_t bytecode ;
      pyobj_t consts ;
      pyobj_t names ;
      pyobj_t varnames ;
      pyobj_t freevars ;
      pyobj_t cellvars ;
    } content ;
    struct {
      pyobj_t filename ;
      pyobj_t name ;
      uint32_t firstlineno ;
      pyobj_t lnotab ;
    } trailer ;
  } binary ;
};



////////////////////////////////////
list_t list_interned(list_t *lexem_list);
list_t list_consts(list_t *lexem_list);
list_t list_names(list_t *lexem_list);

pyobj_t pyobj_new_string(char *str);
pyobj_t pyobj_new_int(char *str);
pyobj_t pyobj_new_float(char *str);
pyobj_t pyobj_new_list(list_t list_obj_pyth);
pyobj_t pyobj_new_pycst(char *str);

pyobj_t pyobj_interned(list_t *lexems);
pyobj_t pyobj_consts(list_t *list_obj_pyth);
pyobj_t pyobj_names(list_t *lexem_str);

codeblock fill_codeblock(pyobj_t interned,pyobj_t consts,pyobj_t names);

int construction_codeblock(list_t *liste_lexems);
////////////////////////////////////
