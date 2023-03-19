#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "teclas_tictac.h"

#define SIZE 100
#define MIN_FILS 20
#define TRUE 1
#define FALSE 0
#define GUSANO_VIDAS 3




typedef struct {

   char nombre[SIZE];
   int puntos, l_nombre;
   int tiempo;          //segundos
   float velocidad_gus;
   ttablero tablero;
   int fin_juego;
   int contador;
   int periodo;
   int vidas;
   int canc;

   
   
} tjuego; 

int inicializar_juego(tjuego *j, int vidas); 
void mostrar_juego(tjuego j);
void ejecutar_juego(tjuego *j);
int es_fin_juego(tjuego j);
void mostrar_datos_juego(tjuego j);
void finalizar_juego(tjuego j);


#endif
