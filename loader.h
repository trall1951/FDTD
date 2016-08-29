#ifndef __LOADER
#define __LOADER

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
#include <cstdlib>
#include "rgrid/darray.h"
//#include "vtk.h"

/*loader читает из файла размеры сетки, размеры граничных условий, типы и число источников и т.д.*/

class loader
{
    loader();
public:
    //аргументы: имя файла, число измерений (1d, 2d, 3d), число ячеек и размер области по каждой координате,
    //число источников, ширина области для граничных поглощающих PML условий, число источников,
    //число ячеек, в которых мы ставим отражающие условия, координаты источника, частота излучения источника
    //координаты ячеек, в которых мы ставим отражающие граничные условия, тип источника, 2 переменных для
    //задания координат и направления распространения плоской волны, флаг для периодических граничных условий,
    //координаты периодических граничных условий
    static void load(const char* , char* , char* , char* , char* , char* , char* , char* ,
                        char* , char* , char* , char* , int* , int* , int* ,
                        double* , int* , int* , int* , char* , int* , int* ,
                        int* , int* );


    //данная функция предназначена для чтения из файла характеристик среды:
    //диэлектрической и магнитной проницаемости, а также проводимости

    //аргументы: имя файла, размер сетки, массив, в который будем писать и какую физическую величину будем писать

    //сначала функция для 2d; после нее функция для 3d
    static void load_array (const char* , int , double** , char );

    static void load_array3d (const char* , int , double*** );

};







#endif
