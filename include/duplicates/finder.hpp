#ifndef FINDER_HPP
#define FINDER_HPP

#include <map>
#include <vector>

#include <boost/filesystem.hpp>

namespace duplicates {

  class finder {
  public:

    using finder_mode = std::size_t;

    // NOTE: might change the value to a custom type to hold more info.
    using list_type = std::multimap<std::string, std::string>;
  private:
    boost::filesystem::path path_;
    finder_mode mode_;
    bool recurse_;
    list_type results_;


    std::string compute_hash(const boost::filesystem::path& path);
  public:

    static const finder_mode HASH_CHECK = 0;
    static const finder_mode ALG_CHECK = 1;

    finder() = delete;
    finder(std::string path, finder_mode mode = HASH_CHECK, bool recurse = false);

    ~finder() = default;

    // This function is responsible for starting the processing on the current
    // directory specified by the path_ variable.
    const list_type& operator()();


  };

}

#endif
