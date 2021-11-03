#include <pyas/all.h>


// Fonction pour lire la section text du fichier assembleur et remplir
// une liste de mnémoniques

list_txt_t text_section_list(FILE*file_conf,list_txt_t list_section_text)
{
  file_conf=fopen("assembleur.conf","r"); //ouverture du fichier avec les opcodes
  if(NULL==file_conf) perror("Erreur ouverture lecture de assembleur.conf/n");

  char str[256];

////////////////////////////////////////////////////////////////////////// Recherche de la section .text dans le fichier assembleur
  while(strcmp(fgets(str,file_conf),".text")!=0)
  {
    fprintf("section .text non trouvée on avance dans le fichier/n");
  }

///////////////////////////////////////////////////////////////////// Dans la section .text:

  while(fgetc(file_conf)!=EOF)
  {
    fseek(file_conf,-1,SEEK_SET); // Pour revenir en arrière apès fgetc

    char str1[30];
    int nb;


    if(fscanf(file_conf,"%s,%d",str1,&nb)==2) // On lit soit une nouvelle ligne soit une mnemo
    {
      if(strcmp('.',str1[0])==0) // Il s'agit d'une section ligne
      {
        int*linenostock;
        *linenostock=nb;
        if(fscanf(file_conf,"%s,%d",str1,&nb)==2)
        {
          list_section_text=enqueue(list_section_text);
          list_section_text->lineno=*linenostock;
          list_section_text->mnemo=str1;
          list_section_text->param=nb;
        } // Lecture de la mnem à la ligne suivante
        else // Il s'agit d'une mnemo
        {
          list_section_text=enqueue(list_section_text);
          list_section_text->lineno=*linenostock;
          list_section_text->mnemo=str1;
          list_section_text->param=-1;
        }
      }
    }

    else // On lit une mnemo avec 0 param
    {
      list_section_text=enqueue(list_section_text);
      list_section_text->lineno=*linenostock;
      list_section_text->mnemo=str1;
      list_section_text->nb_param=-1;
    }
  }

fclose(file_conf);

return list_section_text;
}
