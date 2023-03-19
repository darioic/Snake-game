#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "teclas_tictac.h"

#define SIZE 100
#define MIN_FILS 20
#define TRUE 1
#define FALSE 0

typedef struct {

   char nombre[SIZE];
   int puntos, l_nombre;
   int tiempo;          //segundos
   unsigned int velocidad_gus;
   ttablero tablero;
   int fin_juego;
   int contador;
   
} tjuego; 

int inicializar_juego(tjuego *j); 
void mostrar_juego(tjuego j);
void ejecutar_juego(tjuego *j);
int es_fin_juego(tjuego j);
void mostrar_datos_juego(tjuego j);
void finalizar_juego(tjuego j);


#endif
