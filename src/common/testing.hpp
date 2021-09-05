#ifndef CTCI_SOLUTIONS_TESTING_HPP
#define CTCI_SOLUTIONS_TESTING_HPP

#include <iostream>

namespace testing
{
  inline int num_checks = 0;
  inline int num_failed = 0;

  int summary()
  {
    bool const success = num_failed == 0;
    std::cout << "Test summary:\n";
    std::cout << '\t' << (num_checks - num_failed) << '/' << num_checks << " checks passed\n";
    std::cout << '\t' << num_failed << '/' << num_checks << " checks failed\n";
    std::cout << "Test suite " << (success ? "SUCCEEDED" : "FAILED") << "\n";
    return success ? EXIT_SUCCESS : EXIT_FAILURE;
  }
}

#define STRINGIZE_( x ) #x
#define STRINGIZE( x ) STRINGIZE_( x )
#define LOCATION __FILE__ ":" STRINGIZE( __LINE__ )

#define EXPECT(cond) \
do \
{ \
  ++::testing::num_checks; \
  if (!(cond)) \
  { \
    ++::testing::num_failed; \
    std::cerr << LOCATION ": check failed: " #cond "\n"; \
  } \
} \
while (false)

#define EXPECT_EQ(exp1, exp2) \
do \
{ \
  ++::testing::num_checks; \
  auto const & v1 = exp1; \
  auto const & v2 = exp2; \
  if (!(v1 == v2)) \
  { \
    ++::testing::num_failed; \
    std::cerr << LOCATION ": check failed: " #exp1 " == " #exp2 ", where\n\t" #exp1 " = " << v1 << "\n\t" #exp2 " = " << v2 << "\n"; \
  } \
} \
while (false)

#endif //CTCI_SOLUTIONS_TESTING_HPP
