// Este fichero se le da al alumno

#include <sys/ioctl.h>
#include "tamanyo_terminal.h"

void obtener_tamanyo_terminal(int *nf, int *nc) {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    // w.ws_row = 10;
    // ioctl(0, TIOCSWINSZ, &w);

    *nf = w.ws_row;
    *nc = w.ws_col;
}

