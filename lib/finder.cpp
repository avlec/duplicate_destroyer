#include "duplicates/finder.hpp"

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <openssl/md5.h>

using namespace duplicates;

finder::finder(std::string path, finder_mode mode, bool recurse)
  : path_(boost::filesystem::path(path)), mode_(mode), recurse_(recurse), results_{}
{
  // Validate path, throw exception if invalid
  if(!boost::filesystem::exists(path_))
    if(!boost::filesystem::is_directory(path_))
      throw std::runtime_error("Invalid file path" + path_.string());

  // Validate mode.
  if(mode_ >= 2)
    throw std::runtime_error("Invalid mode" + std::to_string(mode_));
}

std::string finder::compute_hash(const boost::filesystem::path& path)
{
  MD5_CTX ctx;
  MD5_Init(&ctx);

  std::ifstream ifs(path.string(), std::ios::binary);

  char file_buffer[4096];
  while(ifs.read(file_buffer, sizeof(file_buffer)) || ifs.gcount())
    {
      MD5_Update(&ctx, file_buffer, ifs.gcount());
    }
  unsigned char digest[MD5_DIGEST_LENGTH] = {};
  MD5_Final(digest, &ctx);


  // Convert digest into human-readable string
  // TODO in the future remove this entirely
  std::stringstream ss;
  for(unsigned int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    {
      ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }
  return ss.str();
}

const finder::list_type& finder::operator()()
{
  if(recurse_)
    {
      for(auto&& listing : boost::filesystem::recursive_directory_iterator(path_))
        {
          results_.insert(std::make_pair(compute_hash(listing.path()), listing.path().string()));
        }
    }
  else
    {
      for(auto&& listing : boost::filesystem::directory_iterator(path_))
        {
          results_.insert(std::make_pair(compute_hash(listing.path()), listing.path().string()));
        }
    }
  return results_;
}
