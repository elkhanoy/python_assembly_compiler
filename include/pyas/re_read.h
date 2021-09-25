
typedef enum {false=0, true=1} bool;

typedef enum {
  ONE_OR_ZERO,
  ONE_OR_MORE,
  ZERO_OR_MORE,
  EXACTLY_ONE
} occurence_t;

typedef struct char_group{
  bool group[256];
  occurence_t occurence;
} char_group_t;


void set_occurence(char*regexp,char_group_t * subgroup);
void ini_char_group(char_group_t * mini_regexp, bool booleen);
queue_t re_read(char* regexp);
