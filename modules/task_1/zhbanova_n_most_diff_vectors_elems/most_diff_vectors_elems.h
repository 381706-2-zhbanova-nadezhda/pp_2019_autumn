
#ifndef MODULES_TASK_1_ZHBANOVA_N_MOST_DIFF_VECTORS_ELEMS_MOST_DIFF_VECTORS_ELEMS_H_
#define MODULES_TASK_1_ZHBANOVA_N_MOST_DIFF_VECTORS_ELEMS_MOST_DIFF_VECTORS_ELEMS_H_

// Copyright 2019 Zhbanova Nadezhda

#include <vector>

std::vector<int> randomInput(int size);  // создание вектора заданной с рандомными значениями
int maxDiff(std::vector<int> v);  // обычный вариант
int maxDiffMpi(std::vector<int> v);  // с использованием MPI

#endif  // MODULES_TASK_1_ZHBANOVA_N_MOST_DIFF_VECTORS_ELEMS_MOST_DIFF_VECTORS_ELEMS_H_
