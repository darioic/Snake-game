#include <stdio.h>
#include "juego.h"
int inicializar_juego(tjuego *j, int vidas){

   int fils, cols, i=0, cols_min, n;
   char c;
   
   
   j->fin_juego=FALSE;
   j->puntos=0;
   j->tiempo=0;
   j->contador=0;
   j->periodo=PERIODO;
   j->vidas=vidas;
   j->canc=FALSE;
   obtener_tamanyo_terminal(&j->tablero.numf,&j->tablero.numc);
   printf("FO-QT21 - Bienvenido al Proyecto Gusanito\n\n");
   printf("El jugador puede controlar el movimiento del gusanito y el juego con las teclas:\n");
   printf("        - Flecha arriba (o tecla 'a')\n");
   printf("        - Flecha abajo (o tecla 'z')\n");
   printf("        - Flecha izquierda (o tecla 'o')\n");
   printf("        - Tecla 'q' (para cancelar)\n\n");
   do{
      printf("Introduce velocidad en pasos/seg [0: defecto 3 p/s, N: >0 p/s]: ");
      scanf("%c%*c", &c);
      n=c;

      
   }while(n!=48);
   j->velocidad_gus=3.0;
   printf("Introduce el nombre del jugador: ");
   do{
   
      scanf("%c", &j->nombre[i]);
      i++;
   
   }while(j->nombre[i-1]!='\n');
   j->l_nombre=i-1;
   cols_min=42+j->l_nombre;
   printf("Introduce datos de paredes dentro del tablero:\n ");
   printf("        -Numero de paredes: ");
   scanf("%d%*c", &j->tablero.paredes.paredes.ncoords);
   printf("         -Longitud de cada pared: ");
   scanf("%d%*c", &j->tablero.paredes.l);
   printf("         -Anchura de cada pared: ");
   scanf("%d%*c", &j->tablero.paredes.a);
   inicializar_paredes(&j->tablero);
   inicializar_tablero(&j->tablero);			
   guardar_paredes(&j->tablero);
   init_tecla_o_tictac();
   if(j->tablero.numf>=MIN_FILS && j->tablero.numc>cols_min){
   
      return 1;
   
   }else{
   
      return 0;
   
   }
   

}

void mostrar_juego(tjuego j){

   int i;
   
   j.velocidad_gus=1/(j.periodo/1000000.0);
   
   printf_color(GREEN);
   printf(" Jugador: ");
   for(i=0; i<j.l_nombre; i++){
   
      printf("%c", j.nombre[i]);

   }
   printf(", Vidas: %d", j.vidas);
   printf(",  Puntos: %d,  Velocidad: %.2f p/s  Tiempo: %02d m %02d s\n", j.puntos, j.velocidad_gus, j.tiempo/60, j.tiempo%60);
   
   printf_reset_color();
   mostrar_tablero(j.tablero); 
                

}

void ejecutar_juego(tjuego *j){

   int tecla, i, n, trobat=FALSE;
   
   
   do{
      if(!trobat){
         tecla=lee_tecla_o_tictac(PERIODO);
      }else{
   
      do{
      
         tecla=lee_tecla_o_tictac(PERIODO);
      
      }while(tecla!=CANCEL && tecla!=RESTART);
   
     }
       
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
                   j->vidas--;
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_CHOQUE;
                   mostrar_juego(*j);
                  if(j->vidas>0){
                      fprintf(stdout, "Te quedan %d vidas. Pulsa 'q' cancelar o 'r' continuar: ", j->vidas);
                      fflush(stdout);
                      trobat=TRUE;
                      tecla=NOTHING;
                      
                      
                   }
                   if(j->vidas==0){
                      j->fin_juego=TRUE;
                   }
                
                }else if(n==2){
                
                   comer_fruta(&j->tablero);     
                   j->puntos++;
                   j->periodo=j->periodo-10000;  
                
                }else if(n==3){
                
                   j->vidas--;
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_GUSANO;
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila+1][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_CHOQUE;
                   mostrar_juego(*j);
                   if(j->vidas>0){
                      fprintf(stdout, "Te quedan %d vidas. Pulsa 'q' cancelar o 'r' continuar: ", j->vidas);
                      fflush(stdout);
                      tecla=NOTHING;
                      
                      
                  }
                   if(j->vidas==0){
                      j->fin_juego=TRUE;
                   }
                
                }
                  
                
                break;
             
             case GUSANO_SUR:
             
                n=mov_gus_sud(&j->tablero);
                
                if(n==0){
                   j->vidas--;
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_CHOQUE;
                   mostrar_juego(*j);
                   if(j->vidas>0){
                      fprintf(stdout, "Te quedan %d vidas. Pulsa 'q' cancelar o 'r' continuar: ", j->vidas);
                      fflush(stdout);
                      trobat=TRUE;
                      tecla=NOTHING;
                      
                      
                  }
                   if(j->vidas==0){
                      j->fin_juego=TRUE;
                   }
                
                }else if(n==2){
                
                   comer_fruta(&j->tablero);   
                   j->puntos++; 
                   j->periodo=j->periodo-10000; 
                
                }else if(n==3){
                   j->vidas--;
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_GUSANO;
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila-1][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_CHOQUE;
                   mostrar_juego(*j);
                   if(j->vidas>0){
                      fprintf(stdout, "Te quedan %d vidas. Pulsa 'q' cancelar o 'r' continuar: ", j->vidas);
                      fflush(stdout);
                      trobat=TRUE;
                      tecla=NOTHING;
                      
                      
                  }
                   if(j->vidas==0){
                      j->fin_juego=TRUE;
                   }
                
                }
                break;
             
             case GUSANO_ESTE:
                n=n=mov_gus_este(&j->tablero);
                if(n==0){
                   j->vidas--;
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_CHOQUE;
                   mostrar_juego(*j);
                   if(j->vidas>0){
                      fprintf(stdout, "Te quedan %d vidas. Pulsa 'q' cancelar o 'r' continuar: ", j->vidas);
                      fflush(stdout);
                      trobat=TRUE;
                      tecla=NOTHING;
                         
                  }
                   if(j->vidas==0){
                      j->fin_juego=TRUE;
                   }
                
                }else if(n==2){
                
                   comer_fruta(&j->tablero);
                   j->puntos++;
                   j->periodo=j->periodo-10000;     
                
                }else if(n==3){
                   j->vidas--;
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_GUSANO;
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col-1].tipo = CASILLA_CHOQUE;
                   mostrar_juego(*j);
                   if(j->vidas>0){
                      fprintf(stdout, "Te quedan %d vidas. Pulsa 'q' cancelar o 'r' continuar: ", j->vidas);
                      fflush(stdout);
                      trobat=TRUE;
                      tecla=NOTHING;
                      
                      
                  }
                   if(j->vidas==0){
                      j->fin_juego=TRUE;
                   }
                
                }
                break;
             
             case GUSANO_OESTE:
                n=mov_gus_oeste(&j->tablero);
                if(n==0){
                   j->vidas--;
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_CHOQUE;
                   mostrar_juego(*j);
                   if(j->vidas>0){
                      fprintf(stdout, "Te quedan %d vidas. Pulsa 'q' cancelar o 'r' continuar: ", j->vidas);
                      fflush(stdout);
                      trobat=TRUE;
                      tecla=NOTHING;
                      
                      
                  }
                   if(j->vidas==0){
                      j->fin_juego=TRUE;
                   }
                
                }else if(n==2){
                
                   comer_fruta(&j->tablero);
                   j->puntos++;  
                   j->periodo=j->periodo-10000;  
                
                }else if(n==3){
                
                   j->vidas--;
                   guardar_gusano(&j->tablero);
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col].tipo = CASILLA_GUSANO;
                   j->tablero.c[j->tablero.gus.coords.coord[0].fila][j->tablero.gus.coords.coord[0].col+1].tipo = CASILLA_CHOQUE;
                   mostrar_juego(*j);
                   if(j->vidas>0){
                      fprintf(stdout, "Te quedan %d vidas. Pulsa 'q' cancelar o 'r' continuar: ", j->vidas);
                      fflush(stdout);
                      trobat=TRUE;
                      tecla=NOTHING;
                      
                      
                  }
                   if(j->vidas==0){
                      j->fin_juego=TRUE;
                   }
                
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
          j->canc=TRUE;
       
       }else if(tecla==RESTART){
       
          inicializar_tablero(&j->tablero);
          guardar_paredes(&j->tablero);
          j->velocidad_gus=3;
       
       }
  }while(tecla==NOTHING);
}

int es_fin_juego(tjuego j){

   return j.fin_juego;

}

void mostrar_datos_juego(tjuego j){
 
  int i;
  int k;
  
  j.velocidad_gus=1/(j.periodo/1000000.0);   
   mostrar_tablero(j.tablero);
   printf("\n\n");
   printf("El juego ha acabado por ");
   if(j.canc){
      printf("'CANCELACION' con los siguientes datos:\n");
   
   }else{ 
      printf("'CHOQUE' con los siguientes datos:\n");
   }
   printf("        - Nombre del jugador: ");
   for(i=0; i<j.l_nombre; i++){
   
      printf("%c", j.nombre[i]);
   
   }  
   printf("\n"); 
   printf("        - Puntos obtenidos: %d\n", j.puntos);
   printf("        - Tiempo de juego: %02d mins %02d segs\n", j.tiempo/60, j.tiempo%60);
   printf("        - Tamanyo del tablero: %u filas x %u columnas\n", j.tablero.numf-2, j.tablero.numc);
   printf("        - Longitud del gusano: %d\n", j.tablero.gus.coords.ncoords);
   printf("        - Velocidad del gusano: %.2f pasos/s\n", j.velocidad_gus);
 


}

void finalizar_juego(tjuego j){

   mostrar_datos_juego(j);
   end_tecla_o_tictac();   



}

