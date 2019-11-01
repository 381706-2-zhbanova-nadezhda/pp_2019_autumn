//functions

#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <time.h>
#include "../../../modules/task_1/zhbanova_n_most_diff_vectors_elems/most_diff_vectors_elems.h"
#include "./mpi.h"

using namespace std;

//�������, ��������� ������ �������� �����, ���������� ���
vector<int> randomInput(int size) {
  random_device rnd_device;
  mt19937 mersenne_engine(rnd_device());
  vector<int> vec;
  for (int i = 0; i < size; i++)
    vec.push_back(mersenne_engine() % 10);
  return vec;
}

//���������� ������ ���������� ������� �������� ���������
int maxDiff(vector<int> v) {
  int diff = 0;
  if (v.size() >= 2) {
	  //�������� ��� ������ �� 1 ������ ��� ��������� ������� -> v.size() - 1
    for (unsigned int i = 0; i < v.size() - 1; i++) {
      if (abs(v[i] - v[i + 1]) > diff) {
        diff = abs(v[i] - v[i + 1]);
	  }
    }
  }
  else //���� � ������� 1 ������� - ������ �� ����� ������
    throw("error");
  return diff;
}

//������������ ������� ������� ������
int maxDiffMpi(vector<int> v) {
  if (v.size() < 2) {
    throw("error");
  }

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int step = 1, rest = 0;
  //���� ��������� ������ ��� ���������� ���������
  if ((unsigned int)size < v.size() - 1) {
    step = (v.size() - 1) / size;//������� ��� ������ ���������� �������
    rest = (v.size() - 1) % size;//������� - ������� ��� �������� �������������
  }

  //������� 0 ����� ������������ ������ step ��� � ������� ������� �� ����������� ����� ����������
  //��������� ����� ������� step ��� �� ������� �� ���� ��� �������� ������� 0
  if (rank == 0) {
    for (int proc_rank = 1; proc_rank < size; proc_rank++) {
      MPI_Send(&v[0] + proc_rank * step + rest, step + 1, MPI_INT, proc_rank, 0, MPI_COMM_WORLD);
    }
  }

  //������ ������� ��������� ������ ������� ����� ������������
  vector<int> v_proc(step + 1);
  
  if (rank == 0) {
    // ������������ ������������ [..)
	  v_proc = vector<int>(v.begin(), v.begin() + step + rest + 1);
  }
  else {
	  //���� ��������� ���� ������� ������ �� �������� 0
    MPI_Status status;
    MPI_Recv(&v_proc[0], step + 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
  }

  int diff = 0, diff_proc = 0;

  //���� ��������� ������ ��� ���, ������� ���� �������� - ����� �������� ������ ������ v.size() - 1 ���������
  if ((unsigned int)rank < v.size() - 1) {
	  //������� ������� ���� ������
	  diff_proc = maxDiff(v_proc);
  }

  //���������� ���������� �� ���� ���������
  MPI_Reduce(&diff_proc, &diff, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
  return diff;
}