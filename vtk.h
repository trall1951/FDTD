#ifndef VTK_H
#define VTK_H


#include <stdio.h>
#include "rgrid/darray.h"
/*используется для записи значений полей в файлы с расширением vtk, которые
подаются на вход программе paraview*/
typedef rgrid::DArray<double, double> DArray;


void write_to_vtk3d(DArray , const char* , int , int , int , int );

void write_to_vtk2d(DArray , const char* , int , int , int );

void write_to_vtk1d(DArray , const char* , int , int );


#endif //VTK_H
