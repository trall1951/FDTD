#include "source.h"

/*используется для задания различных типов источников*/

void source::init(char mytype, int myiposition, int myjposition, grid rect)
{
    type = mytype;
    iposition = myiposition;
    jposition = myjposition;
    t = 15*rect.tau;
    tau = rect.tau;
}
    //создание источника типа "плоская волна"
void source::init_tfsf (char mytype, int myiposition, int myjposition, grid rect)
{
    type = mytype;
    iposition = myiposition;
    jposition = myjposition;
    t = 15*rect.tau;
    tau = rect.tau;
    double c = 3.0e8;
    t1 = sqrt(rect.d1(myiposition,myjposition,0,13)*rect.d1(myiposition,myjposition,0,12))*tau - 1*rect.tau/2;//for TF/SF
    coeff = sqrt(rect.d1(myiposition,myjposition,0,12)/(rect.d1(myiposition,myjposition,0,13)));
}
    //источник-пульс Гаусса
double source::gaussian (int n, DArray d1)
{
    d1(iposition,jposition,0,2) = exp((-(((n*tau-8*t)*(n*tau-8*t)))/(t*t)));
    return d1(iposition,jposition,0,2);
    //printf("E[50][50] = %f\n", rect.d1(50, 50, 0, 2));

}
    //гармонический источник
double source::harmonic (int n, double omega, DArray d1)
{
    d1(iposition,jposition,0,2) = sin(omega*n*tau);
    return d1(iposition,jposition,0,2);
}
    //пересчитать поле в соответствие с алгоритмом источника-плоской волны TFSF
    //флаги показывают, в каком направлении идет волна, и менять нужно электрическое или магнитное поле
double source::tfsf(int i, int j, int n, int flag, int flagH, DArray d1, DArray q, int nd1, int nq)//if flag = 0 then update H else E
{
    if (flag == 0) {
        if (flagH == 0) {
            d1(i, j, 0, nd1+1) = d1(i, j, 0, nd1+1) + q(i, j, 0, nq)*exp((-(((n*tau-8*t)*(n*tau-8*t)))/(t*t)));
            //d1(i, j, 0, nd1+1) = d1(i, j, 0, nd1+1) + q(i, j, 0, nq)*sin(314*n*tau);//частота 50 Гц
        }//если во всех 3 выражениях поменять знак на противоположный, то волна пойет в противоположную сторону
            //то есть противоположные стенки станут областью scattered field
        else {
            d1(i, j, 0, nd1+1) = d1(i, j, 0, nd1+1) - q(i, j, 0, nq)*exp((-(((n*tau-8*t)*(n*tau-8*t)))/(t*t)));
            //d1(i, j, 0, nd1+1) = d1(i, j, 0, nd1+1) - q(i, j, 0, nq)*sin(314*n*tau);
        }
    }
    else {
        d1(i, j, 0, nd1+1) = d1(i, j, 0, nd1+1) + q(i, j, 0, nq)*coeff*exp((-(((n*tau+t1-8*t)*(n*tau+t1-8*t)))/(t*t)));
        //d1(i, j, 0, nd1+1) = d1(i, j, 0, nd1+1) + q(i, j, 0, nq)*coeff*sin(314*n*tau);
    }
    return d1(i, j, 0, nd1+1);
}

