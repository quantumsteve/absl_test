#include "absl/strings/str_join.h"

#include <boost/spirit/include/karma.hpp>

#include <chrono>
#include <iostream>
#include <vector>

template <typename T>
struct doubleN_policy : boost::spirit::karma::real_policies<T>   
{
    //  we want to generate up to N fractional digits
    static unsigned int precision(T) { return 6; }
};

int main()
{
  std::vector<double> input(10000000,0.123456);
  std::string separator{";"};
  for (int i = 0;i<10;++i)
  {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = absl::StrJoin(input, separator);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << diff.count() << '\n';
    std::string output(result.begin(),std::next(result.begin(),27));
    std::cout << output << '\n';
  }
  using boost::spirit::karma::generate;
  using boost::spirit::karma::lit;
  typedef boost::spirit::karma::real_generator<double, doubleN_policy<double> > 
    doubleN_type;
  doubleN_type const doubleN = doubleN_type();
  std::string result;
  for (int i = 0;i<10;++i)
  {
    result.clear();
    auto start = std::chrono::high_resolution_clock::now();
    generate(std::back_inserter(result),              // the output
             doubleN << *(lit(separator) << doubleN), // the generator
             input                                   // the input
    );
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << diff.count() << '\n';
    std::string output(result.begin(),std::next(result.begin(),27));
    std::cout << output << '\n';
  }
}

