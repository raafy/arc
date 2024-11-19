#ifndef ARC_HPP
#define ARC_HPP

#include <string>
#include <vector>

struct Package
{
  std::string name;
  std::string description;
  std::string version;
};

std::vector<Package> search_aur(const std::string &query);

#endif // ARC_HPP