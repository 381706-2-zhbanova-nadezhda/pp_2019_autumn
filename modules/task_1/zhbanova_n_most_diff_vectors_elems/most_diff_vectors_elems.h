
#ifndef MODULES_TASK_1_ZHBANOVA_N_MOST_DIFF_VECTORS_ELEMS_MOST_DIFF_VECTORS_ELEMS_H_
#define MODULES_TASK_1_ZHBANOVA_N_MOST_DIFF_VECTORS_ELEMS_MOST_DIFF_VECTORS_ELEMS_H_

#include <vector>
using namespace std;

vector<int> randomInput(int size); // создание вектора заданной с рандомными значениями
int maxDiff(vector<int> v); // обычный вариант
int maxDiffMpi(vector<int> v); // с использованием MPI

#endif  // MODULES_TASK_1_ZHBANOVA_N_MOST_DIFF_VECTORS_ELEMS_MOST_DIFF_VECTORS_ELEMS_H_