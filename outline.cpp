#include "outline.h"

/*основной класс, для произведения итераций по нашему численному методу*/

void outline::calculate (outline fdtd, grid rect, int number, char* type, int* xcoord, int* ycoord,
                                double* omega, int N, int WIDTH, int* rxcoord, int* rycoord, int rnumber,
                                int* tf, int* tfcoord)
{
    printf ("calculating...\n");
    double c = 3.0e8;
    double miu0 = 4.0*3.14*1.0e-7;
    double eps0 = 1.0 / (c*c*miu0);
    //для записи в файл
    char sE[20] = "E";
    char s1[20];
    char s2[20];

    int Mx = rect.Mx;
    int My = rect.My;
    int i=0, j=0, k;
    int n = 0;
    FILE* f;
    f = fopen("/home/anton/FDTD/p.txt", "w");
    //инициализация поглощающах граничных условий
    
    pml(WIDTH, rect, &da);
    
    //аллокация массива из источников
    source* s= (source*)calloc(number, sizeof(source));
    //printf ("%f\n", rect.d1(50,50,0,12));
    //инициализация всех источников в соответствии с их типами
    
    for (i = 0; i < number; i++) {
        switch (type[i]) {
            case 'g': s[i].init('g', xcoord[i], ycoord[i], rect); break;
            case 'h': s[i].init('h', xcoord[i], ycoord[i], rect); break;
            case 't': s[i].init_tfsf('t', xcoord[i], ycoord[i], rect); break;
        }
    }
    
    //параметр для источника, характеризующий ширину импульса
    double t = 15*rect.tau;
    //цикл, пока не сделаем количество шагов по времени, заданное во входном файле
	
    while (n < N) {
        //считаем сначала поле источников
        for (i = 0; i < number; i++) {
            if (type[i] == 'h') {
                rect.d1(xcoord[i], ycoord[i], 0, 2) = s[i].harmonic (n, omega[i], rect.d1);
            }
            if (type[i] == 'g') {
                rect.d1(xcoord[i], ycoord[i], 0, 2) = s[i].gaussian (n, rect.d1);
            }
        }
        //пишем в файл значение электрического поля
        strcpy(s2, ".vtk");
        sprintf(s1, "%d", n);
        strcat(sE, s1);
        strcat(sE, s2);
        write_to_vtk2d(rect.d1, sE, rect.Mx, rect.My, 10);//d1(10) = E?????????-----------------------------------------
        strcpy(sE, "E");

		//printf("step %d : ", n);
		//printf("E[50][50] = %f\n", rect.d1(50, 50, 0, 2));
		//printf("E[50][50] = %f\n", rect.d1(50, 50, 0, 10));
		
        //далее идут итерации по нашему численному методу
        for (i = 1; i < Mx - 1; i++) {
            for (j = 1; j < My - 1; j++) {
                rect.d1(i,j,0,9) = da.q(i,j,0,6)*rect.d1(i,j,0,8) + da.q(i,j,0,7) *
                        (rect.d1(i+1,j,0,0) - rect.d1(i,j,0,0) + rect.d1(i+1,j,0,2) - rect.d1(i,j,0,2));

                rect.d1(i,j,0,7) = da.q(i,j,0,4)*rect.d1(i,j,0,6) - da.q(i,j,0,5) *
                        (rect.d1(i,j+1,0,0) - rect.d1(i,j,0,0) + rect.d1(i,j+1,0,2) - rect.d1(i,j,0,2));
//случай источника типа "плоская волна" - особый; в нем нужно поля пересчитывать определенным образом
                if(type[0] == 't') {
                    if ((j == tfcoord[0]-1)&&(tf[0] == 1)) {
                        rect.d1(i,j,0,7) = s[0].tfsf(i, j, n, 0, 0, rect.d1, da.q, 6, 5);
                    }

                    else if ((j == tfcoord[1]-1) && (tf[1] == 1)) {
                        rect.d1(i,j,0,7) = s[0].tfsf(i, j, n, 0, 0, rect.d1, da.q, 6, 5);
                    }

                    else if ((i == tfcoord[2]-1) && (tf[2] == 1)) {
                        rect.d1(i,j,0,9) = s[0].tfsf(i, j, n, 0, 1, rect.d1, da.q, 8, 7);
                    }

                    else if ((i == tfcoord[3]-1) && (tf[3] == 1)) {
                        rect.d1(i,j,0,9) = s[0].tfsf(i, j, n, 0, 1, rect.d1, da.q, 8, 7);
                    }
                }
            }
        }

        for (i = 1; i < Mx - 1; i++) {
            for (j = 1; j < My - 1; j++) {
                rect.d1(i,j,0,8) = rect.d1(i,j,0,9);
                rect.d1(i,j,0,6) = rect.d1(i,j,0,7);
                rect.d1(i,j,0,11) = sqrt(rect.d1(i,j,0,6)*rect.d1(i,j,0,6)+rect.d1(i,j,0,8)*rect.d1(i,j,0,8));
            }
        }
        for (i = 1; i < Mx - 1; i++) {
            for (j = 1; j < My - 1; j++) {

                rect.d1(i,j,0,1) = da.q(i,j,0,0) * rect.d1(i,j,0,0) - da.q(i,j,0,1) *
                                        (rect.d1(i,j,0,6) - rect.d1(i,j-1,0,6));

                rect.d1(i,j,0,3) = da.q(i,j,0,2) * rect.d1(i,j,0,2) + da.q(i,j,0,3) *
                                        (rect.d1(i,j,0,8) - rect.d1(i-1,j,0,8));

//случай источника типа "плоская волна" - особый; в нем нужно поля пересчитывать определенным образом
                if (type[0] == 't') {

                    if ((j == tfcoord[0]-1)&&(tf[0] == 1)) {
                        rect.d1(i,j,0,1) = s[0].tfsf(i, j, n, 1, 0, rect.d1, da.q, 0, 1);
                    }

                    else if ((j == tfcoord[1]-1)&&(tf[1] == 1)) {
                        rect.d1(i,j,0,1) = s[0].tfsf(i, j, n, 1, 0, rect.d1, da.q, 0, 1);
                    }

                    else if ((i == tfcoord[2]-1)&&(tf[2] == 1)) {
                        rect.d1(i,j,0,3) = s[0].tfsf(i, j, n, 1, 1, rect.d1, da.q, 2, 3);
                    }

                    else if ((i == tfcoord[3]-1)&&(tf[3] == 1)) {
                        rect.d1(i,j,0,3) = s[0].tfsf(i, j, n, 1, 1, rect.d1, da.q, 2, 3);
                    }
                }
            }
        }

        /*for (k = 0; k < rnumber; k++) {
            reflect::reflection(rxcoord[k], rycoord[k], rect.Ezx, rect.Ezy, rect.Ez, rect.Hx, rect.Hy);
        }*/

        for (i = 1; i < Mx - 1; i++) {
            for (j = 1; j < My - 1; j++) {
                rect.d1(i,j,0,5) = rect.d1(i,j,0,1) + rect.d1(i,j,0,3);
            }
        }

        for (i = 1; i < Mx - 1; i++) {
            for (j = 1; j < My - 1; j++) {
                rect.d1(i,j,0,0) = rect.d1(i,j,0,1);
                rect.d1(i,j,0,2) = rect.d1(i,j,0,3);
                rect.d1(i,j,0,4) = rect.d1(i,j,0,5);
                rect.d1(i,j,0,10) = (rect.d1(i,j,0,4));
            }
        }


        n = n + 1;
    }
    fclose(f);

}


//инициализация массивов коэффициентов для нашего метода

outline::outline (grid rect)
{
    da.q.resize(rect.Mx, rect.My, 1, 8);
    
    int i, j;

    double c = 3.0e8;
    double MIU = 4.0*3.14*1.0e-7;
    double EPS = 1.0 / (c*c*MIU);//TODO: запихать в другое место

    for (i = 0; i < rect.Mx; i++) {
        for (j = 0; j < rect.My; j++) {
            da.q(i, j, 0, 0) = (1-rect.d1(i, j, 0, 14)*rect.tau/(2*rect.d1(i, j, 0, 12)))/(1+rect.d1(i, j, 0, 14)*rect.tau/(2*rect.d1(i, j, 0, 12)));
            da.q(i, j, 0, 1) = (rect.tau/(rect.d1(i, j, 0, 12)*rect.hx))/(1+rect.d1(i, j, 0, 14)*rect.tau/(2*rect.d1(i, j, 0, 12)));
            da.q(i, j, 0, 2) = (1-rect.d1(i, j, 0, 14)*rect.tau/(2*rect.d1(i, j, 0, 12)))/(1+rect.d1(i, j, 0, 14)*rect.tau/(2*rect.d1(i, j, 0, 12)));
            da.q(i, j, 0, 3) = (rect.tau/(rect.d1(i, j, 0, 12)*rect.hy))/(1+rect.d1(i, j, 0, 14)*rect.tau/(2*rect.d1(i, j, 0, 12)));
            da.q(i, j, 0, 4) = (1-rect.d1(i, j, 0, 15)*rect.tau/(2*rect.d1(i, j, 0, 13)))/(1+rect.d1(i, j, 0, 15)*rect.tau/(2*rect.d1(i, j, 0, 13)));
            da.q(i, j, 0, 5) = (rect.tau/(rect.d1(i, j, 0, 13)*rect.hx))/(1+rect.d1(i, j, 0, 15)*rect.tau/(2*rect.d1(i, j, 0, 13)));
            da.q(i, j, 0, 6) = (1-rect.d1(i, j, 0, 15)*rect.tau/(2*rect.d1(i, j, 0, 13)))/(1+rect.d1(i, j, 0, 15)*rect.tau/(2*rect.d1(i, j, 0, 13)));
            da.q(i, j, 0, 7) = (rect.tau/(rect.d1(i, j, 0, 13)*rect.hy))/(1+rect.d1(i, j, 0, 15)*rect.tau/(2*rect.d1(i, j, 0, 13)));
        }
    }
    //printf("Ca1[75][75] = %f\n", q(75, 75, 0, 1));
}

