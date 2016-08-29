#include "pml3d.h"

pml3d::pml3d(int myWIDTH, grid3d rect, struct DA* w)
{

    double c = 3.0e8;
    double MIU = 4.0*3.14*1.0e-7;
    double EPS = 1.0 / (c*c*MIU);
    int i, j, k;
	
	//w->q.resize(rect.Mx, rect.My, rect.Mz, 12);
	
    gradientCa1 = (double*)calloc(myWIDTH, sizeof(double));
    gradientCb1 = (double*)calloc(myWIDTH, sizeof(double));
    gradientDa1 = (double*)calloc(myWIDTH, sizeof(double));
    gradientDb1 = (double*)calloc(myWIDTH, sizeof(double));

    WIDTH = myWIDTH;
    boundaryWidth = WIDTH * rect.hx;
    sigmaMAX = -log(reflectionCoefficient)*(gradingorder+1.0)*EPS*c/(2*boundaryWidth);
    boundaryFactor = sigmaMAX/(rect.hx*pow(boundaryWidth, gradingorder)*(gradingorder+1));

    for (i = 0, x = 0.0; i < WIDTH; i++, x++) {
        x1 = (x + 0.5) * rect.hx;
        x2 = (x - 0.5) * rect.hx;
        if (i == 0) {
            gradientConductivity = boundaryFactor * (pow(x1,(gradingorder+1)));
        }
        else {
            gradientConductivity = boundaryFactor * (pow(x1,(gradingorder+1)) - pow(x2,(gradingorder+1)) );
        }
        gradientCa1[i] = exp (-gradientConductivity * rect.tau / (EPS) );
        gradientCb1[i] = (1.0 - gradientCa1[i]) / (gradientConductivity * rect.hx);

        x1 = (x + 1.0) * rect.hx;
        x2 = (x + 0.0) * rect.hx;
        gradientConductivity = boundaryFactor * (pow(x1,(gradingorder+1)) - pow(x2,(gradingorder+1)) );
        gradientResistivity = gradientConductivity * (MIU / (EPS ) );
        gradientDa1[i] = exp(-gradientResistivity * rect.tau / MIU);
        gradientDb1[i] = (1.0 - gradientDa1[i]) / (gradientResistivity * rect.hx);
    }




    for (j = 0; j < WIDTH; j++) {
        for (i = 0; i < rect.Mx; i++) {
            for (k = 0; k < rect.Mz; k++) {
                w->q(i,WIDTH - j,k,2) = gradientCa1[j];
                w->q(i,WIDTH - j,k,3) = gradientCb1[j];
                w->q(i,rect.My - WIDTH + j,k,2) = gradientCa1[j];
                w->q(i,rect.My - WIDTH + j,k,3) = gradientCb1[j];
                w->q(i,WIDTH - j - 1,k,8) = gradientDa1[j];
                w->q(i,WIDTH - j - 1,k,9) = gradientDb1[j];
                w->q(i,rect.My - WIDTH + j,k,8) = gradientDa1[j];
                w->q(i,rect.My - WIDTH + j,k,9) = gradientDb1[j];
            }
        }
    }

    for (i = 0; i < WIDTH; i++) {
        for (j = 0; j < rect.My; j++) {
            for (k = 0; k < rect.Mz; k++) {
                w->q(WIDTH - i,j,k,0) = gradientCa1[i];
                w->q(WIDTH - i,j,k,1) = gradientCb1[i];
                w->q(rect.Mx - WIDTH + i,j,k,0) = gradientCa1[i];
                w->q(rect.Mx - WIDTH + i,j,k,1) = gradientCb1[i];
                w->q(WIDTH - i - 1,j,k,6) = gradientDa1[i];
                w->q(WIDTH - i - 1,j,k,7) = gradientDb1[i];
                w->q(rect.Mx - WIDTH + i,j,k,6) = gradientDa1[i];
                w->q(rect.Mx - WIDTH + i,j,k,7) = gradientDb1[i];
            }
        }
    }

    for (k = 0; k < WIDTH; k++) {
        for (j = 0; j < rect.My; j++) {
            for (i = 0; i < rect.Mx; i++) {
                w->q(i,j,WIDTH - k,4) = gradientCa1[k];
                w->q(i,j,WIDTH - k,5) = gradientCb1[k];
                w->q(i,j,rect.Mz - WIDTH + k,4) = gradientCa1[k];
                w->q(i,j,rect.Mz - WIDTH + k,5) = gradientCb1[k];
                w->q(i,j,WIDTH - k - 1,10) = gradientDa1[k];
                w->q(i,j,WIDTH - k - 1,11) = gradientDb1[k];
                w->q(i,j,rect.Mz - WIDTH + k,10) = gradientDa1[k];
                w->q(i,j,rect.Mz - WIDTH + k,11) = gradientDb1[k];
            }
        }
    }
}
