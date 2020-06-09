cmake_minimum_required(VERSION 2.8)

project(BlastCompanyGame)
set(CMAKE_CXX_STANDARD 17)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_add_remote(NAME bincrafters INDEX 1
            URL https://api.bintray.com/conan/bincrafters/public-conan)
conan_cmake_run(REQUIRES  sdl2/2.0.12@bincrafters/stable  bzip2/1.0.8@conan/stable   zlib/1.2.9@conan/stable  libpng/1.6.37@bincrafters/stable  libtiff/4.0.9@bincrafters/stable  boost_any/1.69.0@bincrafters/stable   spdlog/1.3.1@bincrafters/stable   Catch2/2.11.1@catchorg/stable  sdl2_image/2.0.5@bincrafters/stable  nlohmann_json/3.7.3  boost_dll/1.69.0@bincrafters/stable boost_filesystem/1.69.0@bincrafters/stable BASIC_SETUP BUILD missing)
set(CMAKE_CXX_FLAGS_DEBUG, "-g")
include_directories("../InputComponent/")
add_library(${PROJECT_NAME} SHARED "game.cpp")
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
