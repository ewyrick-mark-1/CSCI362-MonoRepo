#include "keyboard.hh"

//maps keyboard x and y values to approximately where they are on the standard
//english keyboard. so distance is determines by how close a key is to another.

void initKeyboard(keyboard_coords table[]) {

    table[A].x = 0;
    table[A].y = 1;

    table[B].x = 4;
    table[B].y = 0;

    table[C].x = 2;
    table[C].y = 0;

    table[D].x = 2;
    table[D].y = 1;

    table[E].x = 2;
    table[E].y = 2;

    table[F].x = 3;
    table[F].y = 1;

    table[G].x = 4;
    table[G].y = 1;

    table[H].x = 5;
    table[H].y = 1;

    table[I].x = 7;
    table[I].y = 2;

    table[J].x = 6;
    table[J].y = 1;

    table[K].x = 7;
    table[K].y = 1;

    table[L].x = 8;
    table[L].y = 1;

    table[M].x = 6;
    table[M].y = 0;

    table[N].x = 5;
    table[N].y = 0;

    table[O].x = 8;
    table[O].y = 2;

    table[P].x = 9;
    table[P].y = 2;

    table[Q].x = 0;
    table[Q].y = 2;

    table[R].x = 3;
    table[R].y = 2;
    
    table[S].x = 1;
    table[S].y = 1;

    table[T].x = 4;
    table[T].y = 2;

    table[U].x = 6;
    table[U].y = 2;

    table[V].x = 3;
    table[V].y = 0;

    table[W].x = 1;
    table[W].y = 2;

    table[X].x = 1;
    table[X].y = 0;

    table[Y].x = 5;
    table[Y].y = 2;

    table[Z].x = 0;
    table[Z].y = 0;

}





