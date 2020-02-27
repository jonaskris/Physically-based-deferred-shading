#pragma once

#include <glad/glad.h>

#include <vector>
#include <map>

#include <DataIdentifier.h>

namespace graphics
{
    namespace RenderData
    {
        /*
            Used to access map container of any type of data.
        */
        template <typename DataType>
        std::map<DataIdentifier<DataType>, DataType*>& access()
        {
            static std::map<DataIdentifier<DataType>, DataType*> m;
            return m;
        }

        /* 
            Insert into map of DataType.
        */
        template <typename DataType>
        DataIdentifier<DataType> insert(DataType* data)
        {
            auto& m = access<DataType>();

            DataIdentifier<DataType> identifier = DataIdentifier<DataType>();
            m[identifier] = data;
            
            return identifier;
        }
    
        template <typename DataType>
        DataType* get(DataIdentifier<DataType> identifier)
        {
            auto& m = access<DataType>();

            auto it = m.find(identifier);
            if(it == m.end())
                return nullptr;
            else
                return it->second;
        }
    }
}