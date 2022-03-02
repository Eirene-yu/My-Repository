#include "Matrix.h"

//перегрузка оператора вывода
ostream &operator<< (ostream &output, const Matrix& O)
{
    for (int i = 0; i < O.Num_line(); ++i)
    {
        for (int j = 0; j < O.Num_column(); ++j)
        {
            output << O.Element_ij(i, j);
            if (j != O.Num_column() - 1) output << ' ';
        }
        output << '\n';
    }
    return output;
}

//перегрузка оператора считывания матрицы
istream& operator>>(istream &is, Matrix& O)
{
    for (int i = 0; i < O.Num_line(); ++i)
    {
        for (int j = 0; j < O.Num_column(); ++j)
        {
          double current_num;
			    is >> current_num;
          O.MATRIX[i][j] = current_num;
          is.ignore(1); 
        } 
    }
  return is;
}

//оператор проверки равенства матриц
bool operator==(const Matrix& a, const Matrix& b) {
	if (a.Num_line() != b.Num_line() || a.Num_column() != b.Num_column()) {
		throw false;
	}
	for (int i = 0; i < a.Num_line(); ++i) {
		for (int j = 0; j < b.Num_line(); ++j) {
			if (a.Element_ij(i, j) != b.Element_ij(i, j))
				return false;
		}
	}
	return true;
}

//оператор проверки неравенства матриц
bool operator!=(const Matrix& a, const Matrix& b) {
	return !(a == b);
}
