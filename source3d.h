#ifndef __SOURCE3d
#define __SOURCE3d

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
#include "grid3d.h"

typedef rgrid::DArray<double, double> DArray;

#define BEGIN 1


//hint: гармонический источник занимает 8 клеток!!! (для имитации сферической волны)!!!!
//но можно исправить и сделать, чтобы занимал 1 клетку

class source3d
{
public:
	double t;
    double tau;
    char type;
    int iposition, jposition, kposition, ssize;

    void init(grid3d, char , int , int , int );

    int gaussian (int , DArray );

    int harmonic (int , double , double , DArray );
};

#endif
