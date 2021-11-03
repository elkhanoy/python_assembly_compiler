#include <pyas/all.h>
/*
char*bytecode(pyobj_t bytecode, FILE*file_read_txt, FILE*file_write_bin) //pyobj_t bytecode contient la liste de lexemes correspondant a la section .text
{
  file_r_txt=fopen("mnémo_bin_correspondance.txt","r"); //ouverture du fichier avec les opcodes
  if(NULL==file_r_txt) perror("Erreur ouverture lecture de mnémo_bin_correspondance.txt/n");

  file_w_bin=fopen("bytecode.bin","wb"); //ouverture du fichier dans lequel noter bytecode
  if(NULL==file_w_bin) perror("Erreur ouverture ecriture de bytecode.bin\n");

  char mnemo_tab[35];
  int opcode;
  while(fscanf(file_read_txt,"%s %x",mnemo_tab, &opcode)==2) //lecture du fichier texte ligne par ligne et stockage dans les variables
  {
    if(strcmp(mnemo_tab,???)==0) //si les 2 chaînes sont identiques
    {
      if(fwrite(opcode,sizeof(&opcode),1,file_w_bin)!=1)
      {
        printf("Impossible d'écrire l'opcode\n") //Ecrire au bon endroit dans le fichier, après les infos de l'entete...
      }
      if(opcode>Ox50) //Présence de paramètre
      {
        fwrite();//ecrire les para dans le bytecode en little end
      }
    } //avancer dans le pyobj
  }

  fclose(file_r_txt);
  fclose(file_w_bin);
}
*/
