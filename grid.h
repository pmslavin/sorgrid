#ifndef _GRID_H_
#define _GRID_H_

#include "GL/glut.h"


const int w = 1024;
const int h = 768;

const int ROWS = N, COLS = N;
const int BORDER = 24;

const int DELAY = 100;
unsigned char converged = 0, paused = 1, boundary = 0;

typedef enum { RED = 0x01, GREEN = 0x02, BLUE = 0x04 } cell_colour_t;
cell_colour_t gridcolour = RED;

int CW;
int CH;
int xoffset;
int stepDelay;

void *font = GLUT_BITMAP_HELVETICA_12;
char *convstr = "Convergence in %d iterations for %dx%d grid with tolerance %5.3f and omega %.8f";
char *iterstr = "Iteration %d    e: %.8f";
char itertext[32];
char convtext[128];


// This isn't used...
typedef struct cell_struct{

        int x, y;
        float r, g, b, a;

} Cell;



void drawcell(int, int, double);
void bitmapString(void *, char *, int, int);
void initRendering(void);
void handleKeyPress(unsigned char, int, int);
void handleResize(int, int);
void drawScene(void);
void update(int);



#endif
