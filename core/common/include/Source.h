#pragma once

#include <iostream>
#include <string>

class Source
{
private:
    std::string directory;
    std::string filename;
    std::string extension;

public:
    Source(const std::string directory, const std::string filename, const std::string extension);
    Source(const std::string source);

    std::string getDirectory() const;
    std::string getFilename() const;
    std::string getExtension() const;
    std::string getFullSource() const;

    bool operator==(const Source& other) const  { return directory == other.getDirectory() && filename == other.getFilename() && extension == other.getExtension(); }

    friend std::ostream& operator<<(std::ostream& out, const Source& source) { out << source.getFullSource(); return out; }
};