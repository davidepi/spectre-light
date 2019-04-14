//Created,   8 Apr 2019
//Last Edit 14 Apr 2019

/**
 *  \file      chunk_wrapper.hpp
 *  \brief     Wrapper containing several instances of Chunk
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      14 Apr 2019
 *  \copyright GNU GPLv3
 */


#ifndef __CHUNK_WRAPPER_HPP__
#define __CHUNK_WRAPPER_HPP__

#include "chunk.hpp"
#include <list>

/**
 * \brief Wrapper for ChunkNamed objects
 *
 * This class is used to wrap multiple ChunkNamed instances into a single file
 * and provides IO capabilities. This class does not operates over Chunk
 * classes because the idea is that if a Chunk is not understood it can be
 * easily skip (different versions/unimplemented materials/whatever). Thus, a
 * Chunk must have an ID to act as a sort of ``name`` for the underlying class.
 *
 * Unlike the Chunk class, the underlying structure here is a list. This
 * class wraps entire chunks and not single bytes, so the list pointers overhead
 * won't kill the memory.
 */
class ChunkWrapper
{

public:
    /**
     * \brief Default constructor
     */
    ChunkWrapper() = default;

    /**
     * \brief Default destructor
     */
    ~ChunkWrapper() = default;

    /**
     * \brief Push a ChunkNamed into the wrapper by MOVING it
     *
     * \warning The original object should not be used anymore!
     *
     * \param[in] chunk The ChunkNamed that will be inserted into the wrapper
     */
    void push_chunk(ChunkNamed& chunk);

    /**
     * \brief Retrieves and removes a ChunkNamed from the wrapper in FIFO order
     * \return The oldest ChunkNamed contained in the wrapper
     */
    void pop_chunk(ChunkNamed* chunk);

    /**
     * \brief Checks whether the wrapper is empty or not
     * \return true if the wrapper is empty, false otherwise
     */
    bool empty();

    /**
     * \brief Writes every ChunkNamed to disk
     * \param[in] path The path where the binary file will be written
     */
    void write(const char* path) const;

    /**
     * \brief Reads a ChunkNamed from the disk
     * \param[in] path The path from where the binary file will be read
     */
    void read(const char* path);

private:
    //list of chunks contained in the wrappers. This is a list of chunks to
    // avoid a super huge overhead due to pointers to single uint8_t. Then
    // all these chunks will be manually written to file in order to retain
    // only the necessary data.
    std::list<ChunkNamed> chunks;
};

#endif
