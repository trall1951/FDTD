#include "vtk.h"
/*используется для записи значений полей в файлы с расширением vtk, которые
подаются на вход программе paraview*/

//num задает номер компоненты DArray (какое из полей)
void write_to_vtk3d(DArray u, const char *path, int Nx, int Ny, int Nz, int num)
{

	FILE *f;
	int i, j, k;
	f = fopen(path, "w");
	fprintf(f, "# vtk DataFile Version 3.0\n");
	fprintf(f, "Plane\n");
	fprintf(f, "ASCII\n");
	fprintf(f, "DATASET STRUCTURED_POINTS\n");
	fprintf(f, "DIMENSIONS %d %d %d\n", Nx, Ny, Nz);
	fprintf(f, "ASPECT_RATIO 1 1 1\n");
	fprintf(f, "ORIGIN 0.0 0.0 0.0\n");
	fprintf(f, "POINT_DATA %d\n", Nx*Ny*Nz);
	fprintf(f, "SCALARS volume_scalars float 1\n");
	fprintf(f, "LOOKUP_TABLE default\n");
	for (i = 0; i < Nz; i++) {
        for (j = 0; j < Ny; j++) {
            for (k = 0; k < Nx; k++) {
                fprintf(f, "%f ", u(k, i, j, num));
            }
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

void write_to_vtk2d(DArray u, const char *path, int Nx, int Ny, int num)
{

	FILE *f;
	int i, j;
	f = fopen(path, "w");
	fprintf(f, "# vtk DataFile Version 3.0\n");
	fprintf(f, "Plane\n");
	fprintf(f, "ASCII\n");
	fprintf(f, "DATASET STRUCTURED_POINTS\n");
	fprintf(f, "DIMENSIONS %d %d 1\n", Nx, Ny);
	fprintf(f, "ASPECT_RATIO 1 1 1\n");
	fprintf(f, "ORIGIN 0.0 0.0 0.0\n");
	fprintf(f, "POINT_DATA %d\n", Nx*Ny);
	fprintf(f, "SCALARS volume_scalars float 1\n");
	fprintf(f, "LOOKUP_TABLE default\n");
	for (i = 0; i < Ny; i++) {
        for (j = 0; j < Nx; j++) {
            fprintf(f, "%f ", u(j, i, 0, num));
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

void write_to_vtk1d(DArray u, const char *path, int N, int num)
{

	FILE *f;
	int i;
	f = fopen(path, "w");
	fprintf(f, "# vtk DataFile Version 3.0\n");
	fprintf(f, "Plane\n");
	fprintf(f, "ASCII\n");
	fprintf(f, "DATASET STRUCTURED_POINTS\n");
	fprintf(f, "DIMENSIONS %d 1 1\n", N);
	fprintf(f, "ASPECT_RATIO 1 1 1\n");
	fprintf(f, "ORIGIN 0.0 0.0 0.0\n");
	fprintf(f, "POINT_DATA %d\n", N);
	fprintf(f, "SCALARS volume_scalars float 1\n");
	fprintf(f, "LOOKUP_TABLE default\n");
	for (i = 0; i < N; i++) {
        fprintf(f, "%f\n", u(i, 0, 0, num));
	}
	fclose(f);
}


