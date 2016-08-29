#ifndef __SOURCE
#define __SOURCE

#include "grid.h"
#include "rgrid/darray.h"
#define BEGIN 1

/*используется для задания различных типов источников*/


typedef rgrid::DArray<double, double> DArray;

class source
{
public:
    char type;
    int iposition, jposition;
    double t;
    double tau;
    double t1;//for TF/SF
    double coeff;
    //создание источника в заданном месте (не типа "плоская волна")
    void init(char , int , int , grid rect);
    //создание источника типа "плоская волна"
    void init_tfsf (char , int , int , grid rect);
    //источник-пульс Гаусса
    double gaussian (int , DArray );
    //гармонический источник
    double harmonic (int , double , DArray );
    //пересчитать поле в соответствие с алгоритмом источника-плоской волны TFSF
    //флаги показывают, в каком направлении идет волна, и менять нужно электрическое или магнитное поле
    double tfsf(int , int , int , int , int , DArray , DArray, int, int);//if flag = 0 then update H else E
};

#endif
