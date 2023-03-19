#ifndef CASILLA_H
#define CASILLA_H
#include "colores.h"

#define CASILLA_VACIA        0
#define CASILLA_PARED        1
#define CASILLA_GUSANO       2
#define CASILLA_FRUTA        3
#define CASILLA_TEXTO        4
#define CASILLA_CHOQUE       5

#define CASILLA_VALOR_VACIA    ' '
#define CASILLA_VALOR_PARED    '#'
#define CASILLA_VALOR_GUSANO   '@'
#define CASILLA_VALOR_FRUTA    '$'
#define CASILLA_VALOR_CHOQUE   'X'

#define CASILLA_COLOR_DEFECTO  WHITE
#define CASILLA_COLOR_VACIA    CASILLA_COLOR_DEFECTO  
#define CASILLA_COLOR_PARED    CASILLA_COLOR_DEFECTO
#define CASILLA_COLOR_GUSANO   BOLD_GREEN
#define CASILLA_COLOR_FRUTA    BOLD_RED
#define CASILLA_COLOR_TEXTO    CASILLA_COLOR_DEFECTO
#define CASILLA_COLOR_CHOQUE   BOLD_YELLOW

typedef struct {

     char tipo, valor, color;
     
} tcasilla ;

#endif
