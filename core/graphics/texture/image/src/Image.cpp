#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <istream>

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <Image.h>

Image::Image(const std::string& file, unsigned int desiredChannels) : file(file)
{

    // Read file
    std::ifstream fileStream(file, std::ios::binary);
    std::vector<char> fileContents((std::istreambuf_iterator<char>(fileStream)),
                              (std::istreambuf_iterator<char>()));

    // Load image from file contents
    pixels = stbi_load_from_memory((stbi_uc* const)(&fileContents[0]), fileContents.size(), &width, &height, &channels, desiredChannels);
}

Image::~Image()
{
    stbi_image_free(pixels);
}

int Image::getWidth() const
{
    return width;
}

int Image::getHeight() const
{
    return height;
}

int Image::getChannels() const
{
    return channels;
}

const unsigned char* const Image::getPixels() const
{
    return pixels;
}

std::ostream& operator<<(std::ostream& out, const Image& image)
{
    out << "Filename:  " << image.file << ", width: " << image.width << ", height: " << image.height;
    return out;
}