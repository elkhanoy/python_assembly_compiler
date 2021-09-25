#include <pyas/all.h>

queue_t re_read(char* regexp) //Fonction traduisant une expression régulière en chaîne de caractère sous forme de liste
{
  char*pregexp=regexp; //Pointeur sur les caractères successifs formant l'expression régulière
  queue_t regexp_q=queue_new(); //Queue représentant les groupes formant la regexp prise en paramètre

  while((*regexp)!='\0') //Tant que l'on n'est pas à la fin de l'expression régulière prise en paramètre
  {
    // 1 - Cas des caractères de la regexp situés à l'extérieur d'un groupe de caractères placé entre crochets:
    // 1.1 - Sous-cas de l'échappement par un backslash de caractères ayant une signification particulière
    if(*pregexp=='\\')
    {
      if(((*pregexp+1)=='*')||((*pregexp+1)=='.')||((*pregexp+1)=='?')||((*pregexp+1)=='[')||((*pregexp+1)=='\')||((*pregexp+1)=='+')||((*pregexp+1)=='^')) //Cas des sept caractères pouvant être échappés après le backslash
      {
        char_group_t * subregexp=calloc(1,sizeof(*subregexp)); //Création d'un espace mémoire pour un sous-groupe pour la regexp étudiée
        ini_char_group(subregexp,1); //Initialisation du tableau de booléens présent dans la structure subregexp afin de pouvoir représenter le sous-groupe
        subregexp->(group[*(pregexp+1)])=1; //Booléen 1 mis dans la case dont l'indice correspond au caractère placé après le bakslash
        occurence_t(pregexp,subregexp);
        regexp_q=enqueue(regexp_q,subgregexp); //On enfile un nouveau maillon pointant sur la structure créée à la fin de la queue créée précédemmet
        pregexp+2; //Le caractère à l'adresse pregexp+1 ayant déjà été traité
      }
      else //Si le backslah n'a pas vocation à echapper le caractère qui le suit
      {
        char_group_t * subregexp=calloc(1,sizeof(*subregexp)); //Création d'un espace mémoire pour un sous-groupe pour la regexp étudiée
        ini_char_group(subregexp,0); //Initialisation du tableau de booléens présent dans la structure subregexp afin de pouvoir représenter le sous-groupe
        subregexp->(group[*pregexp])=1; //Booléen 1 mis dans la case dont l'indice correxpond au caractère backslash
        occurence_t(pregexp,subregexp);
        regexp_q=enqueue(regexp_q,subgregexp);
        pregexp+1; //Le pointeur sur les caractères formant la regexp avance d'un cran
      }
  }
  // 1.2 - Sous-cas de la présence d'un point signifiant que tous les caractères sont autorisés
  if(*pregexp=='.')
  {
    char_group_t * subregexp=calloc(1,sizeof(*subregexp));
    ini_char_group(subregexp,1); //Tous les caractères sont possible, on met donc des 1 dans toutes les cases du tableau
    occurence_t(pregexp,subregexp);
    regexp_q=enqueue(regexp_q,subregexp);
    pregexp++;
  }
  // 1.3 - Sous-cas de la présence d'un accent circonflexe non suivi d'un groupe (cas traité dans la suite)
  if((*pregexp=='^')&&((*pregexp+1)!='[') //Ce qui suit ne peut pas apparaître
  {
    char_group_t * subregexp=calloc(1,sizeof(*subregexp));
    ini_char_group(subregexp,1);
    subregexp->(group[*(pregexp+1)])=0; //Le caractère suivant le '^' ne peut apparaitre donc on place un 0 à son indice dans le tableau de bool
    pregexp++;
    occurence_t(pregexp,subregexp);
    regexp_q=enqueue(regexp_q,subgregexp);
    pregexp++; //Le caractère à l'adresse pregexp+1 ayant déjà été traité
  }
  // 2 - Cas des caractères de la regexp situés à l'intérieur d'un groupe de caractères placé entre crochets:
  if((*pregexp=='^')&&((*pregexp+1)=='[') //Le groupe qui suit le '^' ne doit pas apparaître
  {
    char_group_t * subregexp=calloc(1,sizeof(*subregexp));
    ini_char_group(subregexp,1);
    regexp++;
    while(*pregexp!=']')
    {
      if(*pregexp=='\\')
      {
          if(((*pregexp+1)=='.')||((*pregexp+1)=='\')||((*pregexp+1)==']')||((*pregexp+1)=='^'))
          {
            subregexp->(group[*(pregexp+1)])=0;
            pregexp+2;
          }
          else
          {
            subregexp->(group[*pregexp])=1;
            pregexp++;
          }
      }
      else if(*pregexp=='^')
      {
        subregexp->(group[*(pregexp+1)])=0;
        pregexp+2;
      }
      else if(*pregexp=='-')
      {
        for(int i=*(pregexp-1)+1;i<*(pregexp+1);i++) //Tableau rempli sur l'intervalle des caractères entourant le '-', non compris
        {
          subregexp->group[i]=0;
        }
        pregexp++;
      }
      else
      {
        subregexp->(group[*pregexp])=0;
        pregexp++;
      }
    }
    occurence_t(pregexp,subregexp);
    regexp_q=enqueue(regexp_q,subgregexp);
    pregexp++;

  }
  if(*regexp=='[') //Les caractères formés après celui-ci forment un seul groupe, jusqu'à ce que le caractère ']' apparaisse
  {
    char_group_t * subregexp=calloc(1,sizeof(*subregexp));
    ini_char_group(subregexp,0);
    pregexp++;
    while(*pregexp!=']')
    {
      if(*pregexp=='\\')
      {
          if(((*pregexp+1)=='[')||((*pregexp+1)=='\\')||((*pregexp+1)==']')||((*pregexp+1)=='^'))
          {
            subregexp->(group[*(pregexp+1)])=1;
            pregexp+2;
          }
          else
          {
            subregexp->(group[*pregexp])=1;
            pregexp++;
          }
      }
      else if(*regexp=='^')
      {
        subregexp->(group[*(pregexp+1)])=1;
        pregexp+2;
      }
      else if(*regexp=='-')
      {
        for(int i=*(regexp-1)+1;i<*(regexp+1);i++) //Tableau rempli sur l'intervalle des caractères entourant le '-', non compris
        {
          subregexp->group[i]=1;
        }
        pregexp++;
      }
      else
      {
        subregexp->(group[*pregexp])=1;
        pregexp++
      }
    }
    occurence_t(pregexp,subregexp);
    regexp_q=enqueue(regexp_q,subgregexp);
    pregexp++;
  }
  }
  return regexp_q;
}

//Fonction détectant le nombre d'occurences d'un lexeme
void set_occurence(char*regexp,char_group_t *subgroup){
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

// Fonction permettant d'initialiser le tableau contenu dans les sturctures représentant un sous groupe pour la regexp
void ini_char_group(char_group_t *subgroup,bool booleen)
{
  int j;
  for(j=0; j<=256; j++)
  {
    subgroup->group[j]=booleen ;
  }
  return subregexp;
}
