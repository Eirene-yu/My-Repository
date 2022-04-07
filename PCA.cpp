#include "PCA.h"

vector<double> aver(vector<vector<double>> M, int col, int line){
  vector<double> Average(col);
  int k = 0;
  for (auto element : M){
    for (auto el: element){
      Average[k] += el;
      ++k;}
    k = 0;
  }
  for(int i = 0; i < Average.size(); ++i){
    Average[i] /= line;
  }
  return Average;
}

//Центрирование матрицы
void PCA::Centering(){
  int line = MATRIX.Num_line();
  int col = MATRIX.Num_column();
  vector<double> Average = aver(MATRIX.GetMatrix(), col, line);
  for (auto& element : MATRIX.GetMatrix()){
    int i = 0;
    for (auto& el: element){
      el -= Average[i];
      ++i;
    }
  }
};

//Шкалирование матрицы
void PCA::Scaling(){
  //this->Centering();
  int line = MATRIX.Num_line();
  int col = MATRIX.Num_column();
  vector<double> norm(col);
  int k = 0;
  for (auto element : MATRIX.GetMatrix()){
    for (auto el: element){
      norm[k] += el * el;
      ++k;}
    k = 0;
  }
  for(int i = 0; i < norm.size(); ++i){
    norm[i] /= (line - 1);
    norm[i] = sqrt(norm[i]);
  }
  /*for(int i = 0; i < norm.size(); ++i){
    cout << norm[i] << endl;
  }*/
  for (auto& element : MATRIX.GetMatrix()){
    int i = 0;
    for (auto& el: element){
      el /= norm[i];
      ++i;
    }
  }
};

//aлгоритм NIPALS
tuple<Matrix, Matrix, Matrix> PCA::NIPALS(size_t A, double epsilon){
  //this->Centering();
  //this->Scaling();
  Matrix EE = MATRIX;
  int line = MATRIX.Num_line();
  int col = MATRIX.Num_column();
  Matrix t(line, 1), p, t_old;
  vector<Matrix> vec_t, vec_p;
  if (A == -10) A = col;
  
  for (int j = 0; j < A; ++j) {
    for (int i = 0; i < line; ++i){
      t.Element_ij(i,0) = MATRIX.Element_ij(i,j);
    }
    do {
      p = Transposition(Transposition(t) * EE);
      double t1_t = (Transposition(t) * t).Element_ij(0,0);
      for (auto& element : p.GetMatrix()){
        for (auto& el: element) el /= t1_t;
      }
      
      double norm_p = Euclidean_norm(p);
      
      for (auto& element : p.GetMatrix()){
        for (auto& el: element) el /= norm_p;
      } 
      
      t_old = t;
      t = EE * p;
      double p1_p = (Transposition(p) * p).Element_ij(0,0);
      
      for (auto& element : t.GetMatrix()){
        for (auto& el: element) el /= p1_p;
      }
    } while (Euclidean_norm(t_old - t)> epsilon);
    EE = EE - t * Transposition(p);
    vec_p.push_back(p);
    vec_t.push_back(t);
  }
  
  Matrix T1(line, vec_t.size()),P1(vec_p[0].Num_line(),vec_p.size());
  for (int i = 0; i < line; ++i) {
    for (int r = 0; r < vec_t.size(); ++r) {
      T1.Element_ij(i, r) = vec_t[r].Element_ij(i, 0);
      if (i < vec_p[0].Num_line())
        P1.Element_ij(i, r) = vec_p[r].Element_ij(i, 0);
    }
  }
  T = T1; P = P1; E = EE;
  nip = true;
  return {T, P, E};
};

//вывод всех матриц
void PCA::PRINT() {
  cout << MATRIX << '\n';
  cout << T << '\n';
  cout << P << '\n';
  cout << E << '\n';
}
//размах
vector<double> PCA::Scope() const {
    if (!nip) throw runtime_error("Не был применен алгоритм NIPALS!");
  vector<double> scop;
  for (int i = 0; i < T.Num_line(); ++i){
    Matrix t(1, T.Num_column());
    for (int j = 0; j < T.Num_column(); ++j) {
      t.Element_ij(0, j) = T.Element_ij(i, j);
    }
    auto T1_T = Reverse(Transposition(T) * T);
    auto h = (t * T1_T) *  Transposition(t);
    scop.push_back(h.Element_ij(0, 0));
  }
    return scop;
}
//отклонения
vector<double> PCA::Deviations() const {
    if (!nip) throw runtime_error("Не был применен алгоритм NIPALS!");
  vector<double> devs;
  for (int i = 0; i < E.Num_line(); ++i){
    double v = 0;
    for (int j = 0; j < E.Num_column(); ++j){
      v += E.Element_ij(i, j) * E.Element_ij(i, j);
    }
    devs.push_back(v);
  }
  return devs;
}
//вычисление среднего (для всех образцов) расстояния
double PCA::Average_distance(){
  if (!nip) throw runtime_error("Не был применен алгоритм NIPALS!");
  vector<double> vi = Deviations();
  double v0 = 0;
  for (auto i : vi) v0 += i;
  return v0 / E.Num_line();
}

//дисперсия для полной и объясненной
vector<double> PCA::Dispersion(){
  if (!nip) throw runtime_error("Не был применен алгоритм NIPALS!");
  vector<double> deviations = Deviations();
  for(auto& i : deviations){
    i /= E.Num_column();
  }
  return deviations;
}
//полная дисперсия
double PCA::Full_dispersion(){
  if (!nip) throw runtime_error("Не был применен алгоритм NIPALS!");
  vector<double> dispersion = Dispersion();
  double full = 0;
  for (auto i : dispersion) full += i;
  return full / E.Num_line();
}
//объясненная дисперсия
double PCA::Explained_dispersion(){
  if (!nip) throw runtime_error("Не был применен алгоритм NIPALS!");
  double Exp = 0;
  for (size_t i = 0; i < MATRIX.Num_line(); ++i){
    for (size_t j = 0; j < MATRIX.Num_column(); ++j){
      Exp += MATRIX.Element_ij(i, j) * MATRIX.Element_ij(i, j);  
    }
  }
  return (1 - E.Num_line() * Average_distance() / Exp);
}