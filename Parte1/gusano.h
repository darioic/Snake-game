#ifndef GUSANO_H
#define GUSANO_H

#include "coordenadas.h"

#define GUSANO_NORTE 0
#define GUSANO_SUR   1
#define GUSANO_ESTE  2
#define GUSANO_OESTE 3

typedef struct {

     tcoords coords ;
     unsigned char direccion;    // NORTE,SUR,ESTE,OESTE
     
} tgusano;

void inicializar_gusano(tgusano *gusano, int f, int c);
 

#endif
