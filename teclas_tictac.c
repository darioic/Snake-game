// Este fichero se le da al alumno

// Testeado con Linux, Mac y Windows con DevC++ (que utiliza MinGw)
 
// Si dice algo como "conio.h no such header file" mirar:
	// https://helloacm.com/modern-getch-implementation-on-windows-cc/
// https://stackoverflow.com/questions/10463201/getch-and-arrow-codes
#include <stdio.h>	// for getchar();
#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>	// for getch();
#else // LINUX
#include <stdlib.h>	// for system("/bin/stty raw");
#endif
// #include <time.h>
#include <sys/time.h>
#include "teclas_tictac.h"

#if defined(_WIN32) || defined(_WIN64) // WINDOWS
#define WIN_ARROW	0	// In arrow keyboard (0 and then the arrow)
#define WIN_EXTENDED	224	// In extended keyboard (224 and the arrow)
#define WIN_ESC		1	// ESC
/*
 * Compilando con DevC++ que utiliza MinGw.
 * No con compilador nativo para windows.
 */
#define WIN_C		'c'	// c ClearScreen
#define WIN_R		'r'	// r Restart level
#define WIN_Q		'q'	// q Quit game
#define WIN_O		'o'	// o Right
#define WIN_P		'p'	// p Left
#define WIN_A		'a'	// a Up
#define WIN_Z		'z'	// z Down
/*
 * Se podria dar el caso de que se tubieran que usar estos defines
 * con otro compilador:
#define WIN_C		46	// c ClearScreen
#define WIN_R		19	// r Restart level
#define WIN_Q		16	// q Quit game
*/
#define WIN_UP		72
#define WIN_LEFT	75
#define WIN_RIGHT	77
#define WIN_DOWN	80
#else		// LINUX
#define LINUX_CANCEL	3	// Ctrl+C
#define LINUX_STOP	26	// Ctrl+Z
#define LINUX_ESC	27	// Ctrl+[ because ^[A UP .. ^[D LEFT
#define LINUX_BRACKET	'['	// Not really used
#define LINUX_UP	'A'
#define LINUX_DOWN	'B'
#define LINUX_RIGHT	'C'
#define LINUX_LEFT	'D'
#define LINUX_C		'c'	// c ClearScreen
#define LINUX_Q		'q'	// r Restart level
#define LINUX_R		'r'	// q Quit game
#define LINUX_O		'o'	// o Right
#define LINUX_P		'p'	// p Left
#define LINUX_A		'a'	// a Up
#define LINUX_Z		'z'	// z Down
/*
#define LINUX_CANCEL	3	// Ctrl+C
#define LINUX_STOP	26	// Ctrl+Z
#define LINUX_ESC	27	// ^[A UP .. ^[D LEFT
#define LINUX_BRACKET	91	// Not used
#define LINUX_UP	65
#define LINUX_DOWN	66
#define LINUX_RIGHT	67
#define LINUX_LEFT	68
#define LINUX_Q		113	// r Restart level
#define LINUX_R		114	// q Quit game
*/
#endif // WIN

void borrar_pantalla() {
// https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
#if defined(__linux__)
	// This will work on ANSI terminals, demands POSIX
	printf("\e[1;1H\e[2J");
	// seguro que es mas rapido que una llamada a sistema. Me pregunto si
	// tambien funcionaria para "defined(__unix__) || defined(__APPLE__)"
#endif

#if defined(__unix__) || defined(__APPLE__)
	system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#endif
}

int lee_tecla() {
	int res;

#if defined(_WIN32) || defined(_WIN64)
	// printf("[WINDOWS]\n");
	unsigned char tecla;

	tecla = getch();
	if (tecla == WIN_ARROW || tecla == WIN_EXTENDED) {
		tecla = getch();
		switch (tecla) {
			case WIN_UP:
				res = UP1;
				break;
			case WIN_DOWN:
				res = DOWN1;
				break;
			case WIN_LEFT:
				res = LEFT1;
				break;
			case WIN_RIGHT:
				res = RIGHT1;
				break;
			default:
				// printf("[WIN_OTHER1 %u]", tecla);
				res = OTHER;
		}
	} else {
		switch (tecla) {
			case WIN_C:
				res = CLEAR;
				break;
			case WIN_R:
				res = RESTART;
				break;
			case WIN_ESC:
			case WIN_Q:
				res = CANCEL;
				break;
			case WIN_A:
				res = UP2;
				break;
			case WIN_Z:
				res = DOWN2;
				break;
			case WIN_O:
				res = LEFT2;
				break;
			case WIN_P:
				res = RIGHT2;
				break;
			default:
				// printf("[WIN_OTHER2 %u]", tecla);
				res = OTHER;
		}
	}
#else // !WIN
	// printf("[LINUX]\n");
	int input;

	system("/bin/stty raw");
	input = getchar();
	// printf("[%d]", input);
	switch (input) {
		case LINUX_ESC:
			getchar();
			input = getchar();
			switch (input) {
				case LINUX_UP:		// ^[A
					res = UP1;
					break;
				case LINUX_DOWN:	// ^[B
					res = DOWN1;
					break;
				case LINUX_RIGHT:	// ^[C
					res = RIGHT1;
					break;
				case LINUX_LEFT:	// ^[D
					res = LEFT1;
					break;
				default:
					// printf("[LINUX_OTHER1 %d]", input);
					res = OTHER;
			}
			break;
		case LINUX_C:
			res = CLEAR;
			break;
		case LINUX_R:
			res = RESTART;
			break;
		case LINUX_Q:
		case LINUX_CANCEL:
		case LINUX_STOP:
			res = CANCEL;
			break;
		case LINUX_A:
			res = UP2;
			break;
		case LINUX_Z:
			res = DOWN2;
			break;
		case LINUX_P:
			res = RIGHT2;
			break;
		case LINUX_O:
			res = LEFT2;
			break;
		default:
			// printf("[LINUX_OTHER2 %d]", input);
			res = OTHER;
	}
	system("/bin/stty cooked");
#endif // WIN

	// printf("\n");
	return res;
}

int kbhit() {
	int ret;
	struct timeval tv = { 0L, 0L };

	system("/bin/stty raw");
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	ret = select(1, &fds, NULL, NULL, &tv);
	system("/bin/stty cooked");

	return ret;
}

long tic_tac(int tictac_microsegundos) {
	static long long_stop, long_start = 0;	// En microsegundos
	struct timeval timeval;

	if (long_start == 0) {
		gettimeofday(&timeval, NULL);
		long_start = timeval.tv_sec * 1000000 + timeval.tv_usec;
	} else {
		gettimeofday(&timeval, NULL);
		long_stop = timeval.tv_sec * 1000000 + timeval.tv_usec;
	}

	if ((long_stop - long_start) >= tictac_microsegundos) {
		// printf("TIC-TAC\n");
		long_start += tictac_microsegundos;
		return TIC_TAC;
	}
	return NOTHING;
}

void init_tecla_o_tictac() {
#if defined(__linux__)
	system("/bin/stty -echo");	// linux only
#endif
	tic_tac(0);
}

void end_tecla_o_tictac() {
#if defined(__linux__)
	system("/bin/stty echo");  // linux only
#endif
}

int lee_tecla_o_tictac(int tictac_microsegundos) {
	if (kbhit()) {
		// printf("KBHIT\n");
		return lee_tecla();
	}
	return tic_tac(tictac_microsegundos);
}

// https://stackoverflow.com/questions/10192903/time-in-milliseconds#
//
/*
   struct timeval {
   time_t      tv_sec;     // seconds
   suseconds_t tv_usec;    // microseconds
   };
*/

