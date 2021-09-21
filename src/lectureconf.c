/* Fonction qui prend en argument la chaîne de caractère contenue
dans sur une ligne du fichier de configuration
stockée dans une structure du dictionnaire dans le champs
exp_str. */


#include <pyas/all.h>

queue_t split_regexp(char* regexp, queue_t *list_char){

  //Cas regexp fin de chaine de caractère
  //char * p_regexp=regexp;
  if(*(regexp)=='\0') {
    return list_char;
  } //on arrive à la fin de la regexp

//Si à l'extérieur d'un '[]':
  //Cas du '\\'
  if((*(regexp))=='\\'){
    int code_backslash = check_backslash(regexp);

    if (code_backslash == 0){ //Cas \ suivi de rien
      printf("Expression régulière non-reconnue\n") ;
      return list_char ;
    }

    else if (code_backslash != 8){ //Cas '\n'
      char_group_t * mini_regexp = NULL ;
      mini_regexp=calloc(1,sizeof(*mini_regexp));
      mini_regexp=new_queue_char_group(mini_regexp,"0");
      // for(int j=0, j<256,j++) mini_regexp->group[j]='0' ;// mise à jour du tableau
      mini_regexp->group[*(regexp+1)]='1';
      mini_regexp->occurence=set_occurence(regexp,mini_regexp);
      list_char=enqueue(list_char,(char_group_t*)mini_regexp); //enfilage du char_group
      regexp++; //Là on arrive donc sur le '-'
      list_char=split_regexp(regexp,list_char);
    }
    else { //Cas '\n'
      char_group_t * mini_regexp = NULL ;
      mini_regexp=calloc(1,sizeof(*mini_regexp));
      mini_regexp=new_queue_char_group(mini_regexp,"0");
      // for(int j=0, j<256,j++) mini_regexp->group[j]='0' ;// mise à jour du tableau
      mini_regexp->group[*(regexp)]='1';
      mini_regexp->occurence=set_occurence(regexp,mini_regexp);
      list_char=enqueue(list_char,(char_group_t*)mini_regexp); //enfilage du char_group
      regexp++; //Là on arrive donc sur le '-'
      list_char=split_regexp(regexp,list_char);
    }
    if(*(regexp)=='.'){
      char_group_t * mini_regexp = NULL ;
      mini_regexp=calloc(1,sizeof(*mini_regexp));
      mini_regexp=new_queue_char_group(mini_regexp,"1");
      mini_regexp->occurence=set_occurence(regexp,mini_regexp);
      list_char=enqueue(list_char,(char_group_t*)mini_regexp); //enfilage du char_group
      regexp++; //Là on arrive donc sur le '-'
      list_char=split_regexp(regexp,list_char);
    }
  } //fin du cas '\\'

//Si à l'intérieur de '[]'
  //Cas du '['
  if(regexp=="["){

    regexp++; //on passe au caractère suivant le '['
    char_group_t *mini_regexp = NULL ;
    mini_regexp=calloc(1,sizeof(*mini_regexp));
    mini_regexp=new_queue_char_group(mini_regexp,"0");
    while(regexp!="]"){ //Tant qu'on atteint pas le ']'

      if (*regexp=='\\'){ //Cas '\n'

        // for(int j=0, j<256,j++) mini_regexp->group[j]='0' ;// mise à jour du tableau
        mini_regexp->group[*(regexp+1)]='1'; //enfilage du char_group
        regexp++; //Là on arrive donc sur le '-
       //////////////////////////////////////////////////////////////////////////
     }
     else if(*(regexp)=='^'){ //si le caractère lu est un '^'
        mini_regexp->group[*(regexp+1)]='0';
        regexp++;
     }

     else if(*(regexp)=="-"){ //Si le caractère suivant n'est pas un '-'
        int i;
        for(i=*(regexp-1);i<=*(regexp+1);i++){
          mini_regexp->group[i]='1';
        }
       //enfilage du caractère
       regexp+2; //On passe au caractère suivant
     }

    else{ //si le caractère suivant est un '-'
      mini_regexp->group[*(regexp)]='1';
      regexp++;
    }
  }
  mini_regexp->occurence=set_occurence(regexp,mini_regexp);
  list_char=enqueue(list_char,(char_group_t*)mini_regexp);
  list_char=split_regexp(list_char,list_char);
  }
}
  ///////////////////////////////////////////////////////////////////////////
// Fonction d'échappement de caractères

int check_backslash(char* regexp) {
  if (*(regexp+1)=='\0') { //Si le \ n'est pas suivi par qqc (fin de la chaine de caractère) -> erreur
    return 0 ; // -> erreur
  }
  else if ( (*(regexp+1)=='*') ) { // cas de l'échappement de *
    return 1 ; //on renvoie le code "1" qui veut dire qu'on doit enqueue l'expression régulière "*"
  }
  else if ( (*(regexp+1)=='.') ) { // cas de l'échappement de .
    return 2 ;  //on renvoie le code "2" qui veut dire qu'on doit enqueue l'expression régulière "."
  }
  else if ( (*(regexp+1)=='?') ) { // cas de l'échappement de ?
    return 3 ;  //on renvoie le code "3" qui veut dire qu'on doit enqueue l'expression régulière "?"
  }
  else if ( (*(regexp+1)=='[') ) { // cas du [
    return 4 ;  //on renvoie le code "4" qui veut dire qu'on doit enqueue l'expression régulière "["
  }
  else if ( (*(regexp+1)=='\\') ) { // cas du '\\'
    return 5 ;  //on renvoie le code "5" qui veut dire qu'on doit enqueue l'expression régulière "\"
  }
  else if ( (*(regexp+1)=='+') ) { // cas du +
      return 6 ;  //on renvoie le code "6" qui veut dire qu'on doit enqueue l'expression régulière "+"
    }
  else if ( (*(regexp+1)=='^') ) { // cas du ^
      return 7 ;  //on renvoie le code "7" qui veut dire qu'on doit enqueue l'expression régulière "^"
    }
  else{ //sinon, n'importe quel autre caractère
    return 8 ;  //on renvoie le code "3" qui veut dire qu'on doit enqueue l'expression régulière "caractère_qui_suit_le_\"
  }
}

// Fonction de création structure char_group

// Fonction occurence d'un lexeme
occurence_t set_occurence(char*regexp,char_group_t *mini_regexp){
  if(*(regexp+1) == '+'){
    mini_regexp->occurence=ONE_OR_MORE;
  }
  else if(*(regexp+1) == '*'){
    mini_regexp->occurence=ZERO_OR_MORE;
  }
  else if(*(regexp+1) == '?'){
    mini_regexp->occurence=ONE_OR_ZERO;
  }
  else{
    mini_regexp->occurence=EXACTLY_ONE;
  }
}
// Fonction d'enfilage char_group
char_group_t *new_queue_char_group(char_group_t *mini_regexp, char *bool){
  int j;
  for(j=0; j<256;j++) {
    mini_regexp->group[j]=bool ;
  }// mise à jour du tableau
  return mini_regexp;
}
