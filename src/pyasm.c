#include <pyas/all.h>

// Littel endian pas fait!!
//Tests!!

/* Produira le bytecode (et la stockera dans un objet de code Python) et
lnotab à partir des informations extraites au livrable 2.
Elle retournera -1 en cas d’erreur et 0 sinon */
int pyasm( list_t list_lexems,pyobj_t code )
{
  //////////////////////////////////////////////
  // Fichier avec les Mnémoniques et Opcodes
  //printf("%s\n",((((code->py).codeblock)->binary.content.interned)->py.list.value[0])->py.string.buffer );
  //((((code->py).codeblock)->binary.content.interned)->py.list.value[0])=(pyobj_t)realloc(((((code->py).codeblock)->binary.content.interned)->py.list.value[0]),sizeof(struct pyobj));
//((((code->py).codeblock)->binary.content.interned)->py.list.value[0])->py.string.buffer="TABON";
  //printf("%s\n",((((code->py).codeblock)->binary.content.interned)->py.list.value[0])->py.string.buffer );
  //printf("YEEES\n" );
  FILE*file_r_txt;
  file_r_txt=fopen("mnémo_bin_correspondance.txt","r"); //ouverture du fichier avec les opcodes
  if(NULL==file_r_txt) {perror("Erreur ouverture lecture de mnémo_bin_correspondance.txt/n"); return -1;}
  //////////////////////////////////////////////
  list_t lexem_p=NULL;
  lexem_p=list_lexems;
  // Comptage du nombre de lignes du code Python
  int nb_lines;
  nb_lines=0;
  while(lexem_p->next!=NULL)
  {
    if(strcmp("dir::line",((struct lexem*)(lexem_p->content))->type)==0)
    {

      nb_lines++;
    }
    lexem_p=lexem_p->next;
  }


  lexem_p=list_lexems;
  //////////////////////////////////////////////
  // Pour le bytecode
  // Remplir le tableau de lignes, le delta bytecode et le bytecode --->char ou int?
  int num_lines[nb_lines];
  int*num_lines_p=NULL;
  num_lines_p=num_lines;

  int delta_bytecode[nb_lines];
  int*delta_bytecode_p=NULL;
  delta_bytecode_p=delta_bytecode;

  int delta_nb_lines[nb_lines];

  int lnotab_int[nb_lines];

  char bytecode[256];
  char*bytecode_p=NULL;
  bytecode_p=bytecode;

  while(!list_empty(list_next(lexem_p)))
  {
    if(strcmp(((struct lexem*)(lexem_p->content))->value,".line")==0)
    {
    while(strcmp("number::integer",((struct lexem*)(lexem_p->content))->type)!=0 && !list_empty(list_next(lexem_p)))
    {
        lexem_p=lexem_p->next;
      }
      *num_lines_p=atoi(((struct lexem*)(lexem_p->content))->value);//à transformer en int

      num_lines_p++;

      int nb_bytes_line;
      nb_bytes_line=0;

      char str1[30];
      char str2[30];
      while(strcmp("identifier",((struct lexem*)(lexem_p->content))->type)!=0 && !list_empty(list_next(lexem_p)))
      {
          lexem_p=lexem_p->next;
          if(strcmp("dir::line",((struct lexem*)(lexem_p->content))->type)==0){
                  break;
                }
        }
      while(strcmp("dir::line",((struct lexem*)(lexem_p->content))->type)!=0 && !list_empty(list_next(lexem_p)))
      {
      file_r_txt=fopen("mnémo_bin_correspondance.txt","r");
      int i;
      for (i = 0; i < 120; i++) {
        fscanf(file_r_txt,"%s",str1);
        fscanf(file_r_txt,"%s",str2);
        if(strcmp(((struct lexem*)(lexem_p->content))->value,str1)==0){
          break;
        }
      }
      fclose(file_r_txt);

        strcpy(bytecode_p,str2);
        bytecode_p=bytecode_p+strlen(str2);
        nb_bytes_line=nb_bytes_line+1;
        while(strcmp("number::integer",((struct lexem*)(lexem_p->content))->type)!=0  && !list_empty(list_next(lexem_p)))
        {
            lexem_p=lexem_p->next;
            if(strcmp("identifier",((struct lexem*)(lexem_p->content))->type)==0){
              break;
            }
            if(strcmp("dir::line",((struct lexem*)(lexem_p->content))->type)==0){
                    break;
                  }
          }
        if(strcmp("number::integer",((struct lexem*)(lexem_p->content))->type)==0)
        {  char str[9];
           strcpy (str,"0x0");
           strcat (str,(((struct lexem*)(lexem_p->content))->value));
           strcat (str,"0x00");
          strcpy(bytecode_p,str);
          bytecode_p=bytecode_p+strlen(str);
          nb_bytes_line=nb_bytes_line+3;
        }
        if(strcmp("dir::line",((struct lexem*)(lexem_p->content))->type)!=0){
        while(strcmp("identifier",((struct lexem*)(lexem_p->content))->type)!=0 && !list_empty(list_next(lexem_p)))
        {
            lexem_p=lexem_p->next;
            if(strcmp("dir::line",((struct lexem*)(lexem_p->content))->type)==0){
                    break;
                  }

          }
        }
      }

      *delta_bytecode_p=nb_bytes_line;
      delta_bytecode_p++;
    }


    if(strcmp("dir::line",((struct lexem*)(lexem_p->content))->type)!=0 && !list_empty(list_next(lexem_p))){
      lexem_p=lexem_p->next;
    }
  }

  //////////////////////////////////////////////
  // Stock bytecode dans l'objet Python mis en paramètre
  //char*p_bytecode=NULL;
  //p_bytecode=bytecode;



  (((code->py).codeblock)->binary.content.bytecode)=(pyobj_t)realloc((((code->py).codeblock)->binary.content.bytecode),sizeof(struct pyobj));
  (((code->py).codeblock)->binary.content.bytecode)->py.string.buffer=bytecode;
  (((code->py).codeblock)->binary.content.bytecode)->py.string.length=strlen(bytecode);
  //////////////////////////////////////////////
  // Pour lnotab
  /// Construire delta lignes
  int i;
  int j;
  for(i=0;i<nb_lines;i++)
  {
    delta_nb_lines[i]=num_lines[i]-num_lines[i-1];
  }
  /// Remplir lnotab
  for(j=0;j<nb_lines;j++)
  {
    if(j%2!=0)
    {
      lnotab_int[j]=delta_bytecode[j/2];
    }
    else
    {
      lnotab_int[j]=delta_nb_lines[(j-1)/2];
    }
  }
  //////////////////////////////////////////////
  // Stock bytecode dans l'objet Python mis en paramètre
  ///conversion du tableau de int en tableau de char
  char lnotab[nb_lines];
  int k;

  for(k=0;k<nb_lines;k++)
  {
    lnotab[k]=lnotab_int[k]+'0';
  }
  //char* p_lnotab=NULL;
  //p_lnotab=lnotab;

  (((code->py).codeblock)->binary.trailer.lnotab)=(pyobj_t)realloc((((code->py).codeblock)->binary.trailer.lnotab),sizeof(struct pyobj));
  (((code->py).codeblock)->binary.trailer.lnotab)->py.string.buffer=lnotab;
  (((code->py).codeblock)->binary.trailer.lnotab)->py.string.length=strlen(lnotab);
//fclose(file_r_txt);
return 0;
}
