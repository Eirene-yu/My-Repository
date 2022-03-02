#pragma once

//тесты на корректность работы 1 части лабораторной
void DEFMatrix(); //создание матрицы по умолчанию
void Create_matrix(Matrix& a);
void Create_matrix2(Matrix& a);
void VALMatrix(); //содание матрицы с заданными значениям
void SUMMatrix(); //сложение матриц
void DIFMatrix(); //разность матриц
void Create_matrix3(Matrix& a);
void COMMatrix(); //умножение матриц
void COMMatrixNum(); //умножение матрицы на число
void HadamardMatrix(); //произведение Адамара
void Test1();
//тесты на корректность работы 2 части лабораторной
void TRACEMatrix(); //cлед матрицы
void DETMatrix(); //Определитель матрицы
void Create_vector(Matrix& a);
void Create_vector2(Matrix& a);
void ScaVec(); //скалярное проивзедение векторов
void NORME(); // евклидова норма вектора
void NORMMAX(); // максимальная норма вектора
void NORMMatrix(); //норма Фробениуса
void Test2();
//тесты на корректность работы 3 части лабораторной
void angle(); // угол между векторами
void R(); // ранг матрицы
void revMatrix(); // обратная матрица
void TranMatrix(); // транспонированная матрицы
void Test3();
//тесты на корректность работы 4 части лабораторной
void TextFile(); //чтение и запись в текстовый файл
void BinFile(); //чтение и запись в бинарный файл
void Test4();