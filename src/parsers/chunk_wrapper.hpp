//Created,   8 Apr 2019
//Last Edit 11 Apr 2019

/**
 *  \file      chunk_wrapper.hpp
 *  \brief     Wrapper containing several instances of Chunk
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      11 Apr 2019
 *  \copyright GNU GPLv3
 */


#ifndef __CHUNK_WRAPPER_HPP__
#define __CHUNK_WRAPPER_HPP__

#include "chunk.hpp"
#include <list>

/**
 * \brief Wrapper for Chunk objects
 * This class is used to wrap multiple Chunk instances into a single file and
 * provides IO capabilities
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
     * \brief Push a Chunk into the wrapper by copying it
     * \param[in] chunk The Chunk that will be inserted into the wrapper
     */
    void push_chunk(const Chunk& chunk);

    /**
     * \brief Retrieves and removes a Chunk from the wrapper in FIFO order
     * \return The oldest Chunk contained in the wrapper
     */
    Chunk pop_chunk();

    /**
     * \brief Checks whether the wrapper is empty or not
     * \return true if the wrapper is empty, false otherwise
     */
    bool empty();

    /**
     * \brief Writes the Chunk to disk
     * \param[in] path The path where the binary file will be written
     */
    void write(const char* path) const;

    /**
     * \brief Reads a Chunk from the disk
     * \param[in] path The path from where the binary file will be read
     */
    void read(const char* path);

private:
    //list of chunks contained in the wrappers
    std::list<Chunk> chunks;
};

#endif
