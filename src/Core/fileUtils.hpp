//! @file

#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <fstream>
#include <string>
#include <experimental/filesystem>
#include <vector>
#include <immer-0.6.2/immer/flex_vector.hpp>
#include <immer-0.6.2/immer/flex_vector_transient.hpp>
#include <SDL2/SDL.h>

#include "renderchars.hpp"
#include "datatypes.hpp"
#include "menubar.hpp"

namespace better {
//TODO: finish these function definitions to get file I/O working
int saveFile(immer::flex_vector<immer::flex_vector<char>> contents, std::string filename);
immer::flex_vector<immer::flex_vector<char>> readFile(std::string filename);
immer::flex_vector<char> stringToVector(std::string string);
std::experimental::filesystem::path fileDialog();

}

#endif
