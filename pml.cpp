#include "pml.h"

//делаем значения коэффициентов для метода FDTD на границах сетки равными определенным величинам
//причем так, чтобы от центра к краям их значения увеличивались
//то, как мы это делаем, не разбирайтесь: тут куча геморроя, чтобы оно работало
//q-массив коэффициентов, характеризующих среду в каждой точке сетки
pml::pml(int myWIDTH, grid rect, struct DA * w)//TODO исправить если не по краям а где то в другом месте поглощение
{

    double c = 3.0e8;
    double MIU = 4.0*3.14*1.0e-7;
    double EPS = 1.0 / (c*c*MIU);
    int i, j;
	
	//w->q.resize(rect.Mx, rect.My, 1, 8);
	
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
            gradientConductivity = boundaryFactor * (pow(x1,(pml::gradingorder+1)));
        }
        else {
            gradientConductivity = boundaryFactor * (pow(x1,(gradingorder+1)) - pow(x2,(gradingorder+1)) );
        }
        gradientCa1[i] = exp (-gradientConductivity * rect.tau / (EPS) );
        gradientCb1[i] = (1.0 - gradientCa1[i]) / (gradientConductivity * rect.hx);

        x1 = (x + 1.0) * rect.hx;
        x2 = (x + 0.0) * rect.hx;
        gradientConductivity = boundaryFactor * (pow(x1,(pml::gradingorder+1)) - pow(x2,(pml::gradingorder+1)) );
        gradientResistivity = gradientConductivity * (MIU / (EPS ) );
        gradientDa1[i] = exp(-gradientResistivity * rect.tau / MIU);
        gradientDb1[i] = (1.0 - gradientDa1[i]) / (gradientResistivity * rect.hx);
    }
	//printf ("11111111111111\n");
    for (j = 0; j < WIDTH; j++) {
        for (i = 0; i < rect.Mx; i++) {
			w->q(i, WIDTH - j, 0, 0) = gradientCa1[j];
			w->q(i, WIDTH - j, 0, 1) = gradientCb1[j];
            w->q(i, rect.My - WIDTH + j, 0, 0) = gradientCa1[j];
			w->q(i, rect.My - WIDTH + j, 0, 1) = gradientCb1[j];
			w->q(i, WIDTH - j - 1, 0, 4) = gradientDa1[j];
			w->q(i, WIDTH - j- 1, 0, 5) = gradientDb1[j];
			w->q(i, rect.My - WIDTH + j, 0, 4) = gradientDa1[j];
			w->q(i, rect.My - WIDTH + j, 0, 5) = gradientDb1[j];
        }
    }
	
    for (i = 0; i < WIDTH; i++) {
        for (j = 0; j < rect.My; j++) {
			w->q(WIDTH - i, j, 0, 2) = gradientCa1[i];
			w->q(WIDTH - i, j, 0, 3) = gradientCb1[i];
			w->q(rect.Mx - WIDTH + i, j, 0, 2) = gradientCa1[i];
			w->q(rect.Mx - WIDTH + i, j, 0, 3) = gradientCb1[i];
			w->q(WIDTH - i - 1, j, 0, 6) = gradientDa1[i];
			w->q(WIDTH - i - 1, j, 0, 7) = gradientDb1[i];
			w->q(rect.Mx - WIDTH + i, j, 0, 6) = gradientDa1[i];
			w->q(rect.Mx - WIDTH + i, j, 0, 7) = gradientDb1[i];
        }
    }
    //printf ("2222222222222222\n");
}



