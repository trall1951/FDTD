#include "loader.h"

void loader::load(const char* filename, char* dimension, char* Mx, char* x, char* My, char* y, char* Mz, char* z,
                        char* n, char* WIDTH, char* number, char* rnumber, int* xcoord, int* ycoord, int* zcoord,
                        double* omega, int* rxcoord, int* rycoord, int* rzcoord, char* type, int* tf, int* tfcoord,
                       int* flagP, int* pCoord)
    {
        //далее жирный алгоритм разбора строки
        int i = 0, j = 0, k = 0, m, l;
        char* s = (char*)calloc(50, sizeof(char));
        char* per = (char*)calloc(50, sizeof(char));
        strcpy(s, "");
        char mytf[6][6], mytfcoord[6][6];
        char arr[1000];
        char** myxcoord, **myycoord, **myzcoord, **myrxcoord, **myrycoord, **myrzcoord, **myomega;

        FILE* in = fopen(filename, "r");
        fgets(arr, 1000, in);
        printf ("%s", arr);
        while(arr[i]!='\n') {
            m = i;
            while((arr[i]!=' ')&&(arr[i]!='\n')) {
                s[i-m] = arr[i];
                i++;
            }

            switch (k) {
            case 0:
                strncpy(dimension, s, i-m);
                printf ("dimension = %s\n", dimension);
                break;
            case 1:
                strncpy(Mx, s, i-m);
                printf ("Mx = %s\n", Mx);
                break;
            case 2:
                strncpy(x, s, i-m);
                printf ("x = %s\n", x);
                if (strcmp (dimension, "1") == 0) k = k + 4;
                break;
            case 3:
                strncpy(My, s, i-m);
                printf ("My = %s\n", My);
                break;
            case 4:
                strncpy(y, s, i-m);
                printf ("y = %s\n", y);
                if (strcmp (dimension, "2") == 0) k = k + 2;
                break;
            case 5:
                strncpy(Mz, s, i-m);
                printf ("Mz = %s\n", Mz);
                break;
            case 6:
                strncpy(z, s, i-m);
                printf ("z = %s\n", z);
                break;
            case 7:
                strncpy(n, s, i-m);
                printf ("n = %s\n", n);
                break;
            case 8:
                strncpy(WIDTH, s, i-m);
                printf ("WIDTH = %s\n", WIDTH);
                break;
            case 9:
                strncpy(number, s, i-m);
                printf ("number = %s\n", number);
                myxcoord = (char**)calloc(strtol(number, NULL, 10), sizeof(char*));
                for (l = 0; l < strtol(number, NULL, 10); l++) {
                    myxcoord[l] = (char*)calloc(strtol(number, NULL, 10), sizeof(char));
                }
                myycoord = (char**)calloc(strtol(number, NULL, 10), sizeof(char*));
                for (l = 0; l < strtol(number, NULL, 10); l++) {
                    myycoord[l] = (char*)calloc(strtol(number, NULL, 10), sizeof(char));
                }
                myzcoord = (char**)calloc(strtol(number, NULL, 10), sizeof(char*));
                for (l = 0; l < strtol(number, NULL, 10); l++) {
                    myzcoord[l] = (char*)calloc(strtol(number, NULL, 10), sizeof(char));
                }
                myomega = (char**)calloc(strtol(number, NULL, 10), sizeof(char*));
                for (l = 0; l < strtol(number, NULL, 10); l++) {
                    myomega[l] = (char*)calloc(strtol(number, NULL, 10), sizeof(char));
                }
                break;
            case 10:
                strncpy(rnumber, s, i-m);
                printf ("rnumber = %s\n", rnumber);
                myrxcoord = (char**)calloc(strtol(rnumber, NULL, 10), sizeof(char*));
                for (l = 0; l < strtol(rnumber, NULL, 10); l++) {
                    myrxcoord[l] = (char*)calloc(strtol(rnumber, NULL, 10), sizeof(char));
                }
                myrycoord = (char**)calloc(strtol(rnumber, NULL, 10), sizeof(char*));
                for (l = 0; l < strtol(rnumber, NULL, 10); l++) {
                    myrycoord[l] = (char*)calloc(strtol(rnumber, NULL, 10), sizeof(char));
                }
                myrzcoord = (char**)calloc(strtol(rnumber, NULL, 10), sizeof(char*));
                for (l = 0; l < strtol(rnumber, NULL, 10); l++) {
                    myrzcoord[l] = (char*)calloc(strtol(rnumber, NULL, 10), sizeof(char));
                }
                break;
            }

            k++;


            if ((arr[i+1] == 'h') || (arr[i+1] == 'g')) {
                k = 0;
                i = i+1;
            }

            while ((arr[i] == 'h') || (arr[i] == 'g')) {
                if (arr[i] == 'g') {
                    i = i+2;

                    type[k] = 'g';
                    m = i;
                    while((arr[i]!=' ')&&(arr[i]!='\n')) {
                        s[i-m] = arr[i];
                        i++;
                    }

                    strncpy(myxcoord[k], s, i-m);
                    xcoord[k] = strtol(myxcoord[k], NULL, 10);
                    printf ("xcoord = %d\n", xcoord[k]);
                    if (arr[i]!='\n') {
                        i++;
                    }



                    if ((strcmp(dimension, "2") == 0) || (strcmp(dimension, "3") == 0)) {
                        m = i;
                        while((arr[i]!='\n') &&(arr[i]!=' ')) {
                            s[i-m] = arr[i];
                            i++;
                        }


                        strncpy(myycoord[k], s, i-m);
                        ycoord[k] = strtol(myycoord[k], NULL, 10);
                        printf ("ycoord = %d\n", ycoord[k]);
                        if (arr[i]!='\n') {
                            i++;
                        }
                    }

                    if (strcmp(dimension, "3") == 0) {
                        m = i;
                        while((arr[i]!='\n') &&(arr[i]!=' ')) {
                            s[i-m] = arr[i];
                            i++;
                        }

                        strncpy(myzcoord[k], s, i-m);
                        zcoord[k] = strtol(myzcoord[k], NULL, 10);
                        printf ("zcoord = %d\n", zcoord[k]);
                        if (arr[i]!='\n') {
                            i++;
                        }
                    }

                }

                if (arr[i] == 'h') {
                    i = i+2;
                    type[k] = 'h';
                    strcpy(s, "");
                    m = i;
                    while((arr[i]!=' ')&&(arr[i]!='\n')) {
                        s[i-m] = arr[i];
                        i++;
                    }
                    strncpy(myxcoord[k], s, i-m);
                    xcoord[k] = strtol(myxcoord[k], NULL, 10);
                    i++;

                    if ((strcmp(dimension, "2") == 0) || (strcmp(dimension, "3") == 0)) {
                        strcpy(s, "");
                        m = i;
                        while(arr[i]!=' ') {
                            s[i-m] = arr[i];
                            i++;
                        }
                        strncpy(myycoord[k], s, i-m);
                        ycoord[k] = strtol(myycoord[k], NULL, 10);
                        i++;
                    }

                    if (strcmp(dimension, "3") == 0) {
                        strcpy(s, "");
                        m = i;
                        while (arr[i]!=' ') {
                            s[i-m] = arr[i];
                            i++;
                        }
                        strncpy(myzcoord[k], s, i-m);
                        zcoord[k] = strtol(myzcoord[k], NULL, 10);
                        i++;
                    }

                    strcpy(s, "");
                    m = i;
                    while((arr[i]!='\n') &&(arr[i]!=' ')) {
                        s[i-m] = arr[i];
                        i++;
                    }
                    strncpy(myomega[k], s, i-m);
                    omega[k] = strtod(myomega[k], NULL);
                    if (arr[i]!='\n') {
                        i++;
                    }
                    //TODO: это дело можно загнать в функцию
                }
                k++;
            }

            if (arr[i+1] == 't') {
                i = i+3;
                type[0] = 't';


                for (k = 0; k < 2*strtol(dimension, NULL, 10); k++) {
                    strcpy(s, "");
                    m = i;
                    while((arr[i]!=' ')&&(arr[i]!='\n')) {
                        s[i-m] = arr[i];
                        i++;
                    }
                    strncpy(mytf[k], s, i-m);
                    tf[k] = strtol(mytf[k], NULL, 10);
                    i++;
                }//а оно вообще нужно?

                for (k = 0; k < 2*strtol(dimension, NULL, 10); k++) {
                    strcpy(s, "");
                    m = i;
                    while((arr[i]!=' ')&&(arr[i]!='\n')) {
                        s[i-m] = arr[i];
                        i++;
                    }
                    strncpy(mytfcoord[k], s, i-m);
                    tfcoord[k] = strtol(mytfcoord[k], NULL, 10);
                    if (arr[i]!='\n') {
                        i++;
                    }
                }
                //i++;
            }



            if (arr[i] == 'r') {
                k = 0;
            }

            while (arr[i] == 'r') {
                i = i+2;
                strcpy(s, "");
                m = i;
                while((arr[i]!=' ')&&(arr[i]!='\n')) {
                    s[i-m] = arr[i];
                    i++;
                }
                strncpy(myrxcoord[k], s, i-m);
                rxcoord[k] = strtol(myrxcoord[k], NULL, 10);
                printf ("rcoordx = %d\n", rxcoord[k]);
                if (arr[i] != '\n') {
                    i++;
                }


                if ((strcmp(dimension, "2") == 0) || (strcmp(dimension, "3") == 0)) {
                    strcpy(s, "");
                    m = i;
                    while((arr[i]!='\n') &&(arr[i]!=' ')) {
                            s[i-m] = arr[i];
                            i++;
                    }
                    strncpy(myrycoord[k], s, i-m);
                    rycoord[k] = strtol(myrycoord[k], NULL, 10);
                    printf ("coords: %s %s\n", myrxcoord[k], myrycoord[k]);
                    if (arr[i] != '\n') {
                        i++;
                    }
                }

                if (strcmp(dimension, "3") == 0) {
                    strcpy(s, "");
                    m = i;
                    while((arr[i]!='\n') &&(arr[i]!=' ')) {
                            s[i-m] = arr[i];
                            i++;
                    }
                    strncpy(myrzcoord[k], s, i-m);
                    rzcoord[k] = strtol(myrzcoord[k], NULL, 10);
                    if (arr[i] != '\n') {
                        i++;
                    }
                }

                k++;
            }


            if (arr[i] == 'p') {
                flagP[0] = 1;
                i = i+2;
                pCoord[1] = (int)arr[i];

                if ((strcmp(dimension, "2") == 0) || (strcmp(dimension, "3") == 0)) {
                    pCoord[2] = (int)arr[i+2];
                }

                if (strcmp(dimension, "3") == 0) {
                    pCoord[3] = (int)arr[i+4];
                }
                break;
            }


            if (arr[i] != '\n') {
                i++;
            }
        }
        fclose(in);
        free(s);

        for (l = 0; l < strtol(number, NULL, 10); l++) {
            free(myxcoord[l]);
        }
        free(myxcoord);
        for (l = 0; l < strtol(number, NULL, 10); l++) {
            free(myycoord[l]);
        }
        free(myycoord);
        for (l = 0; l < strtol(number, NULL, 10); l++) {
            free(myzcoord[l]);
        }
        free(myzcoord);
        for (l = 0; l < strtol(rnumber, NULL, 10); l++) {
            free(myrxcoord[l]);
        }
        free(myrxcoord);
        for (l = 0; l < strtol(rnumber, NULL, 10); l++) {
            free(myrycoord[l]);
        }
        free(myrycoord);
        for (l = 0; l < strtol(rnumber, NULL, 10); l++) {
            free(myrzcoord[l]);
        }
        free(myrzcoord);
        for (l = 0; l < strtol(number, NULL, 10); l++) {
            free(myomega[l]);
        }
        free(myomega);

    }

    void loader::load_array (const char* filename, int M, double** arr, char a)
    {
        double c = 3.0e8;
        double MIU = 4.0*3.14*1.0e-7;
        double EPS = 1.0 / (c*c*MIU);
        int i, j, k = 0, l, m;
        FILE* in = fopen(filename, "r");
        char* s = (char*)calloc(20*M, sizeof(char));
        char* s1 = (char*)calloc(20, sizeof(char));
        char*** s2 = (char***)calloc(M, sizeof(char**));

        for (i = 0; i < M; i++) {
            s2[i] = (char**)calloc(M, sizeof(char*));
        }

        for (i = 0; i < M; i++) {
            for (j = 0; j < M; j++) {
                s2[i][j] = (char*)calloc((20), sizeof(char));
            }
        }

        strcpy(s, "");
        strcpy(s1, "");

        while(fgets(s, 1000, in)!=NULL) {
            j = 0;
            for (i = 0; i < M; i++) {
                l = j;
                while ((s[j]!=' ')&&(s[j] != '\n')) {
                    s1[j-l] = s[j];
                    j++;
                }
                strncpy(s2[k][i], s1, j-l);
                arr[k][i] = atof(s2[k][i]);
                printf("arr[%d][%d] = %f\n", k, i, arr[k][i]);
                strcmp(s1, "");
                j++;
            }
            k++;
        }
        if (a == 'e') {
            for (i = 0; i < M; i++) {
                for (j = 0; j < M; j++) {
                    arr[i][j] = arr[i][j]*EPS;
                }
            }
        }
        if (a == 'm') {
            for (i = 0; i < M; i++) {
                for (j = 0; j < M; j++) {
                    arr[i][j] = arr[i][j]*MIU;
                }
            }
        }

        fclose(in);
    }

    void loader::load_array3d (const char* filename, int M, double*** arr)
    {
        int i, j, k, l, m;
        FILE* in = fopen(filename, "r");
        char* s = (char*)calloc(20*M, sizeof(char));
        char* s1 = (char*)calloc(20, sizeof(char));
        char**** s3 = (char****)calloc(M, sizeof(char***));

        for (i = 0; i < M; i++) {
            s3[i] = (char***)calloc(M, sizeof(char**));
        }

        for (i = 0; i < M; i++) {
            for (j = 0; j < M; j++) {
                s3[i][j] = (char**)calloc(M, sizeof(char*));
            }
        }

        for (i = 0; i < M; i++) {
            for (j = 0; j < M; j++) {
                for (k = 0; k < M; k++) {
                    s3[i][j][k] = (char*)calloc(20, sizeof(char));
                }
            }
        }

        strcpy(s, "");
        strcpy(s1, "");

        k = 0;

        while(fgets(s, 1000, in)!=NULL) {
            j = 0;
            m = k/(M+1);
            printf ("m = %d\n", m);
            for (i = 0; i < M; i++) {
                l = j;
                while ((s[j]!=' ')&&(s[j] != '\n')) {
                    s1[j-l] = s[j];
                    j++;
                }
                strncpy(s3[k%M][i][m], s1, j-l);
                arr[k%M][i][m] = atof(s3[k%M][i][m]);
                strcmp(s1, "");
                j++;
            }
            k++;
        }

        fclose(in);
    }








