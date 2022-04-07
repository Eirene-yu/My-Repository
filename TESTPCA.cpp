#include "PCA.h"

void Test5(){
  try{
    Matrix s = Read_text_file("data.txt");
    //cout << s;
    PCA pca(s);
    pca.Centering(); // центрирование
    //cout << pca.GetPCA();
    pca.Scaling(); //шкалирование
    //cout << pca.GetPCA();
    pca.NIPALS(4); //алгоритм Nipals по 4 объектам, как на сайте, чтоб проверить дальнейшие значения
    pca.PRINT();
    Matrix R = pca.GetT() * Transposition(pca.GetP()) + pca.GetE();
    Matrix X = pca.GetPCA();
    bool k = 0;
    //проверка равенства матриц, по точности
    for(int i = 0; i < R.Num_line(); ++i){
      for (int j = 0; j < R.Num_column(); ++j){
        if (R.Element_ij(i,j) - X.Element_ij(i,j)  > 0.00000001) k += 1;
        }
    }
    if (k == 0) cout << "Pавны!" << endl;
    else throw 1;
    vector<double> Scope = pca.Scope();
    vector<double> Deviations = pca.Deviations();
    // Размах
    cout << "Размах " << endl;
    for (double scope : pca.Scope()) {
      cout << scope << " ";
    }
    cout << endl;
    // Отклонение
    cout << "Отклонение " << endl;
    for (double deviations : pca.Deviations()) {
      cout << deviations << " ";
    }
    cout << endl;
    // Дисперсии (v0, TRV, ERV)
    auto v0 = pca.Average_distance();
    auto TRV = pca.Full_dispersion();
    auto ERV = pca.Explained_dispersion();
    cout << "v0 : " << v0 << " TRV : " << TRV << " ERV : " << ERV << endl;
    cout << "Проверим, округлив до трех знаков после запятой, со значениями с сайт." << endl;
    cout << "v0 : " << v0 << " =? 0.690 ";
    if (round(v0*1000)/1000 == 0.690) cout << "Да" << endl;
    else throw 2;
    cout << "TRV : " << TRV << " =? 0.690 ";
    if (round(TRV*1000)/1000 == 0.057) cout << "Да" << endl;
    else throw 3;
    cout << "ERV : " << ERV << " =? 0.690 ";
    if (round(ERV*1000)/1000 == 0.941) cout << "Да" << endl;
    else throw 4;
  }catch (int t){
    if (t == 1) cout << "Матрица найдена не верно.";
    if (t == 2) cout << "v0 не совпадает со значением на сайте.";
    if (t == 3) cout << "TRV не совпадает со значением на сайте.";
    if (t == 4) cout << "ERV не совпадает со значением на сайте.";
  }
  cout << "Test5 пройден." << endl;
}
  