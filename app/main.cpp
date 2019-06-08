#include "duplicates/finder.hpp"

#include <iostream>

int main(int argc, char ** argv)
{
  std::cout << "Program starting" << std::endl;

  if(argc < 2)
    {
      std::cout << "Expected use: dupe_find <dir>" << std::endl;
      return 1;
    }

  duplicates::finder x(argv[1], 0, true);

  const duplicates::finder::list_type results = x();

  for(auto i = results.begin(); i != results.end(); i++)
    {
      std::cout << std::get<0>(*i) << ":\t" << std::get<1>(*i) << std::endl;
    }

  return 0;
}
