#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Matrix{
  private:
    int N_line;
    int N_column;
    vector<vector<double>> MATRIX;
  public:
  // конструкторы
  Matrix(){
    N_line = 0;
    N_column = 0;
    MATRIX.assign(0, vector<double>(0));
  };
  // c параметрами
  Matrix(int n,int m){
    N_line = n;
    N_column = m;
    MATRIX.assign(n, vector<double>(m));
  }; 
  //количество строк
  int Num_line() const{
        return N_line;
  } 
  //количество столбцов
  int Num_column() const{
        return N_column;
  }
  //элемент на месте i, j
  const double& Element_ij(int i,int j) const{
    return MATRIX.at(i).at(j);
  }

  double& Element_ij(int i,int j){
    return MATRIX[i][j];
  }
  
  const vector<vector<double>>& GetMatrix() const{
	  return MATRIX;
  }
	vector<vector<double>>& GetMatrix(){
    return MATRIX;
  }
   //1 часть
   friend Matrix operator+(const Matrix& a,const Matrix& b);//сложение матриц
   friend Matrix operator-(const Matrix& a,const Matrix& b);//разность матриц
   friend Matrix operator*(const Matrix& a,const Matrix& b);// произведение матриц
   friend Matrix operator*(const Matrix& a,const int b); //умножение на число
   friend Matrix Hadamart(const Matrix& a,const Matrix& b);//произведение Адамара
   friend ostream &operator<< (ostream &, const Matrix&);
   friend istream &operator>>(istream &, Matrix&);

   //транспонированная матрица
   friend Matrix Transposition(const Matrix& A);
};

//Подкласс единичная
class OneMatrix : public Matrix {
public:
	OneMatrix(int N) : Matrix(N, N) {
		for (int i = 0; i < N; ++i) {
      this->Element_ij(i, i) = 1;
		}
	}
};

//Подкласс диагональная
class DiagonalMatrix : public OneMatrix {
public:
	DiagonalMatrix(int N) : OneMatrix(N) {
    for(int i = 0; i < N; ++i){
      cout << "Ввод элемента: " << "[" << i << "]" << "[" << i << "]" << " ";
      double el;
      cin >> el;
      this->Element_ij(i, i) = el;
    }
  }
};

//Подкласс верхняя треугольная
class UpperTriangularMatrix : public Matrix {
public:
	UpperTriangularMatrix(int N) : Matrix(N,N) {
    for(int i = 0; i < N; ++i){
      for (int j = 0; j < N; ++j){
        if (j >= i){
          cout << "Ввод элемента: " << "[" << i << "]" << "[" << j << "]" << " ";
          double el;
          cin >> el;
          this->Element_ij(i, j) = el;
        }
      }
    }
  }
};

//Подкласс нижняя треугольная
class LowerTriangularMatrix : public Matrix {
  public:
  LowerTriangularMatrix(int N) : Matrix(N, N) {
    for(int i = 0; i < N; ++i){
      for (int j = 0; j < N; ++j){
        if (j <= i){
          cout << "Ввод элемента: " << "[" << i << "]" << "[" << j << "]" << " ";
          double el;
          cin >> el;
          this->Element_ij(i, j) = el;
        }
      }
    }
  }
};

class SymmetricalMatrix : public Matrix{
  public:
  SymmetricalMatrix(int N) : Matrix(N, N){
    for(int i = 0; i < N; ++i){
      for (int j = 0; j < N; ++j){
        double el;
        if (j == i){
          cout << "Ввод элемента: " << "[" << i << "]" << "[" << j << "]" << " ";
          double el;
          cin >> el;
          this->Element_ij(i, j) = el;
        } else if (i > j){
          cout << "Ввод элементов: " << "[" << i << "]" << "[" << j << "]" << " и " << "[" << j << "]" << "[" << i << "]" << " ";
          cin >> el;
          this->Element_ij(i, j) = el;
          this->Element_ij(j, i) = el;
        }
      }
    }
  }
};

//равенство матриц
bool operator==(const Matrix& a, const Matrix& b);
//неравенство матриц
bool operator!=(const Matrix& a, const Matrix& b);

//2 часть
//след матрицы
double Trace(const Matrix& a);
//скалярное произведение векторов
double Scalar_product(const Matrix& a, const Matrix& b);
//евклидова норма вектора
double Euclidean_norm(const Matrix& a);
//максимальная норма вектора
double Maximum_norm(const Matrix& a);
//Норма матрицы (норма Фробениуса)
double Frobenius_norm(const Matrix& a);
//определитель матрицы используя метод Гаусса
double Determinant(const Matrix& a);
//обработка по методу Гаусса верхнетреугольная матрица
void Gauss_method(Matrix& a, int cur, int& num_permutations);

//3 часть
//угол между векторами
double Angle(const Matrix& a, const Matrix& b);//транспонированная матрица
Matrix Transposition(const Matrix& A);
//ранг матрицы используя алгоритм Гаусса
int Rank(const Matrix& A);
//обратная матрица
Matrix Reverse(const Matrix& A);
//для обнуления треугольника над диагональю
void Lower_Gauss(Matrix& a, int cur);

//4 часть
//запись в текстовый файл
void Write_text_file(const string& file, const Matrix& M);
//чтение из текстового файла
Matrix Read_text_file(const string& file);
//запись в бинарный файл
void Write_bin_file(const string& file, const Matrix& M);
//чтение из бинарного файла
Matrix Read_bin_file(const string& file);


