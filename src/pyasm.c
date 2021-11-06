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
    if(strcmp(((struct lexem*)(lexem_p->content))->value,".line")==0)
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

  while(lexem_p->next!=NULL)
  {
    if(strcmp(((struct lexem*)(lexem_p->content))->value,".line")==0)
    {
      lexem_p=lexem_p->next;
      *num_lines_p=atoi(((struct lexem*)(lexem_p->content))->value);//à transformer en int
      num_lines_p++;
      lexem_p=lexem_p->next;

      int nb_bytes_line;
      nb_bytes_line=0;

      char str1[30];
      char str2[30];

      while(strcmp(((struct lexem*)(lexem_p->content))->value,".line")!=0)
      {
        do
        {fscanf(file_r_txt,"%s,%s",str1,str2);
      } while(strcmp(((struct lexem*)(lexem_p->content))->value,str1)!=0);
        strcpy(bytecode_p,str2);
        bytecode_p=bytecode_p+strlen(str2);
        nb_bytes_line=nb_bytes_line+1;

        lexem_p=lexem_p->next;
        if(strcmp(((struct lexem*)(lexem_p->content))->type,"int")==0)
        {
          *bytecode_p=*(((struct lexem*)(lexem_p->content))->value);
          bytecode_p=bytecode_p+strlen(((struct lexem*)(lexem_p->content))->value);
          nb_bytes_line=nb_bytes_line+3;
        }
      }
      *delta_bytecode_p=nb_bytes_line;
      delta_bytecode_p++;
    }
  }
  //////////////////////////////////////////////
  // Stock bytecode dans l'objet Python mis en paramètre
  ((((code->py).codeblock)->binary).content.bytecode)->py.string.buffer=bytecode;

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
  ((((code->py).codeblock)->binary).trailer.lnotab)->py.string.buffer=lnotab;

fclose(file_r_txt);
return 0;
}
