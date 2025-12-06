#pragma once
#include <unordered_map>
#include <string>

extern int DEFAULT; 
extern std::unordered_map<std::string, int> size_pixels;
enum class Style { Blocky, Edgy, Sharp };
enum class Modes { Ascii, Block };