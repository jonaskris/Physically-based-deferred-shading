#include <iostream>
#include <string>

class Image
{
private:
    std::string file;
    unsigned char* pixels;
    int width, height;

public:
    Image(const std::string& file);
    ~Image();

    int getWidth() const;
    int getHeight() const;
    const unsigned char* const getPixels() const;

    friend std::ostream& operator<<(std::ostream& out, const Image& shader);
};