#include <pyas/all.h>
//modifier l'opératuer ^par une constante dans la structure indiquant si peut apparaitre ou non
queue_t re_read(char* regexp, queue_t regexp_q) //Fonction traduisant une expression régulière en chaîne de caractère sous forme de liste
{
  char*pregexp=regexp; //Pointeur sur les caractères successifs formant l'expression régulière //Queue représentant les groupes formant la regexp prise en paramètre

  while((*pregexp)!='\0') //Tant que l'on n'est pas à la fin de l'expression régulière prise en paramètre
  {
    //printf("\n%s\n",pregexp);
    // 1 - Cas des caractères de la regexp situés à l'extérieur d'un groupe de caractères placé entre crochets:
    // 1.1 - Sous-cas de l'échappement par un backslash de caractères ayant une signification particulière
    if(*pregexp=='\\')
    {
      //Cas des sept caractères pouvant être échappés après le backslash
      char_group_t * subregexp=calloc(1,sizeof(*subregexp)); //Création d'un espace mémoire pour un sous-groupe pour la regexp étudiée
      switch(*(pregexp+1))
      {
            case '*':

              ini_char_group(subregexp,0); //Initialisation du tableau de booléens présent dans la structure subregexp afin de pouvoir représenter le sous-groupe
              subregexp->group[(int)*(pregexp+1)]=1; //Booléen 1 mis dans la case dont l'indice correspond au caractère placé après le bakslash
              set_occurence(pregexp+1,subregexp);
              regexp_q=enqueue(regexp_q,subregexp); //On enfile un nouveau maillon pointant sur la structure créée à la fin de la queue créée précédemmet
              pregexp=pregexp+2; //Le caractère à l'adresse pregexp+1 ayant déjà été traité
              break;

            case '.':

              ini_char_group(subregexp,0); //Initialisation du tableau de booléens présent dans la structure subregexp afin de pouvoir représenter le sous-groupe
              subregexp->group[(int)*(pregexp+1)]=1; //Booléen 1 mis dans la case dont l'indice correspond au caractère placé après le bakslash
              set_occurence(pregexp+1,subregexp);
              regexp_q=enqueue(regexp_q,subregexp); //On enfile un nouveau maillon pointant sur la structure créée à la fin de la queue créée précédemmet
              pregexp=pregexp+2; //Le caractère à l'adresse pregexp+1 ayant déjà été traité
              break;

            case '?':

              ini_char_group(subregexp,0); //Initialisation du tableau de booléens présent dans la structure subregexp afin de pouvoir représenter le sous-groupe
              subregexp->group[(int)*(pregexp+1)]=1; //Booléen 1 mis dans la case dont l'indice correspond au caractère placé après le bakslash
              set_occurence(pregexp+1,subregexp);
              regexp_q=enqueue(regexp_q,subregexp); //On enfile un nouveau maillon pointant sur la structure créée à la fin de la queue créée précédemmet
              pregexp=pregexp+2; //Le caractère à l'adresse pregexp+1 ayant déjà été traité
              break;

            case '[':

              ini_char_group(subregexp,0); //Initialisation du tableau de booléens présent dans la structure subregexp afin de pouvoir représenter le sous-groupe
              subregexp->group[(int)*(pregexp+1)]=1; //Booléen 1 mis dans la case dont l'indice correspond au caractère placé après le bakslash
              set_occurence(pregexp+1,subregexp);
              regexp_q=enqueue(regexp_q,subregexp); //On enfile un nouveau maillon pointant sur la structure créée à la fin de la queue créée précédemmet
              pregexp=pregexp+2; //Le caractère à l'adresse pregexp+1 ayant déjà été traité
              break;

            case '\\':

              ini_char_group(subregexp,0); //Initialisation du tableau de booléens présent dans la structure subregexp afin de pouvoir représenter le sous-groupe
              subregexp->group[(int)*(pregexp+1)]=1; //Booléen 1 mis dans la case dont l'indice correspond au caractère placé après le bakslash
              set_occurence(pregexp+1,subregexp);
              regexp_q=enqueue(regexp_q,subregexp); //On enfile un nouveau maillon pointant sur la structure créée à la fin de la queue créée précédemmet
              pregexp=pregexp+2; //Le caractère à l'adresse pregexp+1 ayant déjà été traité
              break;

            case '+':

              ini_char_group(subregexp,0); //Initialisation du tableau de booléens présent dans la structure subregexp afin de pouvoir représenter le sous-groupe
              subregexp->group[(int)*(pregexp+1)]=1; //Booléen 1 mis dans la case dont l'indice correspond au caractère placé après le bakslash
              set_occurence(pregexp+1,subregexp);
              regexp_q=enqueue(regexp_q,subregexp); //On enfile un nouveau maillon pointant sur la structure créée à la fin de la queue créée précédemmet
              pregexp=pregexp+2; //Le caractère à l'adresse pregexp+1 ayant déjà été traité
              break;

            case '^':

              ini_char_group(subregexp,0); //Initialisation du tableau de booléens présent dans la structure subregexp afin de pouvoir représenter le sous-groupe
              subregexp->group[(int)*(pregexp+1)]=1; //Booléen 1 mis dans la case dont l'indice correspond au caractère placé après le bakslash
              set_occurence(pregexp+1,subregexp);
              regexp_q=enqueue(regexp_q,subregexp); //On enfile un nouveau maillon pointant sur la structure créée à la fin de la queue créée précédemmet
              pregexp=pregexp+2; //Le caractère à l'adresse pregexp+1 ayant déjà été traité
              break;

            case '#':

              ini_char_group(subregexp,0); //Initialisation du tableau de booléens présent dans la structure subregexp afin de pouvoir représenter le sous-groupe
              subregexp->group[(int)*(pregexp+1)]=1; //Booléen 1 mis dans la case dont l'indice correspond au caractère placé après le bakslash
              set_occurence(pregexp+1,subregexp);
              regexp_q=enqueue(regexp_q,subregexp); //On enfile un nouveau maillon pointant sur la structure créée à la fin de la queue créée précédemmet
              pregexp=pregexp+2; //Le caractère à l'adresse pregexp+1 ayant déjà été traité
              break;

            default: //Si le backslah n'a pas vocation à echapper le caractère qui le suit

              ini_char_group(subregexp,0); //Initialisation du tableau de booléens présent dans la structure subregexp afin de pouvoir représenter le sous-groupe
              subregexp->group[(int)*pregexp]=1; //Booléen 1 mis dans la case dont l'indice correxpond au caractère backslash
              set_occurence(pregexp+1,subregexp);
              regexp_q=enqueue(regexp_q,subregexp);
              pregexp=pregexp+1; //Le pointeur sur les caractères formant la regexp avance d'un cran
        }
    }
    // 1.2 - Sous-cas de la présence d'un point signifiant que tous les caractères sont autorisés
    else if(*pregexp=='.')
    {
      char_group_t * subregexp=calloc(1,sizeof(*subregexp));
      ini_char_group(subregexp,1); //Tous les caractères sont possible, on met donc des 1 dans toutes les cases du tableau
      set_occurence(pregexp,subregexp);
      regexp_q=enqueue(regexp_q,subregexp);
      pregexp=pregexp+1;
    }
    // 1.3 - Sous-cas de la présence d'un accent circonflexe non suivi d'un groupe (cas traité dans la suite)
    else if((*pregexp=='^')&&((*(pregexp+1))!='[')) //Ce qui suit ne peut pas apparaître
    {
      char_group_t * subregexp=calloc(1,sizeof(*subregexp));
      ini_char_group(subregexp,1);
      subregexp->group[(int)*(pregexp+1)]=0; //Le caractère suivant le '^' ne peut apparaitre donc on place un 0 à son indice dans le tableau de bool
      pregexp=pregexp+1;
      set_occurence(pregexp,subregexp);
      regexp_q=enqueue(regexp_q,subregexp);
      pregexp=pregexp+1; //Le caractère à l'adresse pregexp+1 ayant déjà été traité
    }
    // 2 - Cas des caractères de la regexp situés à l'intérieur d'un groupe de caractères placé entre crochets:
    else if((*pregexp=='^')&&((*(pregexp+1))=='[')) //Le groupe qui suit le '^' ne doit pas apparaître
    {
      char_group_t * subregexp=calloc(1,sizeof(*subregexp));
      ini_char_group(subregexp,1);
      pregexp=pregexp+1;
      while(*pregexp!=']')
      {
        if(*pregexp=='\\')
        {
            if((*(pregexp+1))=='.')
            {
              subregexp->group[(int)*(pregexp+1)]=0;
              pregexp=pregexp+2;
            }
            else if ((*(pregexp+1))=='\\')
            {
              subregexp->group[(int)*(pregexp+1)]=0;
              pregexp=pregexp+2;
            }
            else if((*(pregexp+1))==']')
            {
              subregexp->group[(int)*(pregexp+1)]=0;
              pregexp=pregexp+2;
            }
            else if((*(pregexp+1))=='^')
            {
              subregexp->group[(int)*(pregexp+1)]=0;
              pregexp=pregexp+2;
            }
            else
            {
              subregexp->group[(int)*pregexp]=0;
              pregexp=pregexp+1;
            }
        }
        else if(*pregexp=='^')
        {
          subregexp->group[(int)*(pregexp+1)]=0;
          pregexp=pregexp+2;
        }
        else if(*pregexp=='-')
        {
          int i;
          for(i=*(pregexp-1);i<*(pregexp+1)+1;i++) //Tableau rempli sur l'intervalle des caractères entourant le '-', non compris
          {
            subregexp->group[i]=0;
          }
          pregexp=pregexp+2; // pregexp+1 est la borne "sup" du "-"
        }
        else
        {
          subregexp->group[(int)*pregexp]=0;
          pregexp=pregexp+1;
        }
      }
      set_occurence(pregexp,subregexp);
      regexp_q=enqueue(regexp_q,subregexp);
      pregexp=pregexp+1;

    }
    else if(*pregexp=='[') //Les caractères formés après celui-ci forment un seul groupe, jusqu'à ce que le caractère ']' apparaisse
    {
      char_group_t * subregexp=calloc(1,sizeof(*subregexp));
      ini_char_group(subregexp,0);
      pregexp=pregexp+1;
      while(*pregexp!=']')
      {
        if(*pregexp=='\\')
        {
          if(*(pregexp+1)=='.')
          {
            subregexp->group[(int)*(pregexp+1)]=1;
            pregexp=pregexp+2;
          }
          else if (*(pregexp+1)=='\\')
          {
            subregexp->group[(int)*(pregexp+1)]=1;
            pregexp=pregexp+2;
          }
          else if(*(pregexp+1)==']')
          {
            subregexp->group[(int)*(pregexp+1)]=1;
            pregexp=pregexp+2;
          }
          else if(*(pregexp+1)=='^')
          {
            subregexp->group[(int)*(pregexp+1)]=1;
            pregexp=pregexp+2;
          }
          else if(*(pregexp+1)=='n')
          {
            subregexp->group[(int)'\n']=1;
            pregexp=pregexp+2;
          }
          else if(*(pregexp+1)=='t')
          {
            subregexp->group[(int)'\t']=1;
            pregexp=pregexp+2;
          }
          else if(*(pregexp+1)=='-')
          {
            subregexp->group[(int)*(pregexp+1)]=1;
            pregexp=pregexp+2;
          }
          else
          {
            subregexp->group[(int)*pregexp]=1;
            pregexp=pregexp+1;
          }
        }
        else if(*pregexp=='^')
        {
          ini_char_group(subregexp,1);
          if(*(pregexp+1)=='\\'){
            if(*(pregexp+2)=='n'){
              subregexp->group[(int)'\n']=0;
              pregexp=pregexp+3;
            }
            else if(*(pregexp+2)=='t'){
              subregexp->group[(int)'\t']=0;
              pregexp=pregexp+3;
            }
            else{
              subregexp->group[(int)*(pregexp+1)]=0;
              pregexp=pregexp+2;
            }
          }
          else{
            subregexp->group[(int)*(pregexp+1)]=0;
            pregexp=pregexp+2;
          }

        }
        else if(*pregexp=='-')
        {
          int i;
          for( i=*(pregexp-1);i<*(pregexp+1)+1;i++) //Tableau rempli sur l'intervalle des caractères entourant le '-', non compris
          {
            subregexp->group[i]=1;
          }
          pregexp=pregexp+2;
        }
        else
        {
          subregexp->group[(int)*pregexp]=1;
          pregexp=pregexp+1;
        }
        if(*(pregexp)=='\0'){
          free(subregexp);
          printf("\nregexp non conforme\n");
          list_delete(regexp_q,char_group_delete);
          return NULL;
        }
      }
      set_occurence(pregexp,subregexp);
      regexp_q=enqueue(regexp_q,subregexp);

      pregexp=pregexp+1;
    }
    else if((*pregexp=='+') || (*pregexp=='?') || (*pregexp=='*')) // Dans le cas où ce sont des opérateurs.
    {
      pregexp=pregexp+1;
    }
    else// Si aucun des cas précedents n'est vérifé, alors il s'agit d'un seul caractère n'ayant pas de signification particulière
    {
      char_group_t * subregexp=calloc(1,sizeof(*subregexp));
      ini_char_group(subregexp,0);
      subregexp->group[(int)*pregexp]=1;
      set_occurence(pregexp,subregexp);
      regexp_q=enqueue(regexp_q,subregexp);
      pregexp=pregexp+1;
    }
    }
  return regexp_q;
}

//Fonction détectant le nombre d'occurences d'un lexeme
void set_occurence(char*regexp,char_group_t *subgroup){
  if(*(regexp+1) == '+'){
    subgroup->occurence=ONE_OR_MORE;
  }
  else if(*(regexp+1) == '*'){
    subgroup->occurence=ZERO_OR_MORE;
  }
  else if(*(regexp+1) == '?'){
    subgroup->occurence=ONE_OR_ZERO;
  }
  else{
    subgroup->occurence=EXACTLY_ONE;
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
}
