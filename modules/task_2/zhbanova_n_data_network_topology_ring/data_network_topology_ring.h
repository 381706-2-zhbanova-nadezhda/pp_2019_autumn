
#ifndef MODULES_TASK_2_ZHBANOVA_N_DATA_NETWORK_TOPOLOGY_RING_DATA_NETWORK_TOPOLOGY_RING_H_
#define MODULES_TASK_2_ZHBANOVA_N_DATA_NETWORK_TOPOLOGY_RING_DATA_NETWORK_TOPOLOGY_RING_H_

// Copyright 2019 Zhbanova Nadezhda

const int VEC_SIZE = 3;

std::vector<int> randomInputVector(int size);
std::vector<int> transferDataToCheck(int rank, int rankFrom, int rankTo, std::vector<int> vec);

// 1 way - all processes initially know the recipient process
std::vector<int> sendVector(int rankFrom, int rankTo, std::vector<int> vec);
void sendByRing(std::vector<int> vec, int rank, int size);
std::vector<int> recvFromRing(int rank, int size);

// 2 way - only the process sender knows the process recipient, initially
void sendVector2(int rankTo, std::vector<int> vec);
std::vector<int> transferVector2(int& rankFrom, int& rankTo);
void sendByRing2(std::vector<int> vec, int rank, int rankFrom, int rankTo, int size);
std::vector<int> recvFromRing2(int rank, int size, int& rankFrom, int& rankTo);

#endif  // MODULES_TASK_1_ZHBANOVA_N_DATA_NETWORK_TOPOLOGY_RING_DATA_NETWORK_TOPOLOGY_RING_H_
