
typedef enum {
  ONE_OR_ZERO,
  ONE_OR_MORE,
  ZERO_OR_MORE,
  EXACTLY_ONE
} occurence_t;

typedef struct char_group{
  char group[256];
  occurence_t occurence;
} char_group_t;


int check_backslash(char* regexp);
occurence_t set_occurence(char*regexp,char_group_t * mini_regexp);
char_group_t *new_queue_char_group(char_group_t * mini_regexp, char* bool);
queue_t split_regexp(char* regexp, queue_t * list_char);
