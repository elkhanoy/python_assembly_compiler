#include <pyas/all.h>


// Fonction pour lire la section text du fichier assembleur et remplir
// une liste de mnémoniques

list_txt_t text_section_list(FILE*file_conf,list_txt_t liste_section_text,list_txt_t list)
{
  file_r_txt=fopen("assembleur.conf","r"); //ouverture du fichier avec les opcodes
  if(NULL==file_r_txt) perror("Erreur ouverture lecture de assembleur.conf/n");

  char str[256];
// Recherche de la section .text dans le fichier assembleur
  while(strcmp(fgets())!=0)
  {
    fprintf("section .text non trouvée on avance dans le fichier/n");
  }

  while(fgetc(file_conf)!=EOF)
  {
    fseek(file_conf,-1,SEEK_SET);

    char str[30];
    int nb;


    if(fscanf(file_conf,"%s,%d",str,&nb)==2)
    {
      if(strcmp('.',str[0])==0) // Entrée dans une section ligne
      {
        int linenostock;
        *linenostock=nb
        fscanf(file_conf,"%s,%d",str,&nb)

        l=enqueue(l);
        l->lineno=*linenostock;
        l->mnemo=str;
        l->nb_param=nb;
      }

      else
      {
        l=enqueue(l);
        l->lineno=*linenostock;
        l->mnemo=str;
        l->nb_param=nb;
      }
    }

    else
    {
      l=enqueue(l);
      l->lineno=*linenostock;
      l->mnemo=str;
      l->nb_param=-1;
    }
  }

fclose(file_conf);

return l;
}
