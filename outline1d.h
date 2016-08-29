#ifndef __OUTLINE1d
#define __OUTLINE1d

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


#include "grid1d.h"
#include "reflect1d.h"
#include "source1d.h"
#include "rgrid/darray.h"




class outline1d
{
public:

    double* Da;
    double* Db;
    double* Ca;
    double* Cb;

    outline1d (grid1d);

    void calculate (outline1d , grid1d , int , char* , int* , double* , int , int , int* , int , int* , int* , int , int* );


};
#endif

