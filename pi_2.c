#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
void main ()
{
	static long num_steps=100000;
	double pi=0,step,sum=0;
	step=1.0/(double)num_steps;
	printf("%f ",omp_get_wtime());
	#pragma omp parallel for reduction(+:sum) schedule(runtime)
		for (int i=1;i<=num_steps;i++)
		{
			double x=(i+0.5)*step;
			sum+=4.0/(1.0+x*x);
	}
	pi=sum*step;
	printf("%f ",omp_get_wtime());
	printf(" %f",pi);
}