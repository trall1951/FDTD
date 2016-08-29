#include "outline1d.h"


void outline1d::calculate (outline1d fdtd, grid1d rect, int number, char* type, int* xcoord,
                            double* omega, int N, int WIDTH, int* rxcoord,
                            int rnumber, int* tf, int* tfcoord, int flagP, int* pCoord)
{
    double t = rect.tau*15;
    double e1, e2, e3, h1, h2, h3;//for ABC
    double c = 3.0e8;
    double miu0 = 4.0*3.14*1.0e-7;
    double eps0 = 1.0 / (c*c*miu0);
    char sE[20] = "E";
    char s1[20];
    char s2[20];
    int M = rect.M;
    int i=0, j=0, k;
    int n = 0;

    source1d* s= (source1d*)calloc(number, sizeof(source1d));

    for (i = 0; i < number; i++) {
        if (type[i] == 'g'){
            s[i].init('g', xcoord[i], rect);
        }
        if (type[i] == 'h') {
            s[i].init('h', xcoord[i], rect);
        }
        if (type[i] == 't') {
            s[i].init_tfsf('t', xcoord[i], rect);
        }
    }


    while (n < N) {
        for (i = 0; i < number; i++) {
            if (type[i] == 'h') {
                s[i].harmonic (n, omega[i], rect.Ez);
            }
            if (type[i] == 'g') {
                s[i].gaussian (n, rect.Ez);
            }
        }

        strcpy(s2, ".vtk");
        sprintf(s1, "%d", n);
        strcat(sE, s1);
        strcat(sE, s2);

        write_to_vtk1d(rect.E, sE, rect.M);
        strcpy(sE, "E");
        e3 = e2;
        e2 = e1;
        e1 = rect.Ez[M-1][0];
        for (i = 0; i < M - 1; i++) {
            rect.Hy[i][1] = Da[i]*rect.Hy[i][0] + Db[i] * (rect.Ez[i+1][0] - rect.Ez[i][0]);
            if (type[0] == 't') {
                if ((i == tfcoord[0]-1)&&(tf[0] == 1)) {
                    s[0].tfsf(i, n, 0, rect.Hy, Db);
                }
                else if ((i == tfcoord[1]-1)&&(tf[1] == 1)) {
                    s[0].tfsf(i, n, 0, rect.Hy, Db);
                }
            }
                /*else { //TF-SF
                    rect.Hy[i][1] = Da[i]*rect.Hy[i][0] + Db[i] * (rect.Ez[i+1][0] - rect.Ez[i][0]-exp((-(((n*rect.tau-8*t)*(n*rect.tau-8*t)))/(t*t))));
                }*/
        }
        if (flagP == 0) {
            rect.Hy[M-1][1] = Da[M-1]*rect.Hy[M-1][0] + Db[M-1] * (e3 - rect.Ez[M-1][0]);
        }

        if (flagP == 1) {
            rect.Hy[M-1][1] = rect.Hy[0][1];
        }

        for (i = 0; i < M; i++) {
            rect.Hy[i][0] = rect.Hy[i][1];
        }

        h3 = h2;
        h2 = h1;
        h1 = rect.Hy[0][0];

        for (i = 1; i < M; i++) {
            rect.Ez[i][1] = Ca[i] * rect.Ez[i][0] + Cb[i] * (rect.Hy[i][0] - rect.Hy[i-1][0]);
            if (type[0] == 't') {
                if ((i == tfcoord[0])&&(tf[0] == 1)) {
                    s[0].tfsf(i, n, 1, rect.Ez, Cb);
                }
                else if ((i == tfcoord[1])&&(tf[1] == 1)) {
                    s[0].tfsf(i, n, 1, rect.Ez, Cb);
                }
            }
                /*else {//TF-SF
                    rect.Ez[i][1] = Ca[i] * rect.Ez[i][0] + Cb[i] * (rect.Hy[i][0] - rect.Hy[i-1][0]+coeff*exp((-(((n*rect.tau+t1-8*t)*(n*rect.tau+t1-8*t)))/(t*t))));
                }*/
                //printf ("rcoord = %d\n", rxcoord[0]);
            for (k = 0; k < rnumber; k++) {
                reflect1d::reflection(rxcoord[k], rect.Ez, rect.Hy);
            }
        }
        if (flagP == 0) {
            rect.Ez[0][1] = Ca[0] * rect.Ez[0][0] + Cb[0] * (rect.Hy[0][0] - h3);
        }
        if (flagP == 1) {
            rect.Ez[0][1] = rect.Ez[M-1][1];
        }
        for (i = 0; i < M; i++) {
            rect.Ez[i][0] = rect.Ez[i][1];
            rect.E[i] = (rect.Ez[i][0]);
        }

        n = n + 1;
    }


    free(Da);
    free(Db);
    free(Ca);
    free(Cb);
}


outline1d::outline1d (grid1d rect)
{
    double* miu = (double*)calloc(rect.M, sizeof(double));
    double* eps = (double*)calloc(rect.M, sizeof(double));
    double c = 3.0e8;
    double miu0 = 4.0*3.14*1.0e-7;
    double eps0 = 1.0 / (c*c*miu0);
    int i;


    Da = (double*)calloc((rect.M),sizeof(double));
    Db = (double*)calloc((rect.M),sizeof(double));
    Ca = (double*)calloc((rect.M),sizeof(double));
    Cb = (double*)calloc((rect.M),sizeof(double));


    for (i = 0; i < rect.M; i++) {
        miu[i] = rect.miu[i]*miu0;
        eps[i] = rect.eps[i]*eps0;
    }

    for (i = 0; i < rect.M; i++) {
        Ca[i] = (1-rect.sigma[i]*rect.tau/(2*eps[i]))/(1+rect.sigma[i]*rect.tau/(2*eps[i]));
        Cb[i] = (rect.tau/(eps[i]*rect.h))/(1+rect.sigma[i]*rect.tau/(2*eps[i]));
        Da[i] = (1-rect.sigma1[i]*rect.tau/(2*miu[i]))/(1+rect.sigma1[i]*rect.tau/(2*miu[i]));
        Db[i] = (rect.tau/(miu[i]*rect.h))/(1+rect.sigma1[i]*rect.tau/(2*miu[i]));
    }
}
