#pragma once

namespace graphics
{
    /*
        DataIdentifier is a generator for a unique identifier per DataType, and
        keeps track of already used identifiers for the DataType.
    */
    template <typename DataType>
    class DataIdentifier
    {
    private:
        static unsigned int counter;

        DataIdentifier() = delete;
        DataIdentifier(const DataIdentifier&) = delete;
        DataIdentifier& operator=(const DataIdentifier&) = delete;

    public:
        static unsigned int newIdentifier() { return ++counter; }
    };

    template <typename DataType>
    unsigned int DataIdentifier<DataType>::counter = 0;
}