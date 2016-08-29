#ifndef __SOURCE1d
#define __SOURCE1d

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

#define BEGIN 1

#include "rgrid/darray.h"

class source1d
{
public:
    char type;
    int iposition;
    double t;
    double tau;
    double t1;//for TF/SF
    double coeff;

    void init(char , int , grid1d );

    void init_tfsf (char , int , grid1d );

    void gaussian (int , double** );

    void harmonic (int , double , double** );

    void tfsf(int , int , int , double** , double* );

};

#endif
