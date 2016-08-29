#ifndef __OUTLINE
#define __OUTLINE

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
#include "vtk.h"
#include "rgrid/darray.h"
#include "grid.h"
#include "pml.h"
#include "source.h"

/*основной класс, для произведения итераций по нашему численному методу*/

typedef rgrid::DArray<double, double> DArray;


class outline
{
public:
    struct DA da;

    outline (grid);

    void calculate (outline fdtd, grid rect, int number, char* type, int* xcoord, int* ycoord,
                            double* omega, int N, int WIDTH, int* rxcoord, int* rycoord,
                            int rnumber, int* tf, int* tfcoord);

};

#endif

