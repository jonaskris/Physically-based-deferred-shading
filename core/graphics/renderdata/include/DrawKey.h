#pragma once

#include <cstdint>

namespace graphics
{
    namespace DrawKey
    {
        namespace
        {
            /*
                Make mask of size bits.
            */
            template <unsigned int size>
            uint64_t makeMask()
            {
                return (1UL << size) - 1;
            }
        }
        
        /*
            DRAWKEY STRUCTURE

                ATTRIBUTES
            |  Program  |  Material |    Mesh   | Transform |
            |                       64                      |
            |     16    |     16    |     16    |     16    |
        */
        inline uint64_t write(uint16_t program, uint16_t material, uint16_t mesh, uint16_t transform)
        {
            uint64_t key = 0;

            // Program
            key |= program & makeMask<16>();
            key <<= 16;

            // Material
            key |= material & makeMask<16>();
            key <<= 16;

            // Mesh
            key |= mesh & makeMask<16>();
            key <<= 16;

            // Transform
            key |= transform & makeMask<16>();

            return key;
        }

        inline void read(uint64_t key, uint16_t& program, uint16_t& material, uint16_t& mesh, uint16_t& transform)
        {
            // Transform
            transform = key & makeMask<16>();
            key >>= 16;

            // Mesh
            mesh = key & makeMask<16>();
            key >>= 16;

            // Material
            material = key & makeMask<16>();
            key >>= 16;

            // Program
            program = key & makeMask<16>();
        }
    }
}