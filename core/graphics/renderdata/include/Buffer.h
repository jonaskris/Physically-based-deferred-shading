#pragma once

#include <string>
#include <vector>

#include <DataIdentifier.h>

namespace graphics
{
    // Container of generic vertices/indices/uv data
    struct Buffer
    {
        std::string uri;
        char* data;
    };

    // Subset of a buffer
    struct BufferView
    {
        DataIdentifier<Buffer> buffer;
        int byteLength, byteOffset, byteStride, target; 
    };

    // Describes how to access data in buffer
    struct Accessor
    {
        DataIdentifier<BufferView> bufferView;
        int offset; // Multiple of sizeof(componentType)
        int componentType; // 5120 (BYTE): 1 byte, 5121 (UNSIGNED_BYTE): 1 byte, 5122 (SHORT): 2 bytes. 5123 (UNSIGNED_SHORT): 2 bytes, 5125 (UNSIGNED_INT): 4 bytes, 5126 (FLOAT): 4 bytes
        std::string type; // "SCALAR": 1 component, "VEC2": 2 components, "VEC3": 3 components, "VEC4": 4 components, "MAT2": 4 components, "MAT3": 9 components, "MAT4": 16 components
        int count;
        std::string min, max;
    };
}