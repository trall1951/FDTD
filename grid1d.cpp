#include "grid1d.h"

grid1d::grid1d(char* type, double step, int ssize)
{
    int i, j;
    double c = 3.0e8;
    h = step;
    tau = h/(2.0*c);
    M = ssize;


    if (strcmp(type, "rect")==0) { //rectangular grid
        support::my_alloc2(&Ez, M, 2);
        support::my_alloc2(&Hy, M, 2);
        E = (double*)calloc((M+1),sizeof(double));
        H = (double*)calloc((M+1),sizeof(double));
        eps = (double*)calloc((M+1),sizeof(double));
        miu = (double*)calloc((M+1),sizeof(double));
        sigma = (double*)calloc((M+1),sizeof(double));
        sigma1 = (double*)calloc((M+1),sizeof(double));

        for (i = 0; i <= M-60; i++) {
            miu[i] = 1;
            eps[i] = 1;
            sigma[i] = 0;
            sigma1[i] = 0;
        }
        for (i = M-60; i <= M-25; i++) {
            miu[i] = 1;
            eps[i] = 1;
            sigma[i] = 0;
            sigma1[i] = 0;
        }
        for (i = M-24; i < M; i++) {
            miu[i] = 1;
            eps[i] = 1;
            sigma[i] = 0;
            sigma1[i] = 0;
        }

    }
}
