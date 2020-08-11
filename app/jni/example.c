//
// Created by jaroslav on 03.05.19.
//

/* File : example.c */
#include <malloc.h>
#include <stdlib.h>
#include <omp.h>

/* A global variable */
double Foo = 3.0;
int ra, ca, rb, cb;
int **matrixA;
int **matrixB;

/* Compute the greatest common divisor of positive integers */
int gcd(int x, int y) {
  int g;
  g = y;
  while (x > 0) {
    g = x;
    x = y % x;
    y = g;
  }
  return g;
}

void randomMatrix(int **matrix, int n, int m);

int** initMatrix(int rowLenA, int columnLenA, int rowLenB, int columnLenB) {

  ra = rowLenA;
  ca = columnLenA;
  rb = rowLenB;
  cb = columnLenB;

  if (columnLenA != rowLenB) {
    return NULL;
  }

  int **result;
  result = (int**)malloc(sizeof(int*)*ra);
  for(int i = 0; i < ra; i++) {
    result[i] = (int*)malloc(sizeof(int)*cb);
  }

  matrixA = (int**)malloc(sizeof(int*)*ra);
  for(int i = 0; i < ra; i++) {
    matrixA[i] = (int*)malloc(sizeof(int)*ca);
  }

  matrixB = (int**)malloc(sizeof(int*)*rb);
  for(int i = 0; i < rb; i++) {
    matrixB[i] = (int*)malloc(sizeof(int)*cb);
  }

  randomMatrix(matrixA,ra,ca);
  randomMatrix(matrixB,rb,cb);

    return result;
}

void randomMatrix(int **matrix, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 100;
        }
    }

}

void parallelMatrixMultiply(int **result, int numThreads, int kind, int chunkSize) {

    omp_set_dynamic(0);
    if (numThreads % omp_get_num_procs() == 0) {
        omp_set_num_threads(omp_get_num_procs());
    } else {
        omp_set_num_threads(numThreads % omp_get_num_procs());
    }

    switch (kind) {
        case 2:
            omp_set_schedule(omp_sched_dynamic,chunkSize);
            break;
        case 3:
            omp_set_schedule(omp_sched_guided,chunkSize);
            break;
        case 4:
            omp_set_schedule(omp_sched_auto, chunkSize);
            break;
        default:
            omp_set_schedule(omp_sched_static,chunkSize);
    }

    omp_set_num_threads(numThreads);
    int a, b, c;
#pragma omp parallel for shared(matrixA, matrixB, result) private(a, b, c)
    for (a = 0; a < ra; a++) {
        for (c = 0; c < cb; c++) {
            result[a][c] = 0;
            for (b = 0; b < rb; b++) {
                result[a][c] += (matrixA[a][b] * matrixB[b][c]);
            }
        }
    }
}

void matrixMultiply(int **result) {

  for (int a = 0; a < ra; a++) {
    for (int c = 0; c < cb; c++) {
      result[a][c] = 0;
      for (int b = 0; b < rb; b++) {
        result[a][c] += (matrixA[a][b] * matrixB[b][c]);
      }
    }
  }
}

int getItemFromMatrix(int **matrix, int row, int column) {
    return matrix[row][column];
}