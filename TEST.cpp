#include "Matrix.h"
#include "TEST.h"
#include <vector>
#include <cmath>

//тесты на первое задание
void DEFMatrix(){
  Matrix M;
  if (M.Num_line() != 0 || M.Num_column() != 0 || M.GetMatrix().size() != 0) throw 1;
}

void Create_matrix(Matrix& a){
  a.Element_ij(0,0) = 5;
  a.Element_ij(0,1) = 8; 
  a.Element_ij(0,2) = -7;
  a.Element_ij(1,0) = 98;
  a.Element_ij(1,1) = 3;
  a.Element_ij(1,2) = 34; 
  a.Element_ij(2,0) = 2;
  a.Element_ij(2,1) = 3;  
  a.Element_ij(2,2) = -3;
}

void Create_matrix2(Matrix& a){
  a.Element_ij(0,0) = -3;
  a.Element_ij(0,1) = 4; 
  a.Element_ij(0,2) = -2;
  a.Element_ij(1,0) = 1;
  a.Element_ij(1,1) = 0;
  a.Element_ij(1,2) = 89; 
  a.Element_ij(2,0) = 23;
  a.Element_ij(2,1) = 13;  
  a.Element_ij(2,2) = -73;
}

void VALMatrix(){
  Matrix M(3,3);
  Create_matrix(M);
  vector<vector<int>> m = {{5,8,-7},{98,3,34},{2,3,-3}}; 
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      if (M.Element_ij(i,j)  != m[i][j]) throw 2;
    }
  }
}

void SUMMatrix(){
  Matrix M(3,3), A(3,3);
  Create_matrix(M);
  Create_matrix2(A);
  Matrix W = M + A;
  vector<vector<int>> m = {{2,12,-9},{99,3,123},{25,16,-76}}; 
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      if (W.Element_ij(i,j)  != m[i][j]) throw 3;
    }
  }
}

void DIFMatrix(){
  Matrix M(3,3), A(3,3);
  Create_matrix(M);
  Create_matrix2(A);
  Matrix W = M - A;
  vector<vector<int>> m = {{8,4,-5},{97,3,-55},{-21,-10,70}}; 
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      if (W.Element_ij(i,j)  != m[i][j]) throw 4;
    }
  }  
}

void Create_matrix3(Matrix& a){
  a.Element_ij(0,0) = -1;
  a.Element_ij(0,1) = 0; 
  a.Element_ij(1,0) = 3;
  a.Element_ij(1,1) = 15;
  a.Element_ij(2,0) = 23;
  a.Element_ij(2,1) = 3;
}

void COMMatrix(){
  Matrix M(3,3), A(3,2);
  Create_matrix(M);
  Create_matrix3(A);
  Matrix W(3,2);
  W = M * A;
  vector<vector<int>> m = {{-142,99},{693,147},{-62,36}}; 
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 2; ++j){
      if (W.Element_ij(i,j)  != m[i][j]) throw 5;
    }
  }  
}

void COMMatrixNum(){
  Matrix M(3,3);
  Create_matrix2(M);
  int b = 5;
  M = M * b;
  vector<vector<int>> m = {{-15,20,-10},{5,0,445},{115,65,-365}}; 
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      if (M.Element_ij(i,j)  != m[i][j]) throw 6;
    }
  }
}

void HadamardMatrix(){
  Matrix M(3,3), A(3,3);
  Create_matrix(M);
  Create_matrix2(A);
  M = Hadamart(M, A);
  vector<vector<int>> m = {{-15,32,14},{98,0,3026},{46,39,219}};
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      if (M.Element_ij(i,j)  != m[i][j]) throw 7;
    }
  }
}


void Test1(){
  try{
    DEFMatrix(); //создание матрицы по умолчанию
    VALMatrix(); //содание матрицы с заданными значениям
    SUMMatrix(); //сложение матриц
    DIFMatrix(); //разность матриц
    COMMatrix(); //умножение матриц
    COMMatrixNum(); //умножение матрицы на число
    HadamardMatrix(); //произведение Адамара
  }catch (int t){
    cout << "Ошибка в ";
    if (t == 1) cout << "создании матрицы по умолчанию.";
    if (t == 2) cout << "создании матрицы с определенными значениями.";
    if (t == 3) cout << "сложении матриц.";
    if (t == 4) cout << "разности матриц.";
    if (t == 5) cout << "умножении матриц.";
    if (t == 6) cout << "умножении матрицы на число.";
    if (t == 7) cout << "произведении Адамара.";
  }
  cout << "Test1 пройден." << endl;
}

//тесты на второе задание
void TRACEMatrix(){
  Matrix M(3,3), A(3,3);
  Create_matrix(M);
  Create_matrix2(A);
  if (Trace(M) != 5  || Trace(A) != -76) throw 1;  
}

void DETMatrix(){
  Matrix M(2,2), A(3,3);
  Create_matrix2(A);
  M.Element_ij(0, 0) = 2;
  M.Element_ij(0, 1) = 3;
  M.Element_ij(1, 0) = -8;
  M.Element_ij(1, 1) = 4;
  if ((Determinant(A) != 11925) || Determinant(M) != 32) throw 2;
}

void Create_vector(Matrix& a){
  a.Element_ij(0,0) = -1;
  a.Element_ij(0,1) = 3; 
  a.Element_ij(0,2) = 7;
  a.Element_ij(0,3) = -9;
  a.Element_ij(0,4) = 4; 
  a.Element_ij(0,5) = 2;
  a.Element_ij(0,6) = -7;
}

void Create_vector2(Matrix& a){
  a.Element_ij(0,0) = -2;
  a.Element_ij(1,0) = 8;
  a.Element_ij(2,0) = -5;
  a.Element_ij(3,0) = -7;
  a.Element_ij(4,0) = 6;
  a.Element_ij(5,0) = -8;
  a.Element_ij(6,0) = 0;
}

void ScaVec(){
  Matrix a(1,7), b(7,1);
  Create_vector(a);
  Create_vector2(b);
  double scalar = Scalar_product(a, b);
  if (scalar != 62) throw 3;  
}

void NORME(){
  Matrix a(1,7), b(7,1);
  Create_vector(a);
  Create_vector2(b);
  if (abs(Euclidean_norm(a) - 14.45683) > 0.0001 || abs(Euclidean_norm(b) - 15.55635) > 0.0001) throw 4;
}

void NORMMAX(){
  Matrix a(1,7), b(7,1);
  Create_vector(a);
  Create_vector2(b);
  if (Maximum_norm(a) != 9 || Maximum_norm(b) != 8) throw 5;
}

void NORMMatrix(){
  Matrix A(3,2);
  Create_matrix3(A);
  if (abs(Frobenius_norm(A) - 27.80288) > 0.0001) throw 6;
}


void Test2(){
  try{
    TRACEMatrix(); //cлед матрицы
    DETMatrix(); //Определитель матрицы
    ScaVec(); //скалярное проивзедение векторов
    NORME(); // евклидова норма вектора
    NORMMAX(); // максимальная норма вектора
    NORMMatrix(); //норма Фробениуса
  }catch (int t){
    cout << "Ошибка в ";
    if (t == 1) cout << "нахождении следа матрицы.";
    if (t == 2) cout << "нахождении определителя матрицы.";
    if (t == 3) cout << "скалярном произведении векторов.";
    if (t == 4) cout << "евклидовой норме вектора.";
    if (t == 5) cout << "максимальной норме вектора.";
    if (t == 6) cout << "максимальной норме Фробениуса.";
  }
  cout << "Test2 пройден." << endl;
}

//тесты на третье задание
void angle(){
  Matrix a(1,7), b(7,1);
  Create_vector(a);
  Create_vector2(b);
  if (abs(Angle(a, b) - 74) > 0.01) throw 1;
}

void R(){
  Matrix M(3,3), A(3,2), T(2,2);
  Create_matrix(M);
  Create_matrix3(A);
  if (Rank(M) != 3 || Rank(A) != 2 || Rank(T) != 0) throw 2;
}
void revMatrix(){
  Matrix M(3,3), revM(3,3), a(3,3), b(3,3);
  Create_matrix(M);
  revM = Reverse(M);
  a = revM * M;
  b = M * revM;
  Matrix One = OneMatrix(3);
  for (int i = 0; i < 3; ++i){
    for (int j = 0; j < 3; ++j){
      if(abs(One.Element_ij(i,j) - a.Element_ij(i,j)) > 0.0001 || abs(One.Element_ij(i,j) - b.Element_ij(i,j)) > 0.0001) throw 3;
    }
  }
}

void TranMatrix(){
  Matrix M(3,3);
  Create_matrix2(M);
  vector<vector<int>> Tran = {{-3,1,23}, {4,0,13},{-2,89,-73}};
  M = Transposition(M);
  for (int i = 0; i < 3; ++i){
    for (int j = 0; j < 3; ++j){
      if(M.Element_ij(i, j) != Tran[i][j]) throw 4;
    }
  } 
}

void Test3(){
  try{
    angle(); // угол между векторами
    R(); // ранг матрицы
    revMatrix(); // обратная матрица
    TranMatrix(); // транспонированная матрицы
  }catch (int t){
    cout << "Ошибка в ";
    if (t == 1) cout << "нахождении угла между векторами.";
    if (t == 2) cout << "нахождении ранга матрицы.";
    if (t == 3) cout << "нахождении обратной матрицы.";
    if (t == 4) cout << "нахождении транспонированной матрицы.";
  }
  cout << "Test3 пройден." << endl;
}

//тесты на четвертое задание
void TextFile(){
	Matrix M(3, 3), A;
	Create_matrix2(M);
  Write_text_file("text_test.txt", M);
  A = Read_text_file("text_test.txt");
  if (A != M) throw 1;
}

void BinFile() {
	Matrix M(3, 3), A;
	Create_matrix(M);
  Write_bin_file("bin_test.bin", M);
  //cout << M << endl;
  A = Read_bin_file("bin_test.bin");
  //cout << A << endl;
	if (A != M) throw 2;
}

void Test4(){
  try{
    TextFile(); //чтение и запись в текстовый файл
    BinFile(); //чтение и запись в бинарный файл
  }catch (int t){
    cout << "Ошибка в ";
    if (t == 1) cout << "чтении и запись в текстовый файл.";
    if (t == 2) cout << "чтении и запись в бинарный файл.";
  }
  cout << "Test4 пройден." << endl;
}
