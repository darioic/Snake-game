#ifndef TABLERO_H
#define TABLERO_H

#include "casilla.h"
#include "gusano.h"
#include "tamanyo_terminal.h"
#include "azar.h"

#define TABLERO_MAXF 300
#define TABLERO_MAXC 300

typedef struct{

   int a, l;
   tcoords paredes;

}tparedes;


typedef struct {

     tcasilla c[TABLERO_MAXF][TABLERO_MAXC];
     unsigned numf, numc; // tamanyo terminal/matriz real 
     tgusano gus;
     tcoord fruta;
     tparedes paredes;

} ttablero;

int inicializar_tablero(ttablero *tablero);
void mostrar_tablero(ttablero tablero);
void guardar_gusano(ttablero *tablero);
void eliminar_gusano(ttablero *tablero);
int mov_gus_norte(ttablero *tablero);
int mov_gus_sud(ttablero *tablero);
int mov_gus_este(ttablero *tablero);
int mov_gus_oeste(ttablero *tablero);
void inicializar_fruta(tcoord *fruta, int f, int c);
void guardar_fruta(ttablero *tablero);
void eliminar_fruta(ttablero *tablero);
void crecer_gusano(ttablero *tablero);
void comer_fruta(ttablero *tablero);
void inicializar_paredes(ttablero *tablero);
void guardar_paredes(ttablero *tablero);


#endif
