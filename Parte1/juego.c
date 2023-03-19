#include <stdio.h>
#include "juego.h"
int inicializar_juego(tjuego *j){

   int fils, cols, i=0, cols_min;
   
   
   j->fin_juego=FALSE;
   j->puntos=0;
   j->tiempo=0;
   j->contador=0;
   obtener_tamanyo_terminal(&j->tablero.numf,&j->tablero.numc);
   inicializar_tablero(&j->tablero);
   printf("FO-QT21 - Bienvenido al Proyecto Gusanito\n\n");
   printf("El jugador puede controlar el movimiento del gusanito y el juego con las teclas:\n");
   printf("        - Flecha arriba (o tecla 'a')\n");
   printf("        - Flecha abajo (o tecla 'z')\n");
   printf("        - Flecha izquierda (o tecla 'o')\n");
   printf("        - Tecla 'q' (para cancelar)\n\n");
   printf("Introduce velocidad en pasos/seg [0: defecto 3 p/s, N: >0 p/s]: ");
   scanf("%u%*c", &j->velocidad_gus);
   printf("Introduce el nombre del jugador: ");
   do{
   
      scanf("%c", &j->nombre[i]);
      i++;
   
   }while(j->nombre[i-1]!='\n');
   j->l_nombre=i-1;
   cols_min=42+j->l_nombre;
   
   init_tecla_o_tictac();
   if(j->tablero.numf>=MIN_FILS && j->tablero.numc>cols_min){
   
      return 1;
   
   }else{
   
      return 0;
   
   }
   

}

void mostrar_juego(tjuego j){

   int i;
   
  
   
   printf_color(GREEN);
   printf(" Jugador: ");
   for(i=0; i<j.l_nombre; i++){
   
      printf("%c", j.nombre[i]);

   }
   printf(",  Puntos: %d,  Tiempo: %02d m %02d s\n", j.puntos, j.tiempo/60, j.tiempo%60);
   printf_reset_color();
   mostrar_tablero(j.tablero);
   
}

void ejecutar_juego(tjuego *j){

   int tecla, i, n;
   
   
   do{
   tecla=lee_tecla_o_tictac(PERIODO);
   
       
       if(tecla==TIC_TAC){
          
          if(j->contador==3){
          
             j->tiempo++;
             j->contador=0;
          
          }
          j->contador++;
         
          switch(j->tablero.gus.direccion){
          
             case GUSANO_NORTE:
               
                
                n=mov_gus_norte(&j->tablero);
               
                if(n==0){
                
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_CHOQUE;
                   j->fin_juego=TRUE;
                
                }else if(n==2){
                
                   comer_fruta(&j->tablero);     
                   j->puntos++; 
                
                }else if(n==3){
                
                   
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_GUSANO;
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila+1][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_CHOQUE;
                   j->fin_juego=TRUE;
                
                }
                break;
             
             case GUSANO_SUR:
             
                n=mov_gus_sud(&j->tablero);
                
                if(n==0){
                
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_CHOQUE;
                   j->fin_juego=TRUE;
                
                }else if(n==2){
                
                   comer_fruta(&j->tablero);   
                   j->puntos++; 
                
                }else if(n==3){
                
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_GUSANO;
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila-1][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_CHOQUE;
                   j->fin_juego=TRUE;
                
                }
                break;
             
             case GUSANO_ESTE:
                n=n=mov_gus_este(&j->tablero);
                if(n==0){
                
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_CHOQUE;
                   j->fin_juego=TRUE;
                
                }else if(n==2){
                
                   comer_fruta(&j->tablero);
                   j->puntos++;    
                
                }else if(n==3){
                
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_GUSANO;
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col-1].tipo = CASILLA_CHOQUE;
                   j->fin_juego=TRUE;
                
                }
                break;
             
             case GUSANO_OESTE:
                n=mov_gus_oeste(&j->tablero);
                if(n==0){
                
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_CHOQUE;
                   j->fin_juego=TRUE;
                
                }else if(n==2){
                
                   comer_fruta(&j->tablero);
                   j->puntos++;    
                
                }else if(n==3){
                
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_GUSANO;
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col+1].tipo = CASILLA_CHOQUE;
                   j->fin_juego=TRUE;
                
                }
                break;
          }   
          
       }else if(tecla==UP1 || tecla==UP2){
       
          if(mov_gus_norte(&j->tablero)!=-1){
                 
             j->tablero.gus.direccion=GUSANO_NORTE;
          }else{
          
             
            j->tablero.gus.direccion=GUSANO_SUR;
   
   
          }   
          
          
          
       }else if(tecla==DOWN1 || tecla==DOWN2){
       
         if(mov_gus_sud(&j->tablero)!=-1){
                 
             j->tablero.gus.direccion=GUSANO_SUR;
          }else{
          
             
            j->tablero.gus.direccion=GUSANO_NORTE;
   
   
          }  
       
       }else if(tecla==LEFT1 || tecla==LEFT2){
       
        
          if(mov_gus_oeste(&j->tablero)!=-1){
                 
             j->tablero.gus.direccion=GUSANO_OESTE;
          }else{
          
             
            j->tablero.gus.direccion=GUSANO_ESTE;
   
   
          }    
       
       }else if(tecla==RIGHT1 || tecla==RIGHT2){
       
        
          if(mov_gus_este(&j->tablero)!=-1){
                 
             j->tablero.gus.direccion=GUSANO_ESTE;
          }else{
          
             
            j->tablero.gus.direccion=GUSANO_OESTE;
   
   
          }   
       
       }else if(tecla==CANCEL){
       
          j->fin_juego=TRUE;
       
       }
  }while(tecla==NOTHING);
}

int es_fin_juego(tjuego j){

   return j.fin_juego;

}

void mostrar_datos_juego(tjuego j){
 
  int i;
  int k;
  
   
  
   for(i=0; i<j.tablero.numf-10; i++){
   
      for(k=0; k<j.tablero.numc; k++){
      
         if( (k==0) || (i==j.tablero.numf-11) || (k==j.tablero.numc-1)){
         
            printf("#");
         
         }  
      
      }
      printf("\n");
   
   
   }
   printf("\n\n");
   printf("El juego ha acabado por 'CHOQUE' con los siguientes datos:\n");
   printf("        - Nombre del jugador: ");
   for(i=0; i<j.l_nombre; i++){
   
      printf("%c", j.nombre[i]);
   
   }  
   printf("\n"); 
   printf("        - Puntos obtenidos: %d\n", j.puntos);
   printf("        - Tiempo de juego: %02d m %02d s\n", j.tiempo/60, j.tiempo%60);
   printf("        - Tamanyo del tablero: %u filas x %u columnas\n", j.tablero.numf-2, j.tablero.numc);
   printf("        - Longitud del gusano: %d\n", j.tablero.gus.coords.ncoords);
   printf("        - Velocidad del gusano: ");
   if(j.velocidad_gus==0){
   
      printf("3.00 pasos/seg\n");
   } 
   


}

void finalizar_juego(tjuego j){

   mostrar_datos_juego(j);
   end_tecla_o_tictac();   



}

