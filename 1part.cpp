#include "Matrix.h"

//перегрузка оператора сложения
Matrix operator+(const Matrix& a,const Matrix& b) {
  if (a.Num_line() != b.Num_line() || a.Num_column() != b.Num_column()) throw runtime_error("Матрицы нельзя сложить, так как они разной размерности.");
  int N = a.Num_line(), M = a.Num_column(); 
  Matrix result(N, M);
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < M; ++j)
    {
      result.MATRIX[i][j] = a.Element_ij(i, j) + b.Element_ij(i, j);
    }
  }
  return result;
}

//перегрузка оператора вычитания
Matrix operator-(const Matrix& a,const Matrix& b) {
  if (a.Num_line() != b.Num_line() || a.Num_column() != b.Num_column()) throw runtime_error("Нельзя найти разность матриц, так как у них разные размерности.");
  int N = a.Num_line(), M = a.Num_column(); 
  Matrix result(N, M);
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < M; ++j)
    {
      result.MATRIX[i][j] = a.Element_ij(i, j) - b.Element_ij(i, j);
    }
  }
  return result;
}

//перегрузка оператора умножения
Matrix operator*(const Matrix& a,const Matrix& b){
  if (a.Num_column() != b.Num_line()) throw runtime_error("Нельзя найти произведение матриц так как количество столбцов первой матрице не равно количеству строк во второй.");
  else {
    int N = a.Num_line(), M = b.Num_column();
    Matrix result(N, M);
    for (int i = 0; i < N; i++){
      for (int j = 0; j < M; j++){
        double res = 0;
        for (int k = 0; k < a.Num_column(); k++){
          res += a.Element_ij(i, k) * b.Element_ij(k, j);
        }
        if (abs(res) < 0.000001) res = 0; 
        result.MATRIX[i][j] = res;
    }
  }
  return result;
  }
}

//перегрузка оператора умножения на число
Matrix operator*(const Matrix& a,const int b){
    int N = a.Num_line(), M = a.Num_column();
    Matrix result(N, M);
    for (int i = 0; i < N; i++){
      for (int j = 0; j < M; j++){
        result.MATRIX[i][j] = b * a.Element_ij(i, j);
    }
  }
  return result;
}

//произведение Адамара
Matrix Hadamart(const Matrix& a,const Matrix& b){
  if (a.Num_column() != b.Num_column() || a.Num_line() != b.Num_line()) throw runtime_error("Нельзя найти так как матрицы имеют разную размерность.");
  int N = a.Num_line(), M = a.Num_column();
  Matrix result(N, M);
  for(int i=0; i < N; i++)
  {
    for(int j=0; j < M; j++)
    {
      result.MATRIX[i][j] = a.Element_ij(i, j) * b.Element_ij(i, j);
    }
  }
  return result;
}






