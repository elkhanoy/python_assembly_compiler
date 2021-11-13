
/**
 * @file all.h
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  2 19:08:12 2021
 * @brief General include.
 *
 * General include.
 */

#ifndef _ALL_H_
#define _ALL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <endian.h>
#include <time.h>
#include <string.h>
#include <pyas/callbacks.h>
#include <pyas/list.h>
#include <pyas/queue.h>
#include <pyas/lexem.h>
#include <pyas/lecture_fichier.h>
#include <pyas/re_match.h>
#include <pyas/re_read.h>
#include <pyas/lex.h>
#include <pyas/parsing_tools.h>
#include <pyas/pyobj_structure.h>
#include <pyas/parsing_nonterminal.h>
#include <pyas/pyasm.h>
#include <pyas/pyobj_write.h>

#define _STRING_ 0
#define _LIST_ 1
#define _INTEGER_ 2
#define _FLOAT_ 3
#define _NONE_ 4
#define _NULL_ 5
#define _TRUE_ 6
#define _FALSE_ 7



#ifdef __cplusplus
}
#endif

#endif /* _ALL_H_ */
