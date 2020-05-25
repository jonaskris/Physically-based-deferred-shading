#include <Image.h>

#include <vector>
#include <fstream>
#include <istream>

#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace graphics
{
    Image::Image(const Source& source) : source(source)
    {
        // Read file
        std::ifstream fileStream(source.getFullSource(), std::ios::binary);
        std::vector<char> fileContents((std::istreambuf_iterator<char>(fileStream)),
                                  (std::istreambuf_iterator<char>()));

        // Load image from file contents
        pixels = stbi_load_from_memory((stbi_uc* const)(&fileContents[0]), fileContents.size(), &width, &height, &channels, 0);
    }

    Image::~Image()
    {
        stbi_image_free(pixels);
    }

    Source Image::getSource() const { return source; }
    
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
        out << "Source:  " << image.source << ", width: " << image.width << ", height: " << image.height;
        return out;
    }
}