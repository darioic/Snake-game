#include <stdio.h>
#include "tablero.h"

void guardar_gusano(ttablero *tablero){
   
   int i;

   for(i=0; i<tablero->gus.coords.ncoords; i++){
       
          tablero->c[tablero->gus.coords.coord[i].fila][tablero->gus.coords.coord[i].col].tipo = CASILLA_GUSANO;
       
   }


}

void eliminar_gusano(ttablero *tablero){

   int i;

   for(i=0; i<tablero->gus.coords.ncoords; i++){
       
          tablero->c[tablero->gus.coords.coord[i].fila][tablero->gus.coords.coord[i].col].tipo = CASILLA_VACIA;
       
   }

}


void guardar_fruta(ttablero *tablero){

   tablero->c[tablero->fruta.fila][tablero->fruta.col].tipo = CASILLA_FRUTA;


}


void eliminar_fruta(ttablero *tablero){


   tablero->c[tablero->fruta.fila][tablero->fruta.col].tipo = CASILLA_VACIA;

}

void inicializar_fruta(tcoord *fruta, int f, int c){


   fruta->fila=f;
   fruta->col=c;


}

void inicializar_paredes(ttablero *tablero){

   int i, j, k, f, c;
   
   for(i=0; i<tablero->paredes.paredes.ncoords; i++){
      
      f=numero_al_azar(tablero->numf-5);
      c=numero_al_azar(tablero->numc-1);
      for(j=f; j<f+tablero->paredes.a; j++){      
                  
         for(k=c; k<c+tablero->paredes.l; k++){
         
            tablero->paredes.paredes.coord[i].fila=j;
            tablero->paredes.paredes.coord[i].col=k;
         
         }
      
      
      
      }
   
   
   
   
   }   


}

void guardar_paredes(ttablero *tablero){

   int i, j, k;

   for(i=0; i<tablero->paredes.paredes.ncoords; i++){
      
      for(j=tablero->paredes.paredes.coord[i].fila; j<tablero->paredes.paredes.coord[i].fila+tablero->paredes.l; j++){      
                  
         for(k=tablero->paredes.paredes.coord[i].col; k<tablero->paredes.paredes.coord[i].col+tablero->paredes.a; k++){
         
            
            tablero->c[j][k].tipo=CASILLA_PARED;      
         
         }
      
      
      }
   
   
   }   


}   





int inicializar_tablero(ttablero *tablero){

   int i, j, k, fila_m, col_m, f, c;
   

   for(i=0; i<tablero->numf-2; i++){
   
      for(j=0; j<tablero->numc; j++){
      
         if((i==0) || (j==0) || (i==tablero->numf-3) || (j==tablero->numc-1)){
         
            tablero->c[i][j].tipo=CASILLA_PARED;
         
         }else{
         
            tablero->c[i][j].tipo=CASILLA_VACIA;
         
         }   
      
      }
   
   
   }   
   fila_m = (tablero->numf-2)/2;
   col_m = tablero->numc/2;
   inicializar_gusano(&tablero->gus, fila_m, col_m);
   guardar_gusano(tablero);
   inicializar_azar();
   do{
      f=numero_al_azar(tablero->numf-3);
      c=numero_al_azar(tablero->numc-2);
      for(i=0; i<tablero->paredes.paredes.ncoords; i++){
      
      for(j=tablero->paredes.paredes.coord[i].fila; j<tablero->paredes.paredes.coord[i].fila+tablero->paredes.l; j++){      
                  
         for(k=tablero->paredes.paredes.coord[i].col; k<tablero->paredes.paredes.coord[i].col+tablero->paredes.a; k++){
         
            
            if(j==f && k==c){
            
               f=0;
               c=0;
            
            }     
         
         }
      
      
      }
   
   
   } 
      
      
   }while(f==0 || c==0);
   inicializar_fruta(&tablero->fruta, f, c);
   guardar_fruta(tablero);

   


}

void mostrar_tablero(ttablero tablero){

   int i, j;

   for(i=0; i<tablero.numf-2; i++){
   
      for(j=0; j<tablero.numc; j++){
      
         switch(tablero.c[i][j].tipo){
             
                case CASILLA_VACIA:
                   printf_color(CASILLA_COLOR_VACIA);
                   printf("%c", CASILLA_VALOR_VACIA);
                   printf_reset_color();
                   break;
                case CASILLA_PARED:
                   printf_color(CASILLA_COLOR_PARED);
                   printf("%c", CASILLA_VALOR_PARED);
                   printf_reset_color();
                   break;
                case CASILLA_GUSANO:
                   printf_color(CASILLA_COLOR_GUSANO);
                   printf("%c", CASILLA_VALOR_GUSANO);
                   printf_reset_color();
                   break;
                case CASILLA_FRUTA:
                   printf_color(CASILLA_COLOR_FRUTA);
                   printf("%c", CASILLA_VALOR_FRUTA);
                   printf_reset_color();
                   break;
                   
                case CASILLA_CHOQUE:
                   printf_color(CASILLA_COLOR_CHOQUE);
                   printf("%c", CASILLA_VALOR_CHOQUE);
                   printf_reset_color();
                   break;
                
                default:
                   printf("?");  
                   break;
         }
            
      
      }
      printf("\n");
   
   }
   

}

int mov_gus_norte(ttablero *tablero){

   int i, j, k;

   eliminar_gusano(tablero);
   if(tablero->gus.coords.coord[0].fila==1){
            
      
      return 0;
            
   }else if(tablero->gus.coords.coord[0].col==tablero->gus.coords.coord[1].col && tablero->gus.coords.coord[1].fila==tablero->gus.coords.coord[0].fila-1){
           
      return -1;
      
   }else if(tablero->gus.coords.coord[0].fila==tablero->fruta.fila && tablero->gus.coords.coord[0].col==tablero->fruta.col){
   
      return 2; //ha comido fruta 
            
   }else{
   
      for(i=1; i<tablero->gus.coords.ncoords; i++){
      
         if(tablero->gus.coords.coord[0].fila==tablero->gus.coords.coord[i].fila && tablero->gus.coords.coord[0].col==tablero->gus.coords.coord[i].col){
         
         
            return 3;
         }
      
      }
      
      for(i=0; i<tablero->paredes.paredes.ncoords; i++){
      
         for(j=tablero->paredes.paredes.coord[i].fila; j<tablero->paredes.paredes.coord[i].fila+tablero->paredes.a; j++){      
                  
            for(k=tablero->paredes.paredes.coord[i].col; k<tablero->paredes.paredes.coord[i].col+tablero->paredes.l; k++){
         
               if(j==tablero->gus.coords.coord[0].fila && k==tablero->gus.coords.coord[0].col){
         
                 return 0;
                 
               }
                     
         
            }
      
      
         }
   
   
      }
            
      for(i=tablero->gus.coords.ncoords-1; i>0; i--){
               
         tablero->gus.coords.coord[i]=tablero->gus.coords.coord[i-1];
               
      }
      tablero->gus.coords.coord[0].fila = tablero->gus.coords.coord[0].fila-1;
      guardar_gusano(tablero);
      
      return 1;
              
   }


}
int mov_gus_sud(ttablero *tablero){

   int i, j, k;

   eliminar_gusano(tablero);
   if(tablero->gus.coords.coord[0].fila==tablero->numf-4){
            
      
      return 0;
            
   }else if(tablero->gus.coords.coord[0].col==tablero->gus.coords.coord[1].col && tablero->gus.coords.coord[1].fila==tablero->gus.coords.coord[0].fila+1){
            
      
      return -1;
      
   }else if(tablero->gus.coords.coord[0].fila==tablero->fruta.fila && tablero->gus.coords.coord[0].col==tablero->fruta.col){
   
      return 2; //ha comido fruta 
            
   }else{
      for(i=1; i<tablero->gus.coords.ncoords; i++){
      
         if(tablero->gus.coords.coord[0].fila==tablero->gus.coords.coord[i].fila && tablero->gus.coords.coord[0].col==tablero->gus.coords.coord[i].col){
         
         
            return 3;
         }
      
      }     
      
      for(i=0; i<tablero->paredes.paredes.ncoords; i++){
      
         for(j=tablero->paredes.paredes.coord[i].fila; j<tablero->paredes.paredes.coord[i].fila+tablero->paredes.a; j++){      
                  
            for(k=tablero->paredes.paredes.coord[i].col; k<tablero->paredes.paredes.coord[i].col+tablero->paredes.l; k++){
         
               if(j==tablero->gus.coords.coord[0].fila && k==tablero->gus.coords.coord[0].col){
         
                 return 0;
                 
               }
                     
         
            }
      
      
         }
   
   
      }
      for(i=tablero->gus.coords.ncoords-1; i>0; i--){
               
         tablero->gus.coords.coord[i]=tablero->gus.coords.coord[i-1];
               
      }
      tablero->gus.coords.coord[0].fila = tablero->gus.coords.coord[0].fila+1;
      guardar_gusano(tablero);
      
      return 1;
            
  }


}
int mov_gus_oeste(ttablero *tablero){

   int i, j, k;

   eliminar_gusano(tablero);
   if(tablero->gus.coords.coord[0].col==1){
            
       
       return 0;
            
   }else if(tablero->gus.coords.coord[0].fila==tablero->gus.coords.coord[1].fila && tablero->gus.coords.coord[1].col==tablero->gus.coords.coord[0].col-1){
            
            
       return -1;
       
   }else if(tablero->gus.coords.coord[0].fila==tablero->fruta.fila && tablero->gus.coords.coord[0].col==tablero->fruta.col){
   
      return 2; //ha comido fruta 
       
   }else{
       for(i=1; i<tablero->gus.coords.ncoords; i++){
      
         if(tablero->gus.coords.coord[0].fila==tablero->gus.coords.coord[i].fila && tablero->gus.coords.coord[0].col==tablero->gus.coords.coord[i].col){
         
         
            return 3;
         }
      
      }  
      for(i=0; i<tablero->paredes.paredes.ncoords; i++){
      
         for(j=tablero->paredes.paredes.coord[i].fila; j<tablero->paredes.paredes.coord[i].fila+tablero->paredes.a; j++){      
                  
            for(k=tablero->paredes.paredes.coord[i].col; k<tablero->paredes.paredes.coord[i].col+tablero->paredes.l; k++){
         
               if(j==tablero->gus.coords.coord[0].fila && k==tablero->gus.coords.coord[0].col){
         
                 return 0;
                 
               }
                     
         
            }
      
      
         }
   
   
      }  
       for(i=tablero->gus.coords.ncoords-1; i>0; i--){
               
          tablero->gus.coords.coord[i]=tablero->gus.coords.coord[i-1];
               
       }
       tablero->gus.coords.coord[0].col = tablero->gus.coords.coord[0].col-1;
       guardar_gusano(tablero);
        
       return 1;    
            
   }

}
int mov_gus_este(ttablero *tablero){

   int i, j, k;

   eliminar_gusano(tablero);
   if(tablero->gus.coords.coord[0].col==tablero->numc-2){
            
    
      
      return 0;
            
   }else if(tablero->gus.coords.coord[0].fila==tablero->gus.coords.coord[1].fila && tablero->gus.coords.coord[1].col==tablero->gus.coords.coord[0].col+1){
            
      
      return -1;
      
   }else if(tablero->gus.coords.coord[0].fila==tablero->fruta.fila && tablero->gus.coords.coord[0].col==tablero->fruta.col){
   
      return 2; //ha comido fruta 
            
   }else{
      for(i=1; i<tablero->gus.coords.ncoords; i++){
      
         if(tablero->gus.coords.coord[0].fila==tablero->gus.coords.coord[i].fila && tablero->gus.coords.coord[0].col==tablero->gus.coords.coord[i].col){
         
         
            return 3;
         }
      
      } 
      
      for(i=0; i<tablero->paredes.paredes.ncoords; i++){
      
         for(j=tablero->paredes.paredes.coord[i].fila; j<tablero->paredes.paredes.coord[i].fila+tablero->paredes.a; j++){      
                  
            for(k=tablero->paredes.paredes.coord[i].col; k<tablero->paredes.paredes.coord[i].col+tablero->paredes.l; k++){
         
               if(j==tablero->gus.coords.coord[0].fila && k==tablero->gus.coords.coord[0].col){
         
                 return 0;
                 
               }
                     
         
            }
      
      
         }
   
   
      }    
      for(i=tablero->gus.coords.ncoords-1; i>0; i--){
               
         tablero->gus.coords.coord[i]=tablero->gus.coords.coord[i-1];
               
      }
      tablero->gus.coords.coord[0].col = tablero->gus.coords.coord[0].col+1;
      guardar_gusano(tablero);
      
      return 1;         
            
   }

}

void crecer_gusano(ttablero *tablero){

   switch(tablero->gus.direccion){
   
      case GUSANO_NORTE:
         
         tablero->gus.coords.coord[tablero->gus.coords.ncoords].fila=tablero->gus.coords.coord[tablero->gus.coords.ncoords-1].fila;
         tablero->gus.coords.coord[tablero->gus.coords.ncoords].col=tablero->gus.coords.coord[tablero->gus.coords.ncoords-1].col;
         tablero->gus.coords.ncoords++;
         mov_gus_norte(tablero);
         guardar_gusano(tablero);
         break;
         
      case GUSANO_SUR:
         tablero->gus.coords.coord[tablero->gus.coords.ncoords].fila=tablero->gus.coords.coord[tablero->gus.coords.ncoords-1].fila;
         tablero->gus.coords.coord[tablero->gus.coords.ncoords].col=tablero->gus.coords.coord[tablero->gus.coords.ncoords-1].col;
         tablero->gus.coords.ncoords++;
         mov_gus_sud(tablero);
         guardar_gusano(tablero);
         break;
         
     case GUSANO_ESTE:

         tablero->gus.coords.coord[tablero->gus.coords.ncoords].fila=tablero->gus.coords.coord[tablero->gus.coords.ncoords-1].fila;
         tablero->gus.coords.coord[tablero->gus.coords.ncoords].col=tablero->gus.coords.coord[tablero->gus.coords.ncoords-1].col;
         tablero->gus.coords.ncoords++;     
         mov_gus_este(tablero);
         guardar_gusano(tablero);
         break;
     
     case GUSANO_OESTE:
         tablero->gus.coords.coord[tablero->gus.coords.ncoords].fila=tablero->gus.coords.coord[tablero->gus.coords.ncoords-1].fila;
         tablero->gus.coords.coord[tablero->gus.coords.ncoords].col=tablero->gus.coords.coord[tablero->gus.coords.ncoords-1].col;
         tablero->gus.coords.ncoords++;
         mov_gus_oeste(tablero);
         guardar_gusano(tablero);
         break;
   
   }


}

void comer_fruta(ttablero *tablero){

    int f, c;

    eliminar_fruta(tablero); 
    crecer_gusano(tablero);
    crecer_gusano(tablero);
    crecer_gusano(tablero);
    do{
      f=numero_al_azar(tablero->numf-3);
      c=numero_al_azar(tablero->numc-2);
    }while(f==0 || c==0);
    inicializar_fruta(&tablero->fruta, f, c);
    guardar_fruta(tablero);


}













