#include <pyas/all.h>

/*  sérialiser un objet Python (y compris, donc, de type code –qui devra donc
pouvoir être exécuté par la machine virtuelle Python) */


int pyobj_write( FILE *fp, pyobj_t obj)
{
  fp=fopen("fp","wb"); //ouverture du fichier dans lequel noter le bytecode
  if(NULL==file_w_bin) {perror("Erreur ouverture ecriture de bytecode.bin\n"); return -1;}


















/*  int nb;
  char str[50];

  while(list_text_section->next!=NULL)
  {
    do
    {
      fscanf(file_read_txt,"%s,%d",str,&nb);
    } while(strcmp(list_text_section->mnemo,str)!=0)

    fwrite(nb,sizeof(&nb),1,file_w_bin) // Ecriture de l'opcode correspondant à la bonne mnemo dans le fichier binaire

    if(nb>Ox50) //Présence de paramètres
    {
      fwrite(list_text_section->param,sizeof(list_text_section->param),1,file_w_bin);//ecrire les para dans le bytecode en little end cmt le mettre en hexa?
    }
    list_text_section=list_text_section->next;
  }

  fclose(file_r_txt);
  fclose(file_w_bin);
}*/
