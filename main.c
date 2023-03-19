#include <stdio.h>
#include "juego.h"
#include <unistd.h>

#define GUSANO_VIDAS 3


int main(){

   tjuego j;
  
   if(inicializar_juego(&j,GUSANO_VIDAS)==1){;
     
     do{
      clear_screen();
      mostrar_juego(j);
      ejecutar_juego(&j);
      
     }while(!es_fin_juego(j));
     mostrar_juego(j);
     sleep(3);
     clear_screen();
     finalizar_juego(j);
   }


}
