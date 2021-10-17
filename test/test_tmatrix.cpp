#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
  TMatrix<int>m1(5);
  TMatrix<int>m2(m1);
  EXPECT_EQ(m1, m2);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
  TMatrix<int>m1(5);
   m1[4][4] = 35;
  TMatrix<int>m2(m1);
  EXPECT_EQ(m1[4][4], m2[4][4]);
}

TEST(TMatrix, can_get_size)
{
  const int SIZE = 15;
  TMatrix<int>m(SIZE);
  EXPECT_EQ(m.GetSize(), SIZE);
}

TEST(TMatrix, can_set_and_get_element)
{
  constexpr int SIZE = 15;
  TMatrix<int>m(SIZE);
  EXPECT_NO_THROW(m[0][0] = 10);
  EXPECT_EQ(m[0][0], 10);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
  constexpr int SIZE = 15;
  TMatrix<int>m(SIZE);
  EXPECT_ANY_THROW(m[-1][-1] = 10);
  EXPECT_ANY_THROW(m[-1][0] = 10);
  EXPECT_ANY_THROW(m[0][-1] = 10);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
  constexpr int SIZE = 15;
  TMatrix<int>m(SIZE);
  EXPECT_ANY_THROW(m[SIZE + 1][SIZE + 1] = 10);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
  constexpr int SIZE = 15;
  TMatrix<int>m(SIZE);
  for (size_t i = 0; i < 15; i++)
  {
	for (size_t j = i; j < 15; j++)
	{
	  m[i][j] = i * j;
	}
  }
  m = m;
  EXPECT_EQ(m, m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
  constexpr int SIZE = 15;
  TMatrix<int>m(SIZE),m2(SIZE);
  for (size_t i = 0; i < SIZE; i++)
	for (size_t j = i; j < SIZE; j++)
	  m[i][j] = i * 10 + j;
  m2 = m;
  EXPECT_EQ(m, m2);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
  TMatrix<int>m(15), m2(10);
  int size_m2_was = m2.GetSize();
  m2 = m;
  int size_m2_now = m2.GetSize();
  EXPECT_NE(size_m2_was,size_m2_now);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
  constexpr int SIZE = 15, SIZE2 = 25;
  TMatrix<int>m(SIZE), m2(SIZE2);
  for (size_t i = 0; i < SIZE; i++)
	for (size_t j = i; j < SIZE; j++)
	  m[i][j] = i * 10 + j;
  m = m2;
  EXPECT_EQ(m, m2);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
  TMatrix<int>m1(10), m2;
  for (size_t i = 0; i < 10; i++)
  {
	for (size_t j = i; j < 10; j++)
	{
	  m1[i][j] = 24 + 53 * i - 53 * i * j;
	}
  }
  m1 = m2;
  EXPECT_EQ(true, m1 == m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
  TMatrix<int>m1(10);
  for (size_t i = 0; i < 10; i++)
  {
	for (size_t j = i; j < 10; j++)
	{
	  m1[i][j] = i + 3 * j + 7 * i * j;
	}
  }
  EXPECT_EQ(true, m1 == m1);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
  TMatrix<int>m1(10),m2(15);
  EXPECT_NE(m1, m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
  constexpr int size = 5;
  int sum = 0;
  TMatrix<int>m1(size), m2(size);
  for (size_t i = 0; i < size; i++)
  {
	for (size_t j= i; j < size; j++)
	{
	  m1[i][j] = 5;
	  m2[i][j] = 10;
	}
  }
  m1[0][0] = 80;
  // 90 15 15 15 15
  //    15 15 15 15 
  //       15 15 15
  //          15 15
  //             15
  m1 = m1 + m2;
  for (size_t i = 0; i < size; i++)
  {
	for (size_t	 j= i; j < size; j++)
	{
	  sum += m1[i][j];
	}
  }
  EXPECT_EQ(sum,300);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
  TMatrix<int>m1(10), m2(15);
  EXPECT_ANY_THROW(m1 = m1 + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
  constexpr int size = 5;
  int sum = 0;
  TMatrix<int>m1(size), m2(size);
  for (size_t i = 0; i < size; i++)
  {
	for (size_t j = i; j < size; j++)
	{
	  m1[i][j] = 5;
	  m2[i][j] = 10;
	}
  }
  m1[size - 1][size - 1] = 38;
   //-5 -5 -5 -5 -5
  //    -5 -5 -5 -5 
  //       -5 -5 -5
  //          -5 -5
  //             28
  m1 = m1 - m2;
  for (size_t i = 0; i < size; i++)
  {
	for (size_t j = i; j < size; j++)
	{
	  sum += m1[i][j];
	}
  }
  EXPECT_EQ(sum, -42);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TMatrix<int>m1(10), m2(15);
  EXPECT_ANY_THROW(m1 = m1 - m2);
}

