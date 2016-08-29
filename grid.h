#ifndef __GRID
#define __GRID

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


/*для создания сетки с заданными параметрами*/

typedef rgrid::DArray<double, double> DArray;

class grid
{
public:
	DArray d1;
    int Mx, My;
    double tau;
    double hx, hy;
    grid (char*, double, double, int, int);
    ~grid(){}
};


#endif
