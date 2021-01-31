#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

/**
 * @brief Rotate Matrix.
 *
 * Rotate a NxN 2D matrix by 90 degrees clockwise.
 * Time complexity: O(N^2)
 * Space complexity: O(1)
 */
template <typename T>
void rotate_90(vector<T> & mat)
{
  auto const N = static_cast<size_t>(round(sqrt(size(mat))));
  assert(N * N == size(mat));

  // Define a 2D accessor
  auto v = [&mat,N](size_t i, size_t j) -> T & { return mat[i * N + j]; };

  // rotate by layer starting from the outside
  for (size_t i = 0; i < N/2; ++i)
  {
    for (size_t j = i; j < N-i-1; ++j)
    {
      T tmp = std::move(v(i, j));
      v(i, j) = std::move(v(N-j-1, i));
      v(N-j-1, i) = std::move(v(N-i-1, N-j-1));
      v(N-i-1, N-j-1) = std::move(v(j, N-i-1));
      v(j, N-i-1) = std::move(tmp);
    }
  }
}

bool test(vector<int> m, vector<int> const & e)
{
  rotate_90(m);
  return m == e;
}

int main()
{
  assert(test({}, {}));
  assert(test({1}, {1}));
  assert(test({1,2,3,4}, {3,1,4,2}));
  assert(test({1,2,3,4,5,6,7,8,9}, {7,4,1,8,5,2,9,6,3}));
}
