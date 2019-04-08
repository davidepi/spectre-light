//
// Created by Davide Pizzolotto on 2019-04-08.
//

#ifndef __CHUNK_WRAPPER_HPP__
#define __CHUNK_WRAPPER_HPP__

#include "chunk.hpp"
#include <list>

class ChunkWrapper
{
public:
    ChunkWrapper() = default;
    ~ChunkWrapper() = default;
    void push_chunk(const Chunk& chunk);
    Chunk pop_chunk();
    bool empty();
    void write(const char* path) const;
    void read(const char* path);
private:
    std::list<Chunk> chunks;
};

#endif
