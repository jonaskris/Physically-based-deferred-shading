#include <Source.h>

Source::Source(const std::string directory, const std::string filename, const std::string extension) : directory(directory), filename(filename), extension(extension) {}
Source::Source(const std::string source)
{
    size_t directoryEnd = source.find_last_of('/') + 1;
    size_t filenameEnd = source.find_last_of('.') + 1;

    directory = source.substr(0, directoryEnd);
    filename = source.substr(directoryEnd, filenameEnd - directoryEnd - 1);
    extension = source.substr(filenameEnd, source.length() - filenameEnd);
}

std::string Source::getDirectory() const { return directory; }
std::string Source::getFilename() const { return filename; }
std::string Source::getExtension() const { return extension; }
std::string Source::getFullSource() const { return directory + filename + '.' + extension; }
