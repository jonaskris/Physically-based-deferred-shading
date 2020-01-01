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
        std::map<unsigned int, DataType*>& access()
        {
            static std::map<unsigned int, DataType*> m;
            return m;
        }

        /* 
            Insert into map of DataType, identify with counter for IdentifierType
            For example, you can insert Model(s) and Camera(s) as Node(s), or Texture2D(s) and 
            TextureCubemap(s) as Texture(s).
        */
        template <typename DataType, typename IdentifierType>
        unsigned int insert(DataType* data)
        {
            auto& m = access<DataType>();

            unsigned int identifier = DataIdentifier<IdentifierType>::newIdentifier();
            m[identifier] = data;
            
            return identifier;
        }

        /*
            For cases where DataType = IdentifierType for method above.
        */
        template <typename DataType>
        unsigned int insert(DataType* data)
        {
            return insert<DataType, DataType>(data);
        }
    
        template <typename DataType>
        DataType* get(unsigned int identifier)
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