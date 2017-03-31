#ifndef _SOR_H_
#define _SOR_H_


#define N 100
#define M N+2	/* Unused, but would make arrays neater */
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define M_PI 3.14159265358979323846264338327


extern double x[N+2][N+2];
extern double xnew[N+2][N+2];
extern double solution[N+2][N+2];

extern double omega;
extern double tol, epsilon;
extern int iter;

void	showgrid(double g[][N+2]);
double	calcerror(void);
void	initgrid(void);
void	runsor(void);



#endif
