#include <pyas/all.h>


char*bytecode(FILE*file_read_txt, FILE*file_write_bin, list_txt_t l) //pyobj_t bytecode contient la liste de lexemes correspondant a la section .text
{
  file_r_txt=fopen("mnémo_bin_correspondance.txt","r"); //ouverture du fichier avec les opcodes
  if(NULL==file_r_txt) perror("Erreur ouverture lecture de mnémo_bin_correspondance.txt/n");

  file_w_bin=fopen("bytecode.bin","wb"); //ouverture du fichier dans lequel noter le bytecode
  if(NULL==file_w_bin) perror("Erreur ouverture ecriture de bytecode.bin\n");

  int nb;
  char str[50];

while(l->next!=NULL)
{
  do
  {
    fscanf(file_read_txt,"%s,%d",str,nb);
  } while(strcmp(l->mnemo,str)!=0)

  fwrite(nb,sizeof(&nb),1,file_w_bin)
  if(nb>Ox50) //Présence de paramètres
  {
    fwrite(l->nb_param,sizeof(nb_param),1,file_w_bin);//ecrire les para dans le bytecode en little end cmt le mettre en hexa?
  }
  l=l->next;
}
}











  fclose(file_r_txt);
  fclose(file_w_bin);
}
