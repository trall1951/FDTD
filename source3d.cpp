#include "source3d.h"

void source3d::init(grid3d rect, char mytype, int myiposition, int myjposition, int mykposition)
{
    type = mytype;
    iposition = myiposition;
    jposition = myjposition;
    kposition = mykposition;
    t = 15*rect.tau;
    tau = rect.tau;
}

int source3d::gaussian (int n, DArray d1)
{
    
    d1(iposition,jposition,kposition,4) = exp((-(((n*tau-8*t)*(n*tau-8*t)))/(t*t)));;
    return d1(iposition,jposition,kposition,4);
}

int source3d::harmonic (int n, double omega, double tau, DArray d1)
{
    int i, j, k;

    /*Exy[iposition+1][jposition+1][kposition+1][0] = BEGIN*sin(omega*n*tau);
    Eyz[iposition+1][jposition+1][kposition+1][0] = BEGIN*sin(omega*n*tau);
    Ezx[iposition+1][jposition+1][kposition+1][0] = BEGIN*sin(omega*n*tau);
    Exz[iposition+1][jposition+1][kposition+1][0] = BEGIN*sin(omega*n*tau);
    Eyx[iposition+1][jposition+1][kposition+1][0] = BEGIN*sin(omega*n*tau);
    Ezy[iposition+1][jposition+1][kposition+1][0] = BEGIN*sin(omega*n*tau);

    Exy[iposition][jposition+1][kposition+1][0] = -BEGIN*sin(omega*n*tau);
    Eyz[iposition][jposition+1][kposition+1][0] = BEGIN*sin(omega*n*tau);
    Ezx[iposition][jposition+1][kposition+1][0] = BEGIN*sin(omega*n*tau);
    Exz[iposition][jposition+1][kposition+1][0] = -BEGIN*sin(omega*n*tau);
    Eyx[iposition][jposition+1][kposition+1][0] = BEGIN*sin(omega*n*tau);
    Ezy[iposition][jposition+1][kposition+1][0] = BEGIN*sin(omega*n*tau);

    Exy[iposition+1][jposition][kposition+1][0] = BEGIN*sin(omega*n*tau);
    Eyz[iposition+1][jposition][kposition+1][0] = -BEGIN*sin(omega*n*tau);
    Ezx[iposition+1][jposition][kposition+1][0] = BEGIN*sin(omega*n*tau);
    Exz[iposition+1][jposition][kposition+1][0] = BEGIN*sin(omega*n*tau);
    Eyx[iposition+1][jposition][kposition+1][0] = -BEGIN*sin(omega*n*tau);
    Ezy[iposition+1][jposition][kposition+1][0] = BEGIN*sin(omega*n*tau);

    Exy[iposition+1][jposition+1][kposition][0] = BEGIN*sin(omega*n*tau);
    Eyz[iposition+1][jposition+1][kposition][0] = BEGIN*sin(omega*n*tau);
    Ezx[iposition+1][jposition+1][kposition][0] = -BEGIN*sin(omega*n*tau);
    Exz[iposition+1][jposition+1][kposition][0] = BEGIN*sin(omega*n*tau);
    Eyx[iposition+1][jposition+1][kposition][0] = BEGIN*sin(omega*n*tau);
    Ezy[iposition+1][jposition+1][kposition][0] = -BEGIN*sin(omega*n*tau);

    Exy[iposition][jposition+1][kposition][0] = -BEGIN*sin(omega*n*tau);
    Eyz[iposition][jposition+1][kposition][0] = BEGIN*sin(omega*n*tau);
    Ezx[iposition][jposition+1][kposition][0] = -BEGIN*sin(omega*n*tau);
    Exz[iposition][jposition+1][kposition][0] = -BEGIN*sin(omega*n*tau);
    Eyx[iposition][jposition+1][kposition][0] = BEGIN*sin(omega*n*tau);
    Ezy[iposition][jposition+1][kposition][0] = -BEGIN*sin(omega*n*tau);

    Exy[iposition+1][jposition][kposition][0] = BEGIN*sin(omega*n*tau);
    Eyz[iposition+1][jposition][kposition][0] = -BEGIN*sin(omega*n*tau);
    Ezx[iposition+1][jposition][kposition][0] = -BEGIN*sin(omega*n*tau);
    Exz[iposition+1][jposition][kposition][0] = BEGIN*sin(omega*n*tau);
    Eyx[iposition+1][jposition][kposition][0] = -BEGIN*sin(omega*n*tau);
    Ezy[iposition+1][jposition][kposition][0] = -BEGIN*sin(omega*n*tau);

    Exy[iposition][jposition][kposition+1][0] = -BEGIN*sin(omega*n*tau);
    Eyz[iposition][jposition][kposition+1][0] = -BEGIN*sin(omega*n*tau);
    Ezx[iposition][jposition][kposition+1][0] = BEGIN*sin(omega*n*tau);
    Exz[iposition][jposition][kposition+1][0] = -BEGIN*sin(omega*n*tau);
    Eyx[iposition][jposition][kposition+1][0] = -BEGIN*sin(omega*n*tau);
    Ezy[iposition][jposition][kposition+1][0] = BEGIN*sin(omega*n*tau);

    Exy[iposition][jposition][kposition][0] = -BEGIN*sin(omega*n*tau);
    Eyz[iposition][jposition][kposition][0] = -BEGIN*sin(omega*n*tau);
    Ezx[iposition][jposition][kposition][0] = -BEGIN*sin(omega*n*tau);
    Exz[iposition][jposition][kposition][0] = -BEGIN*sin(omega*n*tau);
    Eyx[iposition][jposition][kposition][0] = -BEGIN*sin(omega*n*tau);
    Ezy[iposition][jposition][kposition][0] = -BEGIN*sin(omega*n*tau);*/
	
	return 0;
}


