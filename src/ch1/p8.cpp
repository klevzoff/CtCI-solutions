#include "testing.hpp"
#include "printing.hpp"

#include <vector>
#include <cassert>

/**
 * @brief Zero Matrix.
 *
 * Zero all rows and columns of a MxN matrix that contain a zero element.
 * Time complexity: O(MxN).
 * Space complexity: O(1).
 */
template <typename T>
void zero_rowcol(std::vector<T> & mat, size_t M, size_t N)
{
  assert(M * N == size(mat));

  // define a 2D accessor into matrix values
  auto v = [&mat,N](size_t i, size_t j) -> T & { return mat[i * N + j]; };

  // these will be index of row/col that is used to mark zeroed rows/cols
  auto idx_row = size_t(-1);
  auto idx_col = size_t(-1);

  // first pass: find rows/cols to zero
  for (size_t i = 0; i < M; ++i)
  {
    for (size_t j = 0; j < N; ++j)
    {
      if (v(i, j) == T(0))
      {
        if (idx_row == size_t(-1))
        {
          idx_row = i;
          idx_col = j;
        }
        v(idx_row, j) = T(0);
        v(i, idx_col) = T(0);
      }
    }
  }

  if (idx_row == size_t(-1)) return;

  // actually zero rows
  for (size_t i = 0; i < M; ++i)
  {
    if (v(i, idx_col) == T(0) && i != idx_row)
    {
      for (size_t j = 0; j < N; ++j) v(i, j) = T(0);
    }
  }

  // actually zero cols
  for (size_t j = 0; j < N; ++j)
  {
    if (v(idx_row, j) == T(0))
    {
      for (size_t i = 0; i < M; ++i) v(i, j) = T(0);
    }
  }

  // final pass to zero out index row that we skipped
  for (size_t j = 0; j < N; ++j) v(idx_row, j) = T(0);
}

void test(std::vector<int> m, size_t M, size_t N, std::vector<int> const & e)
{
  zero_rowcol(m, M, N);
  EXPECT_EQ(m, e);
}

int main()
{
  test({}, 0, 0, {});
  test({1}, 1, 1, {1});
  test({1,2,3,0}, 2, 2, {1,0,0,0});
  test({1,2,3,0,5,0,7,8,9,0,11,12}, 4, 3, {0,2,0,0,0,0,0,8,0,0,0,0});
  return testing::summary();
}
