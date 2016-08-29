#ifndef __GRID1d
#define __GRID1d

#include <stdio.h>
#include <omp.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <errno.h>
#include <sys/time.h>


#include "rgrid/darray.h"

class grid1d
{
public:

    int M;
    double tau;
    double h;
    double **Ez, **Hy;
    double *E, *H;
    double *eps, *miu, *sigma, *sigma1;
    grid1d (char*, double, int);
    ~grid1d(){}
};


#endif
