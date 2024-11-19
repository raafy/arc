cmake_minimum_required(VERSION 3.10)
project(arc)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

include_directories(${CURL_INCLUDE_DIRS} include)

add_executable(arc src/main.cpp)
target_link_libraries(arc ${CURL_LIBRARIES} nlohmann_json::nlohmann_json)