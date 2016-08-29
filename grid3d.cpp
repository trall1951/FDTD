#include "grid3d.h"

grid3d::grid3d(char* type, double stepx, double stepy, double stepz, int ssizex, int ssizey, int ssizez)
{
    int i, j, k;
    double c = 3.0e8;
    hx = stepx;
    hy = stepy;
    hz = stepz;
    tau = 1/(c*sqrt(1/(hx*hx)+1/(hy*hy)+1/(hz*hz)));
    Mx = ssizex;
    My = ssizey;
    Mz = ssizez;

    if (strcmp(type, "rect")==0) { //rectangular grid

        d1.resize(Mx, My, Mz, 30);

        for (i = 0; i < Mx; i++) {
            for (j = 0; j < My; j++) {
                for (k = 0; k < Mz; k++) {
                    d1(i,j,k,27) = 4.0*3.14*1.0e-7;
                    d1(i,j,k,26) = 1.0 / (c*c*d1(i,j,k,27));
                    d1(i,j,k,28) = 0;
                    d1(i,j,k,29) = 0;
                }
            }
        }

    }
}


