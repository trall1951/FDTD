#ifndef __OUTLINE3d
#define __OUTLINE3d

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


#include "grid3d.h"
#include "pml3d.h"
#include "pml.h"
#include "source3d.h"
#include "rgrid/darray.h"

typedef rgrid::DArray<double, double> DArray;

class outline3d
{
public:

    struct DA da;

    outline3d (grid3d);

    void calculate (outline3d fdtd, grid3d rect, int number, char* type, int* xcoord, int* ycoord, int* zcoord,
                                                        double* omega, int N, int WIDTH, int* rxcoord, int* rycoord,
                                                        int* rzcoord, int rnumber, int* tf, int* tfcoord);

};

#endif


