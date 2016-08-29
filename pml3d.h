#ifndef __PML3d
#define __PML3d

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

#include "grid3d.h"
#include "pml.h"
#include "rgrid/darray.h"

typedef rgrid::DArray<double, double> DArray;


class pml3d
{
public:
    int WIDTH;
    double temporary;
    double x, x1, x2;
    double gradientConductivity, gradientResistivity;
    double boundaryWidth;
    double sigmaMAX;
    double boundaryFactor;
    double*  gradientCa1;
    double*  gradientCb1;
    double*  gradientDa1;
    double*  gradientDb1;
    static const int gradingorder = 3;
    static const double reflectionCoefficient = 1.0e-300;
    pml3d(int, grid3d, struct DA*);
    ~pml3d(){
        free(gradientCa1);
        free(gradientCb1);
        free(gradientDa1);
        free(gradientDb1);
    }

};




#endif

