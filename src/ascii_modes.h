#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include "globals.h"

char grayscale_to_ascii(unsigned char pixel);
const char *grayscale_to_block(unsigned char pixel, Style style = Style::Blocky);

void draw_in_terminal(cv::Mat img);
void draw_in_new_file(cv::Mat img, const std::string &filename = "art.txt");
