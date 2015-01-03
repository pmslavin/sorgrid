#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
  #include "windows.h"
#endif
#include "GL/glut.h"
#include "sor.h"
#include "grid.h"



void drawcell(int x, int y, double v)
{
	if(gridcolour == RED)
		glColor3f(v, v/2.0, v/3.5);	/* Flame */
	else if(gridcolour == GREEN)
		glColor3f(v/2.5, v, v/2.0);	/* Absinthe */
	else if(gridcolour == BLUE)
		glColor3f(v/3.0, v/2.5, v);	/* Cherenkov */


	glBegin(GL_QUADS);
		glVertex2i(x*CW+BORDER+xoffset, y*CH+BORDER);
		glVertex2i((x+1)*CW+BORDER+xoffset, y*CH+BORDER);
		glVertex2i((x+1)*CW+BORDER+xoffset, (y+1)*CH+BORDER);
		glVertex2i(x*CW+BORDER+xoffset, (y+1)*CH+BORDER);
	glEnd();
}


void bitmapString(void *font, char *str, int x, int y)
{
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(x, y);

	if(str && strlen(str)){
		while(*str){
			glutBitmapCharacter(font, *str);
			str++;
		}
	}
}


void initRendering(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	gluOrtho2D(0, w, h, 0);
}


void handleKeyPress(unsigned char key, int wx, int wy)
{
	(void)wx; /* Unused */
	(void)wy; /* Unused */

        switch(key){
  /* q */	case 'q':
  /* ESC */     case 27:
				exit(0);
                                break;
  /* Space */	case 32:
  /* p */	case 'p':
				paused = (paused ? 0 : 1);
				break;

  /* b */	case 'b':	boundary = (boundary ? 0 : 1);
				break;

  /* s */	case 's':	paused = 1;
			        if((epsilon = calcerror()) >= tol){
			                runsor();
        		        	glutPostRedisplay();
				}else{
					paused = 0;
				}
				break;

  /* r */	case 'r':	iter = 0;
				paused = 1;
				converged = 0;
				epsilon = 0.0;
				stepDelay = DELAY;
				initgrid();
				glutPostRedisplay();
				break;

  /* c */	case 'c':	gridcolour = ((gridcolour << 1) % 7);
				break;

  /* i */	case 'i':	stepDelay = (stepDelay ? 0 : DELAY);
				paused = 0;
/* Can time here...				glutTimerFunc(stepDelay, update, 0); */
				break;

        }
}



void handleResize(int wx, int hx)
{
        glViewport(0, 0, wx, hx);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void drawScene(void)
{
	int i, j;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

	for(i=0; i<N+boundary; i++){
		for(j=0; j<N+boundary; j++){
			drawcell(j, i, x[i+1][j+1]);
		}
	}


	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2i(xoffset-BORDER, BORDER);
		glVertex2i(w-xoffset+BORDER, BORDER);

		glVertex2i(w-xoffset+BORDER, BORDER);
		glVertex2i(w-xoffset+BORDER, ROWS*CH+BORDER);

		glVertex2i(w-xoffset+BORDER, ROWS*CH+BORDER);
		glVertex2i(xoffset-BORDER, ROWS*CH+BORDER);

		glVertex2i(xoffset-BORDER, ROWS*CH+BORDER);
		glVertex2i(xoffset-BORDER, BORDER);
	glEnd();


	snprintf(itertext, 32, iterstr, iter, epsilon);
	bitmapString(font, itertext, w-w/5, h-BORDER/3);
	if(converged){
		snprintf(convtext, 128, convstr, iter, N, N, tol, omega);
		bitmapString(font, convtext, 48, h-BORDER/3);
	}
	if(paused){
		bitmapString(font, "-=: PAUSED :=-", w/2-40, BORDER/2);
	}
	glutSwapBuffers();


}


void update(int v)
{
	(void)v;	/* Unused */

	if(paused){
	        glutTimerFunc(stepDelay, update, 0);
		glutPostRedisplay();
		return;
	}

	if((epsilon = calcerror()) >= tol){
		runsor();
		glutPostRedisplay();
	        glutTimerFunc(stepDelay, update, 0);
	}else{
		converged = 1;
	        glutTimerFunc(stepDelay, update, 0);
		glutPostRedisplay();
	}
}


int main(int argc, char *argv[])
{
	CW = (MIN(w,h)-2*BORDER)/COLS;
	CH = CW;
	xoffset = (w-(CW*COLS))/2;

	stepDelay = DELAY;
	initgrid();

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(w, h);

        glutCreateWindow("SOR Grid");
        initRendering();

        glutDisplayFunc(drawScene);
        glutKeyboardFunc(handleKeyPress);
        glutReshapeFunc(handleResize);

        glutTimerFunc(stepDelay, update, 0);

        glutMainLoop();
        return 0;
}

