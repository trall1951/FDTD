#include "grid.h"

grid::grid(char* type, double stepx, double stepy, int ssizex, int ssizey)
{
    int i, j, k;
    double c = 3.0e8;
    hx = stepx;
    hy = stepy;
    tau = 1/(c*sqrt(1/(hx*hx)+1/(hy*hy)));
    Mx = ssizex;
    My = ssizey;
	
	d1.resize(Mx, My, 1, 16);

	
    if (strcmp(type, "rect")==0) { //rectangular grid
        for (i = 0; i < Mx; i++) {
            for (j = 0; j < My; j++) {
				d1(i, j, 0, 13) = 4.0*3.14*1.0e-7;
				d1(i, j, 0, 12) = 1.0 / (c*c*d1(i, j, 0, 13));
				d1(i, j, 0, 14) = 0;
				d1(i, j, 0, 15) = 0;
            }
        }
        
		
		//printf ("kabancheg = %f\n", 100000000*d1(50,50,0,12));//---------------------------------------------------------
		
		
        /*for (i = 0; i < Mx; i++) {
            for (j = 100; j < 105; j++) {
                d1(i, j, 0, 14) = 3;
            }
        }

        for (i = 0; i < Mx; i++) {
            for (j = 105; j < 150; j++) {
                d1(i, j, 0, 12) = d1(i, j, 0, 12) * 4.5;
            }
        }*/

    }
}


