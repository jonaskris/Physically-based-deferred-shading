#pragma once

/*
    DataIdentifier is a class for a unique identifier per T, and
    keeps track of already used identifiers for T.
*/
template <typename T>
class DataIdentifier
{
public:
    unsigned int identifier;

    DataIdentifier() : identifier(0) {}
    explicit DataIdentifier(unsigned int identifier) : identifier(identifier) {}

    operator bool() const { return identifier != 0; }
        
    friend bool operator<(const DataIdentifier<T>& lhs, const DataIdentifier<T>& rhs) { return lhs.identifier < rhs.identifier; }
};