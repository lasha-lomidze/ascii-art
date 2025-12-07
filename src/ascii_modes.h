#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include "globals.h"

// reset ANSI escape
extern const std::string ANSI_RESET;

// ASCII conversions
char grayscale_to_ascii(unsigned char pixel);
char rgb_to_ascii(int R, int G, int B);

// Block-style grayscale ASCII
const char *grayscale_to_block(unsigned char pixel, Style style = Style::Blocky);

// ANSI color conversions
int rgb_to_ansi256(int R, int G, int B);
std::string rgb_to_ansi256_string(int R, int G, int B);

// high-level drawing functions
void draw_in_terminal(cv::Mat img);
void draw_in_new_file(cv::Mat img, const std::string &filename = "art.txt");
