// Copyright 2019 Zhbanova Nadezhda

#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include "./data_network_topology_ring.h"

TEST(data_network_topology_ring, exceptionIfRankFromLessThanZero) {
  std::vector<int> vec;
  int rankFrom = -1;
  int rankTo = 1;

  ASSERT_THROW(sendVector(rankFrom, rankTo, vec), std::runtime_error);
}

TEST(data_network_topology_ring, exceptionIfRankFromMoreThanNumOfProc) {
  std::vector<int> vec;
  int rankTo = 1;
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rankFrom = size;
  ASSERT_THROW(sendVector(rankFrom, rankTo, vec), std::runtime_error);
}

TEST(data_network_topology_ring, exceptionIfRankToLessThanZero) {
  std::vector<int> vec;
  int rankFrom = 0;
  int rankTo = -1;

  ASSERT_THROW(sendVector(rankFrom, rankTo, vec), std::runtime_error);
}

TEST(data_network_topology_ring, exceptionIfRankToMoreThanNumOfProc) {
  std::vector<int> vec;
  int rankFrom = 0;
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rankTo = size;
  ASSERT_THROW(sendVector(rankFrom, rankTo, vec), std::runtime_error);
}

TEST(data_network_topology_ring, exceptionToSendItself) {
  std::vector<int> vec;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int rankFrom = rank;
  int rankTo = rank;

  ASSERT_THROW(sendVector(rankFrom, rankTo, vec), std::runtime_error);
}

TEST(data_network_topology_ring, sendFromFirstToLast) {   // all processes are involved
  // prepare data
  std::vector<int> vec;
  int rankFrom = 0;
  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rankTo = size - 1;

  if (rank == rankFrom)
  {
    vec = randomInputVector(VEC_SIZE);
  }

  // execute
  std::vector<int> resultVec = sendVector(rankFrom, rankTo, vec);

  // check data
  resultVec = transferDataToCheck(rank, rankFrom, rankTo, resultVec);
  if (rank == rankFrom)
  {
    for (int i = 0; i < resultVec.size(); i++)
    {
      ASSERT_EQ(resultVec[i], vec[i]);
    }
  }
}

TEST(data_network_topology_ring, sendVia0Proc) {   // all processes are involved
  // prepare data
  std::vector<int> vec;
  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rankFrom = size / 2;
  int rankTo = rankFrom - 1;

  if (rank == rankFrom)
  {
    vec = randomInputVector(VEC_SIZE);
  }

  // execute
  std::vector<int> resultVec = sendVector(rankFrom, rankTo, vec);

  // check data
  resultVec = transferDataToCheck(rank, rankFrom, rankTo, resultVec);
  if (rank == rankFrom)
  {
    for (int i = 0; i < resultVec.size(); i++)
    {
      ASSERT_EQ(resultVec[i], vec[i]);
    }
  }
}

TEST(data_network_topology_ring, sendViaNotAllProcFromLessTo) {
  // prepare data
  std::vector<int> vec;
  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rankFrom = 0;
  int rankTo = size/2;

  if (rank == rankFrom)
  {
    vec = randomInputVector(VEC_SIZE);
  }

  // execute
  std::vector<int> resultVec = sendVector(rankFrom, rankTo, vec);

  // check data
  resultVec = transferDataToCheck(rank, rankFrom, rankTo, resultVec);
  if (rank == rankFrom)
  {
    for (int i = 0; i < resultVec.size(); i++)
    {
      ASSERT_EQ(resultVec[i], vec[i]);
    }
  }
}

TEST(data_network_topology_ring, sendViaNotAllProcFromMoreTo) {
  // prepare data
  std::vector<int> vec;
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int rankFrom = size - 1;
  int rankTo = 0;

  if (rank == rankFrom)
  {
    vec = randomInputVector(VEC_SIZE);
  }

  // execute
  std::vector<int> resultVec = sendVector(rankFrom, rankTo, vec);

  // check data
  resultVec = transferDataToCheck(rank, rankFrom, rankTo, resultVec);
  if (rank == rankFrom)
  {
    for (int i = 0; i < resultVec.size(); i++)
    {
      ASSERT_EQ(resultVec[i], vec[i]);
    }
  }
}

/************************способ 2****************************/
TEST(data_network_topology_ring_2, exceptionIfRankToLessThanZero) {
  std::vector<int> vec;
  int rankTo = -1;

  ASSERT_THROW(sendVector2(rankTo, vec), std::runtime_error);
}

TEST(data_network_topology_ring_2, exceptionIfRankToMoreThanNumOfProc) {
  std::vector<int> vec;
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rankTo = size;
  ASSERT_THROW(sendVector2(rankTo, vec), std::runtime_error);
}

TEST(data_network_topology_ring_2, exceptionToSendItself) {
  std::vector<int> vec;
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  ASSERT_THROW(sendVector2(rank, vec), std::runtime_error);
}

TEST(data_network_topology_ring_2, sendFromFirstToLast) {   // all processes are involved
  // prepare data
  std::vector<int> vec, resultVec(VEC_SIZE);
  int rank, size;
  int rankTo = -1;
  int rankFrom = 0;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == rankFrom)
  {
    rankTo = size - 1;
    vec = randomInputVector(VEC_SIZE);
  }

  // execute
  if (rank == rankFrom)
  {
    sendVector2(rankTo, vec);
  } else {
    vec = transferVector2(rankFrom, rankTo);
  }

  // check result
  if (rank == rankTo)
  {
    MPI_Send(&vec[0], vec.size(), MPI_INT, rankFrom, 0, MPI_COMM_WORLD);
  }
  if (rank == rankFrom)
  {
    MPI_Status status;   // received message parameter
    MPI_Recv(&resultVec[0], VEC_SIZE, MPI_INT, rankTo, 0, MPI_COMM_WORLD, &status);

    for (int i = 0; i < resultVec.size(); i++)
    {
      ASSERT_EQ(resultVec[i], vec[i]);
    }
  }
}

TEST(data_network_topology_ring_2, sendVia0Proc) {   // all processes are involved
  std::vector<int> vec, resultVec(VEC_SIZE);
  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int rankFrom = size/2;
  int rankTo;
  if (rank == rankFrom)
  {
    rankTo = rankFrom - 1;
    vec = randomInputVector(VEC_SIZE);
    sendVector2(rankTo, vec);

    MPI_Status status;
    MPI_Recv(&resultVec[0], VEC_SIZE, MPI_INT, rankTo, 0, MPI_COMM_WORLD, &status);
  } else {
    vec = transferVector2(rankFrom, rankTo);
    if (rank == rankTo)
    {
      MPI_Send(&vec[0], vec.size(), MPI_INT, rankFrom, 0, MPI_COMM_WORLD);
    }
  }

  // check data
  if (rank == rankFrom)
  {
    for (int i = 0; i < resultVec.size(); i++)
    {
      ASSERT_EQ(resultVec[i], vec[i]);
    }
  }
}

TEST(data_network_topology_ring_2, sendViaNotAllProcFromLessTo) {
  std::vector<int> vec, resultVec(VEC_SIZE);
  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int rankFrom = 0;
  int rankTo;
  if (rank == rankFrom)
  {
    rankTo = size / 2;
    vec = randomInputVector(VEC_SIZE);
    sendVector2(rankTo, vec);

    MPI_Status status; // параметр принятого сообщения
    MPI_Recv(&resultVec[0], VEC_SIZE, MPI_INT, rankTo, 0, MPI_COMM_WORLD, &status);
  } else {
    vec = transferVector2(rankFrom, rankTo);
    if (rank == rankTo)
    {
      MPI_Send(&vec[0], vec.size(), MPI_INT, rankFrom, 0, MPI_COMM_WORLD);
    }
  }

  // check data
  if (rank == rankFrom)
  {
    for (int i = 0; i < resultVec.size(); i++)
    {
      ASSERT_EQ(resultVec[i], vec[i]);
    }
  }
}

TEST(data_network_topology_ring_2, sendViaNotAllProcFromMoreTo) {
  std::vector<int> vec, resultVec(VEC_SIZE);
  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int rankFrom = size - 1;
  int rankTo;
  if (rank == rankFrom)
  {
    rankTo = 0;
    vec = randomInputVector(VEC_SIZE);
    sendVector2(rankTo, vec);

    MPI_Status status; // параметр принятого сообщения
    MPI_Recv(&resultVec[0], VEC_SIZE, MPI_INT, rankTo, 0, MPI_COMM_WORLD, &status);
  } else {
    vec = transferVector2(rankFrom, rankTo);
    if (rank == rankTo)
    {
      MPI_Send(&vec[0], vec.size(), MPI_INT, rankFrom, 0, MPI_COMM_WORLD);
    }
  }

  // check data
  if (rank == rankFrom)
  {
    for (int i = 0; i < resultVec.size(); i++)
    {
      ASSERT_EQ(resultVec[i], vec[i]);
    }
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
    ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}



