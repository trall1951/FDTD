#include "source1d.h"

void source1d::init(char mytype, int myiposition, grid1d rect)
{
    type = mytype;
    iposition = myiposition;
    t = 15*rect.tau;
    tau = rect.tau;
}

void source1d::init_tfsf (char mytype, int myiposition, grid1d rect)
{
    type = mytype;
    iposition = myiposition;
    t = 15*rect.tau;
    tau = rect.tau;
    double c = 3.0e8;
    double miu0 = 4.0*3.14*1.0e-7;
    double eps0 = 1.0 / (c*c*miu0);
    t1 = (sqrt(rect.miu[myiposition]*rect.eps[myiposition])*rect.h)/(2*c) + rect.tau/2;//for TF/SF
    coeff = sqrt(rect.eps[myiposition]*eps0/(rect.miu[myiposition]*miu0));
}

void source1d::gaussian (int n, double** Ez)
{
    Ez[iposition][0] = exp((-(((n-8*t)*(n-8*t)))/(t*t)));
}

void source1d::harmonic (int n, double omega, double** Ez)
{
    Ez[iposition][0] = sin(omega*n*tau);
}

void source1d::tfsf(int i, int n, int flag, double** field, double* k)//if flag = 0 then update H else E
{
    if (flag == 0) {
        field[i][1] = field[i][1] - k[i]*exp((-(((n*tau-8*t)*(n*tau-8*t)))/(t*t)));
    }
    else {
        field[i][1] = field[i][1] + k[i]*coeff*exp((-(((n*tau+t1-8*t)*(n*tau+t1-8*t)))/(t*t)));
    }
}


