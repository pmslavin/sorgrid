#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sor.h"


double tol = 0.001, epsilon = 0.0;
int iter = 0;


void initgrid(void)
{
	int i, j;
	double h = M_PI/(double)(N+1);

	for(i=0; i<N+2; i++)
		x[i][N+1] = sin((double)i*h);
	

	for(i=0; i<N+2; i++)
		for(j=0; j<N+1; j++)
			x[i][j] = (double)j*h*x[i][N+1];

	for(i=0; i<N+2; i++)
		for(j=0; j<N+2; j++)
			solution[i][j] = sinh((double)j*h) * sin((double)i*h)/sinh(M_PI);
	

	omega = 2.0/(1.0+sin(M_PI/(double)(N+1)));

	for(i=0; i<N+2; i++){
		for(j=0; j<N+2; j++){
			xnew[0][j] = x[0][j];
			xnew[N+1][j] = x[N+1][j];
		}
		xnew[i][0] = x[i][0];
		xnew[i][N+1] = x[i][N+1];
	}
}

void runsor(void)
{
	int i, j;

	for(i=1; i<N+1; i++)
		for(j=1; j<N+1; j++)
			xnew[i][j] = x[i][j]+0.25*omega*(xnew[i-1][j] + xnew[i][j-1] + x[i+1][j] + x[i][j+1] - (4*x[i][j]));

	for(i=1; i<N+1; i++)
		for(j=1; j<N+1; j++)
			x[i][j] = xnew[i][j];

	iter++;
}


void showgrid(double g[][N+2])
{
	int i,j;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			printf("%.2f ",g[i][j]);
		}
		putchar('\n');
	}
}


double calcerror(void)
{
	int i,j;
	double error = 0.0;

	for(i=1; i<N+1; i++)
		for(j=1; j<N+1; j++)
			error = MAX(error, fabs(solution[i][j] - x[i][j]));

	return error;
}
