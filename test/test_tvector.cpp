#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
  TVector<int>v(10);
  TVector<int>v1(v);
  EXPECT_EQ(v, v1);
}

TEST(TVector, copied_vector_has_its_own_memory)
{//
  TVector<int> v1(4,5);
  v1[5]= 4;
 TVector<int>v2(v1);
 EXPECT_EQ(v1[5], v2[5]);

}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
  TVector<int>v(5);
  EXPECT_ANY_THROW(v[-1] = 5);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
  constexpr int SIZE = 10;
  TVector<int>v(SIZE);
  EXPECT_ANY_THROW(v[SIZE + 1] = SIZE);
}

TEST(TVector, can_assign_vector_to_itself)
{//
  TVector<int>v(5);
  v = v;
  EXPECT_EQ(v,v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{//
 TVector<int> v1(4,6) ,v2(4,5);
 v1 = v1 + 5;
 v1 = v2;
 EXPECT_EQ(v1, v2);
}

TEST(TVector, assign_operator_change_vector_size)
{
  TVector<int> v1(4,6) ,v2(6,5);
  v2=  v2+ 10;
  v1 = v2;
  EXPECT_EQ(v1.GetSize(), 6);
}

TEST(TVector, can_assign_vectors_of_different_size)
{
  TVector<int> v1(4, 6), v2(6, 5);
  v2 = v2 + 10;
  v1 = v2;
  EXPECT_EQ(v1, v2);
}

TEST(TVector, compare_equal_vectors_return_true)
{//
  TVector<int>v1(4, 5);
  v1 = v1 + 10;
  TVector<int>v2(v1);
  EXPECT_EQ(true, v1 == v2);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
  TVector<int>v1(4, 5);
  v1 = v1 + 10;
  EXPECT_EQ(true, v1 == v1);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
  TVector<int>v1(10), v2(12);
  EXPECT_NE(v1, v2);
}

TEST(TVector, can_add_scalar_to_vector)
{//
  constexpr int a = 15;
  int sum = 0;
  TVector<int>v(10);
  v = v + 15;
  for (size_t i = 0; i < 10; i++)
  {
    sum += v[i];
  }
  EXPECT_EQ(sum, 150);
}

TEST(TVector, can_subtract_scalar_from_vector)
{//
  constexpr int a = 15;
  int sum = 0;
  TVector<int>v(10);
  v = v - a;
  for (size_t i = 0; i < 10; i++)
  {
    sum += v[i];
  }
  EXPECT_EQ(sum, -150);
}

TEST(TVector, can_multiply_scalar_by_vector)
{//
  constexpr int a = 2;
  int sum = 0;
  TVector<int>v(10);
  v = v + a;
  v = v * 5;
  for (size_t i = 0; i < 10; i++)
  {
    sum += v[i];
  }
  EXPECT_EQ(sum, 100);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
  int sum = 0;
  TVector<int>v(10),v2(10);
  v = v + 15;
  v2 = v2 + 10;
  v = v + v2;
  for (size_t i = 0; i < 10; i++)
  {
    sum += v[i];
  }
  EXPECT_EQ(sum, 250);
}
//
TEST(TVector, cant_add_vectors_with_not_equal_size)
{
  int sum = 0;
  TVector<int>v(10), v2(12);
  EXPECT_ANY_THROW(v = v + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
  int sum = 0;
  TVector<int>v(10), v2(10);
  v = v + 15;
  v2 = v2 + 10;
  v = v - v2;
  for (size_t i = 0; i < 10; i++)
  {
    sum += v[i];
  }
  EXPECT_EQ(sum, 50);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
  TVector<int>v(10), v2(12);
  EXPECT_ANY_THROW(v = v - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
  TVector<int>v(10), v2(10);
  v = v + 2;
  v2 = v2 + 3;
  int sum = v * v2;
  EXPECT_EQ(sum, 60);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
  TVector<int>v(10), v2(12);
  EXPECT_ANY_THROW(v = v * v2);
}

TEST(TVector, set_the_value_to_all_elements_of_the_vector)
{
  int sum = 0;
  TVector<int>v(20);
  v.SetValueToVector(10);
  for (size_t i = 0; i <v.GetSize(); i++)
  {
    sum += v[i];
  }
  EXPECT_EQ(200, sum);
}