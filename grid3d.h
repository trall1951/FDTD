#ifndef __GRID3d
#define __GRID3d

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

typedef rgrid::DArray<double, double> DArray;

class grid3d
{
public:

    int Mx, My, Mz;
    double tau;
    double hx, hy, hz;
    DArray d1;
    grid3d (char*, double, double, double, int, int, int);
    ~grid3d(){}
};

#endif
