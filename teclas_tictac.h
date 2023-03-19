// Este fichero se le da al alumno

#ifndef TECLAS_TICTAC_H
#define TECLAS_TICTAC_H
// https://msdn.microsoft.com/en-us/library/aa299374(VS.60).aspx
// http://www.lagmonster.org/docs/DOS7/v-ansi-keys.html

#define UP1	1
#define DOWN1	2
#define LEFT1	3
#define RIGHT1	4
#define UP2	5
#define DOWN2	6
#define LEFT2	7
#define RIGHT2	8
#define CANCEL	9
#define RESTART	10
#define CLEAR	11
#define TIC_TAC	12
#define NOTHING	13
#define OTHER	-1
#define PERIODO 333333

void borrar_pantalla();
void init_tecla_o_tictac();
void end_tecla_o_tictac();
int lee_tecla_o_tictac(int tictac_microsegundos);

#endif // TECLAS_TICTAC_H

