#include <stdio.h>
#include "gusano.h"

void inicializar_gusano(tgusano *gusano, int f, int c){

   int i;

   gusano->coords.ncoords=4;
   gusano->direccion=GUSANO_ESTE;
   gusano->coords.coord[0].fila=f;
   gusano->coords.coord[0].col=c;
   for(i=1; i<gusano->coords.ncoords; i++){
   
      gusano->coords.coord[i].fila=f;
      gusano->coords.coord[i].col=c-1;
      c--;   
   
   }


}

	
