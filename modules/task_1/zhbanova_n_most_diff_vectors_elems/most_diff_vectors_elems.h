
#ifndef MODULES_TASK_1_ZHBANOVA_N_MOST_DIFF_VECTORS_ELEMS_MOST_DIFF_VECTORS_ELEMS_H_
#define MODULES_TASK_1_ZHBANOVA_N_MOST_DIFF_VECTORS_ELEMS_MOST_DIFF_VECTORS_ELEMS_H_

#include <vector>
using namespace std;

vector<int> randomInput(int size); // �������� ������� �������� � ���������� ����������
int maxDiff(vector<int> v); // ������� �������
int maxDiffMpi(vector<int> v); // � �������������� MPI

#endif  // MODULES_TASK_1_ZHBANOVA_N_MOST_DIFF_VECTORS_ELEMS_MOST_DIFF_VECTORS_ELEMS_H_