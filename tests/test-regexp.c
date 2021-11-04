#include <pyas/all.h>

int main(int argc,char*argv[]) //La source et la regexp en chaine de caractères
{
  if(argc<2 && argc>3) //Le nombre de paramètres ajoutés doit être de 1 ou 2
  {
    printf("Entrez au moins un et au plus 2 paramètres\n");
    exit(EXIT_FAILURE);
  }
  if(argc==2){
    queue_t regexp_queue=NULL;
    queue_t debut_rgq=NULL;
    char regexp[80]; //Nom du fichier source
    char *rxp_stock=NULL;
    rxp_stock=calloc(256,sizeof(*rxp_stock));
    char *times;
    char int_char[2];
    strcpy(regexp,argv[1]); //Copie du nom du fichier source pris en paramètre lors de la compilation, dans le tableau
    regexp_queue=re_read(regexp,regexp_queue);
    regexp_queue=queue_to_list(regexp_queue);
    debut_rgq=regexp_queue;
    while(regexp_queue){
      memset(rxp_stock,0,256);
      int i;
      for(i=0;i<256;i++){
        if(((char_group_t*)(regexp_queue)->content)->group[i]){
          sprintf(int_char,"%c",i);
          strcat(rxp_stock,int_char);
        }
      }
      switch(((char_group_t*)(regexp_queue)->content)->occurence){
        case ONE_OR_ZERO:
          times=strdup("zero or one time");
          break;
        case ONE_OR_MORE:
          times=strdup("one or more times");
          break;
        case ZERO_OR_MORE:
          times=strdup("zero or more times");
          break;
        case EXACTLY_ONE:
          times=strdup("one time");
          break;
      }
      printf("One in \"%s\", %s.\n",rxp_stock,times);
      free(times);
      regexp_queue=(regexp_queue)->next;
    }
    free(rxp_stock);
    regexp_queue=debut_rgq;
    list_delete(regexp_queue,char_group_delete);
    return 1;
  }
  else{
    char ** end=NULL;
    end=calloc(1,sizeof(*end));
    *end=NULL;
    char source[80]; //Nom du fichier de configuration
    char regexp[80]; //Nom du fichier source
    strcpy(source,argv[2]); //Copie du nom du fichier de configuration pris en paramètre lors de la compilation, dans le tableau
    strcpy(regexp,argv[1]); //Copie du nom du fichier source pris en paramètre lors de la compilation, dans le tableau
    queue_t regexp_queue=NULL;
    queue_t debut_rgq=NULL;
    regexp_queue=re_read(regexp,regexp_queue);
    regexp_queue=queue_to_list(regexp_queue);
    debut_rgq=regexp_queue;
    if(re_match(regexp_queue,source,end)){
      if(**end=='\0'){
        printf("The start of '%s' is %s, END: ''.\n",source,regexp);
      }
      else{
        printf("The start of '%s' is %s, next: '%s'.\n",source,regexp,*end);
      }
    }
    else{
      printf("The start of '%s' is *NOT* %s.\n",source,regexp);
    }
    free(end);
    regexp_queue=debut_rgq;
    list_delete(regexp_queue,char_group_delete);
    return 1;
  }

}
