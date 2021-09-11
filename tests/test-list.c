
/**
 * @file test-list.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  2 17:58:47 2021
 * @brief Driver for list of lexems.
 *
 * Driver for list of lexems.
 */

#include <pyas/all.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void print_help( char *prog ) { 
  char *ptr = prog + strlen( prog ) - 1;
  
  while ( *ptr ) { 
    if ( '/' == *ptr || '\\' == *ptr ) {
      break; 
    }
    ptr--; 
  }
  
  printf( "\n%s -- help\n\n", ptr+1 );

  printf( "  Simple demo for (generic) list of lexems!\n" );

  printf( "\n" );

  exit( EXIT_SUCCESS );
}

static void parse_args( int argc, char *argv[] ) { 
  int i;
  
  for ( i = 1 ; i < argc ; i++ ) { 
    if ( !strcmp( argv[ i ], "-h" ) ||
	 !strcmp( argv[ i ], "--help" )) { 
      print_help( argv[ 0 ] );
    }
  }
  
  return; 
}

int main ( int argc, char *argv[] ) { 

  list_t l = list_new(); 

  parse_args( argc, argv ); 
  
  printf( "\nEmpty list: " );
  list_print( l, lexem_print );
  printf( "\n" );

  l = list_add_first( l, lexem_new( "int", "42", 1, 8 ) );
  l = list_add_first( l, lexem_new( "str", "ficelle", 1, 0 ) );

  printf( "\nList: " );
  list_print( l, lexem_print );
  printf( "\n\n" );

  list_delete( l, lexem_delete );
  
  exit( EXIT_SUCCESS );
}
