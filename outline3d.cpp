#include "outline3d.h"


void outline3d::calculate (outline3d fdtd, grid3d rect, int number, char* type, int* xcoord, int* ycoord, int* zcoord,
                            double* omega, int N, int WIDTH, int* rxcoord, int* rycoord, int* rzcoord, int rnumber,
                            int* tf, int* tfcoord)
{
    char sE[20] = "E";
    char s1[20];
    char s2[20];
    int Mx = rect.Mx;
    int My = rect.My;
    int Mz = rect.Mz;
    int i=0, j=0, k, l=0;
    int n = 0;



    pml3d(WIDTH, rect, &da);
    
    source3d* s= (source3d*)calloc(number, sizeof(source3d));

    for (i = 0; i < number; i++) {
        if (type[i] == 'g'){
            s[i].init(rect, 'g', xcoord[i], ycoord[i], zcoord[i]);
        }
        if (type[i] == 'h') {
            s[i].init(rect, 'h', xcoord[i], ycoord[i], zcoord[i]);
        }
    }
	/*for (i = 1; i < Mx-1; i++) {
        for (j = 1; j < My-1; j++) {
            for (k = 1; k < Mz-1; k++) {
                rect.d1(i, j, k,4) = 0.5*exp((-(((j-My/2)*(j-My/2))+((k-Mz/2)*(k-Mz/2)))/(3.5*3.5)));
            }
        }
    }*/

    while (n < N) {
        for (i = 0; i < number; i++) {
            /*if (type[i] == 'h') {
                s[i].harmonic (n, omega[i], rect.tau, rect.Ezx, rect.Ezy, rect.Exy, rect.Exz, rect.Eyz, rect.Eyx);
            }*/
            if (type[i] == 'g') {
                rect.d1(xcoord[i], ycoord[i], zcoord[i],4) = s[i].gaussian (n, rect.d1);
            }
        }

        strcpy(s2, ".vtk");
        sprintf(s1, "%d", n);
        strcat(sE, s1);
        strcat(sE, s2);
        write_to_vtk3d(rect.d1, sE, rect.Mx, rect.My, rect.Mz, 24);
        strcpy(sE, "E");

        for (i = 1; i < Mx - 1; i++) {
            for (j = 1; j < My - 1; j++) {
                for (k = 1; k < Mz - 1; k++) {
                    rect.d1(i,j,k,17) = da.q(i,j,k,8) * rect.d1(i,j,k,16) - da.q(i,j,k,9) * (rect.d1(i,j+1,k,2)-rect.d1(i,j,k,2)-rect.d1(i,j,k,0)+rect.d1(i,j+1,k,0));
                    rect.d1(i,j,k,19) = da.q(i,j,k,10) * rect.d1(i,j,k,18) + da.q(i,j,k,11) * (rect.d1(i,j,k+1,8)-rect.d1(i,j,k,8)-rect.d1(i,j,k,10)+rect.d1(i,j,k+1,10));
                    rect.d1(i,j,k,23) = da.q(i,j,k,6) * rect.d1(i,j,k,22) + da.q(i,j,k,7) * (rect.d1(i+1,j,k,0)-rect.d1(i,j,k,0)-rect.d1(i,j,k,2)+rect.d1(i+1,j,k,2));
                    rect.d1(i,j,k,21) = da.q(i,j,k,10) * rect.d1(i,j,k,20) - da.q(i,j,k,11) * (rect.d1(i,j,k+1,6)-rect.d1(i,j,k,6)-rect.d1(i,j,k,4)+rect.d1(i,j,k+1,4));
                    rect.d1(i,j,k,13) = da.q(i,j,k,6) * rect.d1(i,j,k,12) - da.q(i,j,k,7) * (rect.d1(i+1,j,k,10)-rect.d1(i,j,k,10)-rect.d1(i,j,k,8)+rect.d1(i+1,j,k,8));
                    rect.d1(i,j,k,15) = da.q(i,j,k,8) * rect.d1(i,j,k,14) + da.q(i,j,k,9) * (rect.d1(i,j+1,k,6)-rect.d1(i,j,k,6)-rect.d1(i,j,k,4)+rect.d1(i,j+1,k,4));
                }
            }
        }

        for (i = 1; i < Mx - 1; i++) {
            for (j = 1; j < My - 1; j++) {
                for (k = 1; k < Mz - 1; k++) {
                    rect.d1(i,j,k,16) = rect.d1(i,j,k,17);
                    rect.d1(i,j,k,20) = rect.d1(i,j,k,21);
                    rect.d1(i,j,k,12) = rect.d1(i,j,k,13);
                    rect.d1(i,j,k,18) = rect.d1(i,j,k,19);
                    rect.d1(i,j,k,22) = rect.d1(i,j,k,23);
                    rect.d1(i,j,k,14) = rect.d1(i,j,k,15);
                }
            }
        }

        for (i = 1; i < Mx - 1; i++) {
            for (j = 1; j < My - 1; j++) {
                for (k = 1; k < Mz - 1; k++) {
                    rect.d1(i,j,k,5) = da.q(i,j,k,2) * rect.d1(i,j,k,4) +  da.q(i,j,k,3)*(-rect.d1(i,j-1,k,12) + rect.d1(i,j,k,12) - rect.d1(i,j-1,k,14) + rect.d1(i,j,k,14));
                    rect.d1(i,j,k,7) = da.q(i,j,k,4) * rect.d1(i,j,k,6) -  da.q(i,j,k,5)*(-rect.d1(i,j,k-1,22) + rect.d1(i,j,k,22) - rect.d1(i,j,k-1,20) + rect.d1(i,j,k,20));
                    rect.d1(i,j,k,9) = da.q(i,j,k,4) * rect.d1(i,j,k,8) +  da.q(i,j,k,5)*(-rect.d1(i,j,k-1,16) + rect.d1(i,j,k,16) - rect.d1(i,j,k-1,18) + rect.d1(i,j,k,18));
                    rect.d1(i,j,k,11) = da.q(i,j,k,0) * rect.d1(i,j,k,10) -  da.q(i,j,k,1)*(-rect.d1(i-1,j,k,12) + rect.d1(i,j,k,12) - rect.d1(i-1,j,k,14) + rect.d1(i,j,k,14));
                    rect.d1(i,j,k,1) = da.q(i,j,k,0) * rect.d1(i,j,k,0) +  da.q(i,j,k,1)*(-rect.d1(i-1,j,k,20) + rect.d1(i,j,k,20) - rect.d1(i-1,j,k,22) + rect.d1(i,j,k,22));
                    rect.d1(i,j,k,3) = da.q(i,j,k,2) * rect.d1(i,j,k,2) -  da.q(i,j,k,3)*(-rect.d1(i,j-1,k,16) + rect.d1(i,j,k,16) - rect.d1(i,j-1,k,18) + rect.d1(i,j,k,18));
                }
            }
        }

        for (i = 1; i < Mx - 1; i++) {
            for (j = 1; j < My - 1; j++) {
                for (k = 1; k < Mz - 1; k++) {
                    rect.d1(i,j,k,4) = rect.d1(i,j,k,5);
                    rect.d1(i,j,k,8) = rect.d1(i,j,k,9);
                    rect.d1(i,j,k,0) = rect.d1(i,j,k,1);
                    rect.d1(i,j,k,6) = rect.d1(i,j,k,7);
                    rect.d1(i,j,k,10) = rect.d1(i,j,k,11);
                    rect.d1(i,j,k,2) = rect.d1(i,j,k,3);
                    rect.d1(i,j,k,24) = sqrt((rect.d1(i,j,k,4)+rect.d1(i,j,k,6))*(rect.d1(i,j,k,4)+rect.d1(i,j,k,6))+(rect.d1(i,j,k,8)+rect.d1(i,j,k,10))*(rect.d1(i,j,k,8)+rect.d1(i,j,k,10))+(rect.d1(i,j,k,0)+rect.d1(i,j,k,2))*(rect.d1(i,j,k,0)+rect.d1(i,j,k,2)));
                }
            }
        }

        n = n + 1;
    }
}



outline3d::outline3d (grid3d rect)
{
    da.q.resize(rect.Mx, rect.My, rect.Mz, 12);
    
    int i, j, k;

    double c = 3.0e8;
    double MIU = 4.0*3.14*1.0e-7;
    double EPS = 1.0 / (c*c*MIU);//TODO: запихать в другое место


    for (i = 0; i < rect.Mx; i++) {
        for (j = 0; j < rect.My; j++) {
            for (k = 0; k < rect.Mz; k++) {
                da.q(i,j,k,0) = (1-rect.d1(i,j,k,28)*rect.tau/(2*rect.d1(i,j,k,26)))/(1+rect.d1(i,j,k,28)*rect.tau/(2*rect.d1(i,j,k,26)));
                da.q(i,j,k,1) = (rect.tau/(rect.d1(i,j,k,26)*rect.hx))/(1+rect.d1(i,j,k,28)*rect.tau/(2*rect.d1(i,j,k,26)));
                da.q(i,j,k,2) = (1-rect.d1(i,j,k,28)*rect.tau/(2*rect.d1(i,j,k,26)))/(1+rect.d1(i,j,k,28)*rect.tau/(2*rect.d1(i,j,k,26)));
                da.q(i,j,k,3) = (rect.tau/(rect.d1(i,j,k,26)*rect.hy))/(1+rect.d1(i,j,k,28)*rect.tau/(2*rect.d1(i,j,k,26)));
                da.q(i,j,k,4) = (1-rect.d1(i,j,k,28)*rect.tau/(2*rect.d1(i,j,k,26)))/(1+rect.d1(i,j,k,28)*rect.tau/(2*rect.d1(i,j,k,26)));
                da.q(i,j,k,5) = (rect.tau/(rect.d1(i,j,k,26)*rect.hz))/(1+rect.d1(i,j,k,28)*rect.tau/(2*rect.d1(i,j,k,26)));
                da.q(i,j,k,6) = (1-rect.d1(i,j,k,29)*rect.tau/(2*rect.d1(i,j,k,27)))/(1+rect.d1(i,j,k,29)*rect.tau/(2*rect.d1(i,j,k,27)));
                da.q(i,j,k,7) = (rect.tau/(rect.d1(i,j,k,27)*rect.hx))/(1+rect.d1(i,j,k,29)*rect.tau/(2*rect.d1(i,j,k,27)));
                da.q(i,j,k,8) = (1-rect.d1(i,j,k,29)*rect.tau/(2*rect.d1(i,j,k,27)))/(1+rect.d1(i,j,k,29)*rect.tau/(2*rect.d1(i,j,k,27)));
                da.q(i,j,k,9) = (rect.tau/(rect.d1(i,j,k,27)*rect.hy))/(1+rect.d1(i,j,k,29)*rect.tau/(2*rect.d1(i,j,k,27)));
                da.q(i,j,k,10) = (1-rect.d1(i,j,k,29)*rect.tau/(2*rect.d1(i,j,k,27)))/(1+rect.d1(i,j,k,29)*rect.tau/(2*rect.d1(i,j,k,27)));
                da.q(i,j,k,11) = (rect.tau/(rect.d1(i,j,k,27)*rect.hz))/(1+rect.d1(i,j,k,29)*rect.tau/(2*rect.d1(i,j,k,27)));

            }
        }
    }

    /*for (i = 0; i < rect.Mx; i++) {
        for (j = 0; j < rect.My; j++) {
            for (k = 0; k < rect.Mz; k++) {
                Ca1[i][j][k] = 1;
                Cb1[i][j][k] = rect.tau/(EPS*rect.hx);
                Ca2[i][j][k] = 1;
                Cb2[i][j][k] = rect.tau/(EPS*rect.hy);
                Ca3[i][j][k] = 1;
                Cb3[i][j][k] = rect.tau/(EPS*rect.hz);
                Da1[i][j][k] = 1;
                Db1[i][j][k] = rect.tau/(MIU*rect.hx);
                Da2[i][j][k] = 1;
                Db2[i][j][k] = rect.tau/(MIU*rect.hy);
                Da3[i][j][k] = 1;
                Db3[i][j][k] = rect.tau/(MIU*rect.hz);
            }
        }
    }*/
}
