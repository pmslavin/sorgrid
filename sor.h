#ifndef _SOR_H_
#define _SOR_H_


#define N 100
#define M N+2	// Not used, but would make arrays neater
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

double x[N+2][N+2], xnew[N+2][N+2], solution[N+2][N+2];

void showgrid(double g[][N+2]);
double calcerror(double g[][N+2]);
void initgrid(void);
void runsor(void);

double omega;
extern double tol, epsilon;
extern int iter;


#endif
