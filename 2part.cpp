#include "Matrix.h"
#include <cmath>
#include <algorithm> 

//след матрицы
double Trace(const Matrix& a){
   if (a.Num_line() != a.Num_column()) throw runtime_error("Нельзя найти след, так как матрица не квадратная, количество столбцов не равно количеству строк.");
   double trace = 0;
   for(int i=0; i < a.Num_line(); i++)
  {
    for(int j=0; j < a.Num_column(); j++)
    {
      if (i == j) trace += a.Element_ij(i, j);
    }
  }
  return trace;
}

//скалярное произведение векторов
double Scalar_product(const Matrix& a, const Matrix& b){
  if ((a.Num_line() != 1 && a.Num_column() != 1) || (b.Num_line() != 1 && b.Num_column() != 1)) throw runtime_error("Нельзя найти скалярное произведение, так как один из элементов не вектор.");
  double scalar = 0;
  if ((a.Num_line() == b.Num_line() && a.Num_column() == b.Num_column()) || (a.Num_line() == b.Num_column() && b.Num_line() == a.Num_column())){
    vector<double> v1, v2;
    for(int i=0; i < a.Num_line(); i++)
      for(int j=0; j < a.Num_column(); j++)
        v1.push_back(a.Element_ij(i, j));
    for(int i=0; i < b.Num_line(); i++)
      for(int j=0; j < b.Num_column(); j++)
        v2.push_back(b.Element_ij(i, j));
    int N1 = a.Num_line();
    if (N1 < a.Num_column()) N1 = a.Num_column();
    for(int i = 0; i < N1; i++){
      scalar += v1[i] * v2[i];
    }
  } else throw runtime_error("Нельзя найти скалярное произведение, так как вектора имеют разную длину.");
  return scalar;
}

//евклидова норма вектора
double Euclidean_norm(const Matrix& a){
  if (a.Num_line() != 1 && a.Num_column() != 1) throw runtime_error("Нельзя найти евклидову норму вектора, так как это матрица, а не вектор.");
  double norm = 0;
  for(int i=0; i < a.Num_line(); i++)
  {
    for(int j=0; j < a.Num_column(); j++)
    {
      norm += a.Element_ij(i, j) * a.Element_ij(i, j);
    }
  }
  return sqrt(norm);
}

//максимальная норма вектора
double Maximum_norm(const Matrix& a){
  if (a.Num_line() != 1 && a.Num_column() != 1) throw runtime_error("Нельзя найти максимальную норму вектора, так как это матрица, а не вектор.");
  double norm = 0;
  for(int i=0; i < a.Num_line(); i++)
  {
    for(int j=0; j < a.Num_column(); j++)
    {
      if (norm < abs(a.Element_ij(i, j))) norm = abs(a.Element_ij(i, j));
    }
  }
  return norm;
}

//Норма матрицы (норма Фробениуса)
double Frobenius_norm(const Matrix& a){
  double F = 0;
   for(int i = 0; i < a.Num_line(); i++)
      for(int j = 0; j < a.Num_column(); j++)
        F += a.Element_ij(i, j) * a.Element_ij(i, j);
  return sqrt(F);
}

//обработка по методу Гаусса верхнетреугольная матрица
void Gauss_method(Matrix& a, int cur, int& num_permutations) {
  int ROW = a.Num_line(), COL = a.Num_column(), i_max = -1;
	auto& M = a.GetMatrix(); double max_v;
	bool f = true;
	for (int i = cur; i < ROW; i++) {
		if (f){ i_max = i;
			max_v = a.Element_ij(i, cur);
			f = false;
    } else {
			if (a.Element_ij(i, cur) > max_v) {
				max_v = a.Element_ij(i, cur);
				i_max = i;}
		  }
	}
	if (cur != i_max) { //перемещаем строки
		swap(M[cur], M[i_max]);
		num_permutations++;
	}
	for (int i = cur + 1; i < ROW; i++) {
		if (M[cur][cur] == 0)
			break;
		double coeff = M[i][cur] / M[cur][cur];
		for (int j = 0; j < COL; j++) {
			M[i][j] -= M[cur][j] * coeff;
			if (abs(M[i][j] - 0) < 0.00001) M[i][j] = 0;
		}
	}
}

//определитель матрицы используя метод Гаусса
double Determinant(const Matrix& a){
    if (a.Num_column() != a.Num_line()) throw runtime_error("Нельзя посчитать определитель методом Гаусса, так как матрица не квадратная.");
    if (a.Num_column() == 0 || a.Num_line() == 0) throw runtime_error("Нельзя посчитать определитель для пустой матрицы.");
    int N = a.Num_line(), num_permutations = 0;
    Matrix A = a;
    //вызов обработки строк
    for (int i = 0; i < N; i++){
      Gauss_method(A, i, num_permutations);
    }
    double determ = 1;
    for (int i = 0; i < A.Num_line(); i++) {
			determ *= A.Element_ij(i, i);
		}
    if (determ == 0) return determ;
    else{
      return (pow(-1, num_permutations) * determ);
    }
}
