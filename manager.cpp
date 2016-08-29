#include <stdio.h>
#include <omp.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <errno.h>
#include <sys/time.h>
#include "vtk.h"

#include "grid.h"
#include "outline.h"
#include "grid3d.h"
#include "outline3d.h"
#include "loader.h"



#include "rgrid/darray.h"

//using namespace std;

/*#include "grid3d.h"
#include "outline3d.h"
#include "grid1d.h"
#include "outline1d.h"*/

typedef rgrid::DArray<double, double> DArray;


int main (int argc, char** argv)
{
    if ((argc != 3)) {
        printf ("wrong input! need 2 arguments\n");
        return 0;
    }
    int i, dimension, Mx, My, Mz, n, WIDTH, number, rnumber;
    double x, y, z;
    double hx, hy, hz;

    //все эти переменные чтобы в loader подать в каччестве аргументов; loader читает из файла размеры сетки,
    //размеры граничных условий, типы и число источников и т.д.

    //мы подаем в loader строки; в качестве параметра выбрано 5, т.к. координаты и число источников
    //не должны быть более, чем 5-значными
    char* mydimension = (char*)calloc(2, sizeof(char));
    int* pCoord = (int*)calloc(5, sizeof(int));
    char* myMx = (char*)calloc(5, sizeof(char));
    char* myMy = (char*)calloc(5, sizeof(char));
    char* myMz = (char*)calloc(5, sizeof(char));
    char* myx = (char*)calloc(5, sizeof(char));
    char* myy = (char*)calloc(5, sizeof(char));
    char* myz = (char*)calloc(5, sizeof(char));
    char* myn = (char*)calloc(5, sizeof(char));
    char* myWIDTH = (char*)calloc(5, sizeof(char));
    char* mynumber = (char*)calloc(5, sizeof(char));
    char* myrnumber = (char*)calloc(5, sizeof(char));

    //6 задано в соответствии с числом параметров в массивах для плоской волны(см loader или README)
    int* tf = (int*)calloc(6, sizeof(int));
    int* flagP = (int*)calloc(6, sizeof(int));
    int* tfcoord = (int*)calloc(6, sizeof(int));

    int num, rnum;//число источников и отражателей




    num = strtol(argv[1], NULL, 10);
    rnum = strtol(argv[2], NULL, 10);
    printf ("rnum = %d\n", rnum);

    char* type = (char*)calloc(num, sizeof(char));
    int* xcoord = (int*)calloc(num, sizeof(int));
    int* ycoord = (int*)calloc(num, sizeof(int));
    int* zcoord = (int*)calloc(num, sizeof(int));
    double* omega = (double*)calloc(num, sizeof(int));
    int* rxcoord = (int*)calloc(rnum, sizeof(int));
    int* rycoord = (int*)calloc(rnum, sizeof(int));
    int* rzcoord = (int*)calloc(rnum, sizeof(int));



    loader::load("in.txt", mydimension, myMx, myx, myMy, myy, myMz, myz, myn, myWIDTH, mynumber, myrnumber, xcoord, ycoord, zcoord,
                                                                        omega, rxcoord, rycoord, rzcoord, type, tf, tfcoord, flagP, pCoord);
    int pflag = flagP[0];//здесь не используется, но отвечает за периодичность
    dimension = strtol(mydimension, NULL, 10);//число измерений
    Mx = strtol(myMx, NULL, 10);//число ячеек по каждой координате (соответственно, х, y, z)
    My = strtol(myMy, NULL, 10);
    Mz = strtol(myMz, NULL, 10);
    x = atof(myx);//размер области в метрах по каждой координате
    y = atof(myy);
    z = atof(myz);
    n = strtol(myn, NULL, 10);//число шагов по времени
    WIDTH = strtol(myWIDTH, NULL, 10);//размер граничных поглощающих PML условий
    number = strtol(mynumber, NULL, 10);//число источников
    rnumber = strtol(myrnumber, NULL, 10);//число точек, в которых позже поставим отражающие граничные условия

    hx = (double)x/(double)Mx;//размер ячейки сетки по каждой координате
    hy = (double)y/(double)My;
    hz = (double)z/(double)Mz;

    char* name = (char*) malloc (sizeof(char));//тип сетки; пока только прямоугольные, но потом будут и другие
    strcpy(name, "rect");


    //далее в зависимости от числа измерений все происходит.

    /*if (dimension == 1) {
        grid1d rect(name, hx, Mx);
        outline1d fdtd (rect);
        fdtd.calculate(fdtd, rect, number, type, xcoord, omega, n, WIDTH, rxcoord, rnumber, tf, tfcoord, pflag, pCoord);
        free(rect.E);
        free(rect.H);
        free(rect.eps);
        free(rect.miu);
        free(rect.sigma);
        free(rect.sigma1);
        support::my_free2(rect.Ez, rect.M, rect.M);
        support::my_free2(rect.Hy, rect.M, rect.M);
    }*/


    if (dimension == 2) {
        grid rect(name, hx, hy, Mx, My);
        //loader::load_array("eps.txt", M, rect.eps, 'e');
        //loader::load_array("miu.txt", M, rect.miu, 'm');

        //TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //вообще говоря, надо все 4 массива из файлов грузить. При желании все, что надо, - создать
        //еще 3 файла, убрать пару строчек в rect и раскомментить 3 строчки тут, но все время менять
        //содержимое этих входных файлов - большой геморрой, так что пока прога на стадии тестинга,
        //обойдемся этой одной подгрузкой

        //loader::load_array("sigma.txt", M, rect.sigma, 's');
        //loader::load_array("sigma.txt", M, rect.sigma1, 's');
        outline fdtd (rect);
        fdtd.calculate(fdtd, rect, number, type, xcoord, ycoord, omega, n, WIDTH, rxcoord, rycoord, rnumber, tf, tfcoord);
    }


    if (dimension == 3) {
        grid3d rect(name, hx, hy, hz, Mx, My, Mz);
        //loader::load_array3d("sigma1.txt", M, rect.sigma);
        outline3d fdtd (rect);
        fdtd.calculate(fdtd, rect, number, type, xcoord, ycoord, zcoord, omega, n, WIDTH, rxcoord, rycoord, rzcoord, rnumber, tf, tfcoord);
    }



    free(mydimension);
    free(myMx);
    free(myx);
    free(myMy);
    free(myy);
    free(myMz);
    free(myz);
    free(myn);
    free(myWIDTH);
    free(mynumber);
    free(myrnumber);
    free(xcoord);
    free(ycoord);
    free(zcoord);
    free(omega);
    free(rxcoord);
    free(rycoord);
    free(rzcoord);
    free(type);
    free(flagP);
    free(pCoord);

    return 0;
}









