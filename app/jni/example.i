/* File : example.i */
%module example

%inline %{
extern int    gcd(int x, int y);
extern double Foo;
extern int ra, ca, rb, cb;
extern int** initMatrix(int rowLenA, int columnLenA, int rowLenB, int columnLenB);
extern int getItemFromMatrix(int **matrix, int row, int column);
extern void parallelMatrixMultiply(int **result, int numThreads, int kind, int chunkSize);
extern void matrixMultiply(int **result);
%}