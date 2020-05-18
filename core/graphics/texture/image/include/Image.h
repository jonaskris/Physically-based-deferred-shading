#pragma once

#include <iostream>
#include <string>

#include <Source.h>

namespace graphics
{
    class Image
    {
    private:
        Source source;
        unsigned char* pixels;
        int width, height;
        int channels;
    
    public:
        Image(const Source& source);
        ~Image();
    
        Source getSource() const;

        int getWidth() const;
        int getHeight() const;
        int getChannels() const;
        const unsigned char* const getPixels() const;

        friend std::ostream& operator<<(std::ostream& out, const Image& image);
    };
}