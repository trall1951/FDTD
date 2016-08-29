#ifndef __PML
#define __PML

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

#include "grid.h"


typedef rgrid::DArray<double, double> DArray;

/*для моделирования поглощающих PML-условий*/

struct DA {
	DArray q;
};

class pml
{
public:
    int WIDTH;
    double temporary;
    static const double omega = 5.0e9;
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
    
    pml(int, grid, struct DA*);
    
    ~pml(){
        free(gradientCa1);
        free(gradientCb1);
        free(gradientDa1);
        free(gradientDb1);
    }


};






#endif

