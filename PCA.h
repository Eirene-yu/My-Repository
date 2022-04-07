#pragma once

#include "Matrix.h"
#include <cmath>  


class PCA{
  private:
    Matrix MATRIX, P, T, E;
    bool nip; 
  public:
  PCA(const Matrix& a){
      MATRIX.Num_line() = a.Num_line();
      MATRIX.Num_column() = a.Num_column();
      MATRIX.GetMatrix() = a.GetMatrix();
  }
  const Matrix& GetPCA() const{
    return MATRIX;
  }
  const Matrix& GetP() const{
    return P;
  }
  const Matrix& GetT() const{
    return T;
  }
  const Matrix& GetE() const{
    return E;
  }
  void Centering();
  void Scaling();
  tuple<Matrix, Matrix, Matrix> NIPALS(size_t A = -10, double epsilon = 0.00000001);
  void PRINT();
  vector<double> Scope() const;
  vector<double> Deviations() const;
  double Average_distance();
  vector<double> Dispersion();
  double Full_dispersion();
  double Explained_dispersion();
};

