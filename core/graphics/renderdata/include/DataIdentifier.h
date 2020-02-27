#pragma once

namespace graphics
{
    /*
        DataIdentifier is a class for a unique identifier per DataType, and
        keeps track of already used identifiers for the DataType.
    */
    template <typename DataType>
    class DataIdentifier
    {
    private:
        static unsigned int counter;
        unsigned int identifier;

    public:
        DataIdentifier() : identifier(++counter) {};
        
        friend bool operator<(const DataIdentifier<DataType>& lhs, const DataIdentifier<DataType>& rhs) { return lhs.identifier < rhs.identifier; }
    };

    template <typename DataType>
    unsigned int DataIdentifier<DataType>::counter = 0;
}