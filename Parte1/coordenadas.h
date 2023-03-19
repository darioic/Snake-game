#ifndef COORDENADAS_H
#define COORDENADAS_H

#define MAX_COORDS 64

typedef struct {

     unsigned fila, col ;
     
} tcoord;

typedef struct {

   unsigned ncoords;
   tcoord coord[MAX_COORDS];
   
} tcoords;


#endif
