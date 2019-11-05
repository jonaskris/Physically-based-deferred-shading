#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <Image.h>


Image::Image(const std::string& file) : file(file)
{
    pixels = stbi_load((char* const)file.c_str(), &width, &height, 0, STBI_rgb_alpha);
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

const unsigned char* const Image::getPixels() const
{
    return pixels;
}