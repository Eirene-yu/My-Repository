#include "Matrix.h"
#include <cmath>  

#define PI 3.14159265

//угол между векторами
double Angle(const Matrix& a, const Matrix& b){
  double rad = 0;
  if ((a.Num_line() != 1 && a.Num_column() != 1) ||(b.Num_line() != 1 && b.Num_column() != 1)) throw runtime_error("Нельзя найти угол, так как один из элементов не вектор.");
  if ((a.Num_line() == b.Num_line() && a.Num_column() == b.Num_column()) || (a.Num_line() == b.Num_column() && b.Num_line() == a.Num_column())){
    vector<double> v1, v2;
    for(int i=0; i < a.Num_line(); i++)
      for(int j=0; j < a.Num_column(); j++)
        v1.push_back(a.Element_ij(i, j));
    for(int i = 0; i < b.Num_line(); i++)
      for(int j = 0; j < b.Num_column(); j++)
        v2.push_back(b.Element_ij(i, j));
    int N1 = a.Num_line();
    if (N1 < a.Num_column()) N1 = a.Num_column();
    double num = 0, den1 = 0, den2 = 0;
    for(int i = 0; i < N1; i++){
      num += v1[i] * v2[i];
      den1 += v1[i] * v1[i];
      den2 += v2[i] * v2[i];
    }
    rad = num / (sqrt(den1) * sqrt(den2));
  } else throw runtime_error("Нельзя найти угол, так как вектора имеют разную длину.");
  return (acos(rad) * 180.0 / PI);
}

//транспонирование матрицы
Matrix Transposition(const Matrix& A){
  int N = A.Num_line();
  int M = A.Num_column(); 
  Matrix result(M, N);
  for(int i = 0; i < M; i++)
  {
    for(int j = 0; j < N; j++)
    {
      result.MATRIX[i][j] = A.Element_ij(j, i);
    }
  }
  return result;
}

//ранг матрицы используя алгоритм Гаусса
int Rank(const Matrix& A){
  int N = A.Num_line(), M = A.Num_column();
  int rank = N;
  Matrix a = A;
  int R2 = 0;
  for(int i=0; i < N; i++){
    int t = 0;
    for(int j = 0; j < M; j++){
      if (a.Element_ij(i, j) == 0) t += 1;
      if(t == M){
        ++R2;
      }
    }
  }
  if (R2 == rank) return 0;
  else{
    //вызов обработки строк
    int num_permutations = 0;
    for (int i = 0; i < min(N, M); i++){
      Gauss_method(a, i, num_permutations);
      }
      int h = N;
      for(int i=0; i < N; i++){
        int t = 0;
        for(int j = 0; j < M; j++){
          if (a.Element_ij(i, j) == 0) t += 1;
          if(t == M){
            --rank;
          }
        }
      }
    return rank;
  }
}

//для обнуления треугольника над диагональю
void Lower_Gauss(Matrix& a, int cur) {
	auto& M = a.GetMatrix();
  int ROW = a.Num_line(), COL = a.Num_column();
	for (int i = cur - 1; i >= 0; i--) {
		if (M[cur][cur] == 0)
			break;
		double coeff = M[i][cur] / M[cur][cur];
		for (int j = 0; j < COL; j++) {
			M[i][j] -= M[cur][j] * coeff;
			if (abs(M[i][j] - 0) < 0.00001)
				M[i][j] = 0;
		}
	}
}

//Обратная матрица
Matrix Reverse(const Matrix& A){
  if (A.Num_line() != A.Num_column()) throw runtime_error("Нельзя найти обратную, так как матрица не квадратная.");
  if (Determinant(A) == 0) throw runtime_error("Нельзя найти обратную матрицу, так как вырожденная, ее определитель = 0");
  int N = A.Num_line();
  Matrix result(N, 2 * N);
  int t = 0;
  for(int i=0; i < N; i++){
    for(int j = 0; j < 2 * N; j++){
      if (j < N) result.GetMatrix()[i][j] = A.Element_ij(i, j);
      else{
        if (t == i && j == t + N){
           result.GetMatrix()[i][j] = 1;
           ++t;
        } else result.GetMatrix()[i][j] = 0;
      }
    }
  }
  int num_permutations = 0;
  for (int i = 0; i < N; i++){
      Gauss_method(result, i, num_permutations);
  }
  for (int i = N - 1; i >= 0; i--)
		Lower_Gauss(result, i);
  for (int i = 0; i < N; ++i){
    double del = 1;
    for(int j = 0; j < 2 * N; ++j){
      if (i == j) del = result.Element_ij(i, j);
      result.GetMatrix()[i][j] /= del;
    }
  }
  Matrix res(N, N);
  for(int i=0; i < N; i++){
    for(int j = 0; j < N; j++){
      res.GetMatrix()[i][j] = result.GetMatrix()[i][j + N];
    }
  }
  return res;
}
