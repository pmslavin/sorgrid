#ifndef _GRID_H_
#define _GRID_H_


typedef enum {
	RED = 0x01,
	GREEN = 0x02,
	BLUE = 0x04
} cell_colour_t;

/* Unused */
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
