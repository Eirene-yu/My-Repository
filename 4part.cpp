#include "Matrix.h"
#include <fstream>

//функция записи в текстовый файл
void Write_text_file(const string& file, const Matrix& M){
  ofstream out(file);
  if (!out.is_open()) throw runtime_error("Файл не был открыт для записи.");
  else out << M;
  out.close();
}

//функция чтения из текстового файла
Matrix Read_text_file(const string& file){
  ifstream in(file);
  if (!in.is_open()) throw runtime_error("Файл не был открыт для чтения или его не существует.");
  else{
    int ROW = 0, COL = 0;
    while (!in.eof()){ 
      char c;
      in.get(c);
      if (c == ' ' || c == '\n') COL++;
      if (c == '\n') ROW++;
    }
   --ROW;
   COL = (COL - 1) / ROW;
   Matrix result(ROW, COL);
   in.close();
   ifstream inf(file, ios::app);
   inf >> result;
   return result;
  }
}

//запись в бинарный файл
void Write_bin_file(const string& file, const Matrix& M){
  ofstream out(file, ios::binary);
  if (!out.is_open()) throw runtime_error("Файл не был открыт для записи.");
  else{
    int ROW = M.Num_line();
    int COL = M.Num_column();
    out.write((char*)&ROW, sizeof ROW);
	  out.write((char*)&COL, sizeof COL);
    for (int i = 0; i < ROW; i++){
				for (int j = 0; j < COL; j++){
					out.write((char*)&M.Element_ij(i, j), sizeof(double));
        }
    }
  }
}

//чтение из бинарного файла
Matrix Read_bin_file(const string& file){
  ifstream in(file, ios::binary);
  if (!in.is_open()) throw runtime_error("Файл не был открыт для чтения или его не существует.");
  else{
    int ROW = 0, COL = 0;
    in.read((char*)&ROW, sizeof(int));
		in.read((char*)&COL, sizeof(int));
    Matrix result(ROW, COL);
    for (int i = 0; i < ROW; i++){
				for (int j = 0; j < COL; j++){
					in.read((char*)&result.Element_ij(i, j), sizeof(double));
        }
    }
    return result;
  }

}
