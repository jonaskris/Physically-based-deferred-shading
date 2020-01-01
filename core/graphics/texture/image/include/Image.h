#pragma once

#include <iostream>
#include <string>

class Image
{
private:
    std::string file;
    unsigned char* pixels;
    int width, height;
    int channels;

public:
    Image(const std::string& file);
    ~Image();

    int getWidth() const;
    int getHeight() const;
    int getChannels() const;
    const unsigned char* const getPixels() const;

    friend std::ostream& operator<<(std::ostream& out, const Image& shader);
};