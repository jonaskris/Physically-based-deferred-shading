#pragma once

#include <vector>

#include <DataIdentifier.h>

namespace DataStore
{
    /*
        Used to access vector container of any type of data.
    */
    template <typename T>
    std::vector<T*>& access()
    {
        static std::vector<T*> vec;
        return vec;
    }

    /* 
        Insert into vector of T.
    */
    template <typename T>
    DataIdentifier<T> insert(T* t)
    {
        auto& vec = access<T>();

        vec.push_back(t);
       
        return DataIdentifier<T>(vec.size());
    }

    template <typename T>
    T* get(const DataIdentifier<T> identifier)
    {
        auto& vec = access<T>();

        if(identifier.identifier <= vec.size() && identifier.identifier != 0)
            return vec[identifier.identifier - 1];
        else
            return nullptr;
    }
}