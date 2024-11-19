#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "arc.hpp"

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

std::vector<Package> search_aur(const std::string &query)
{
  std::vector<Package> packages;
  CURL *curl = curl_easy_init();
  if (!curl)
  {
    std::cerr << "Failed to initialize CURL" << std::endl;
    return packages;
  }

  std::string readBuffer;
  std::string url = "https://aur.archlinux.org/rpc/?v=5&type=search&arg=" + query;
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

  CURLcode res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  if (res != CURLE_OK)
  {
    std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
    return packages;
  }

  try
  {
    auto json = nlohmann::json::parse(readBuffer);
    if (json.contains("results") && json["results"].is_array() && !json["results"].empty())
    {
      for (const auto &result : json["results"])
      {
        if (result.contains("Name") && result.contains("Description") && result.contains("Version"))
        {
          Package pkg;
          pkg.name = result["Name"].is_null() ? "" : result["Name"];
          pkg.description = result["Description"].is_null() ? "" : result["Description"];
          pkg.version = result["Version"].is_null() ? "" : result["Version"];
          packages.push_back(pkg);
        }
      }
    }
    else
    {
      std::cerr << "No packages found for query: " << query << std::endl;
    }
  }
  catch (const nlohmann::json::parse_error &e)
  {
    std::cerr << "JSON parse error: " << e.what() << std::endl;
  }

  return packages;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " <search_query>" << std::endl;
    return 1;
  }

  std::string query = argv[1];
  auto packages = search_aur(query);

  if (packages.empty())
  {
    std::cout << "No packages found for query: " << query << std::endl;
  }
  else
  {
    for (const auto &pkg : packages)
    {
      std::cout << "Name: " << pkg.name << std::endl;
      std::cout << "Description: " << pkg.description << std::endl;
      std::cout << "Version: " << pkg.version << std::endl;
      std::cout << "------------------------" << std::endl;
    }
  }

  return 0;
}