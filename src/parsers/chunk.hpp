//Created,   7 Apr 2019
//Last Edit 11 Apr 2019

/**
 *  \file      chunk.hpp
 *  \brief     Class containing arbitrary binary data
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      11 Apr 2019
 *  \copyright GNU GPLv3
 */


#ifndef __CHUNK_HPP__
#define __CHUNK_HPP__

#include <cstdint>
#include <queue>
#include <string>

//Forward declaration for the ChunkWrapper, because it is needed as friend
class ChunkWrapper;

/**
 * \brief Class containing data in binary form.
 *
 * This is a generic class that should be used by factories in order to
 * reconstruct an object. The class consist of methods that can be used to push
 * or pop values inside the chunk and an id used to give an identity to the
 * chunk. Ideally this will be wrapped alongisde other chunk in a ChunkWrapper.
 *
 * \warning The endianness of the data inside the chunk IS NOT checked!!!
 */
class Chunk
{
    friend ChunkWrapper;
public:
    /**
     * \brief Default constructor
     * \param[in] id An integer representing the ID of the chunk. Ideally an
     * ID should be unique to a specific class stored inside the chunk.
     */
    Chunk(uint16_t id);

    /**
     * \brief Default destructor
     */
    ~Chunk() = default;

    /**
     * \brief Getter for the chunk ID
     * \return the ID of the chunk
     */
    uint16_t get_id() const;

    /**
     * \brief Insert an 8 bit integer into the chunk
     * \param[in] value The value that will be inserted
     * \sa push_int16
     * \sa push_int32
     * \sa push_int64
     * \sa pop_int8
     */
    void push_int8(uint8_t value);

    /**
     * \brief Retrieves and removes an 8 bit integer from the chunk
     * \return The contained 8 bit integer
     * \sa push_int8
     */
    uint8_t pop_int8();

    /**
     * \brief Insert a 16 bit integer into the chunk
     * \param[in] value The value that will be inserted
     * \sa push_int8
     * \sa push_in32
     * \sa push_int64
     * \sa pop_int16
     */
    void push_int16(uint16_t value);

    /**
     * \brief Retrieves and removes a 16 bit integer from the chunk
     * \return The contained 16 bit integer
     * \sa push_int16
     */
    uint16_t pop_int16();

    /**
     * \brief Insert a 32 bit integer into the chunk
     * \param[in] value The value that will be inserted
     * \sa push_int8
     * \sa push_int16
     * \sa push_int64
     * \sa pop_int32
     */
    void push_int32(uint32_t value);

    /**
     * \brief Retrieves and removes a 32 bit integer from the chunk
     * \return The contained 32 bit integer
     * \sa push_int32
     */
    uint32_t pop_int32();

    /**
     * \brief Insert a 64 bit integer into the chunk
     * \param[in] value The value that will be inserted
     * \sa push_int8
     * \sa push_int16
     * \sa push_int32
     * \sa push_int64
     * \sa pop_int64
     */
    void push_int64(uint64_t value);

    /**
     * \brief Retrieves and removes a 64 bit integer from the chunk
     * \return The contained 64 bit integer
     * \sa push_int64
     */
    uint64_t pop_int64();

    /**
     * \brief Insert a float into the chunk
     * \param[in] value The value that will be inserted
     * \sa push_double
     * \sa pop_float
     */
    void push_float(float value);

    /**
     * \brief Retrieves and removes a float from the chunk
     * \return The contained float integer
     * \sa push_float
     */
    float pop_float();

    /**
     * \brief Insert a double into the chunk
     * \param[in] value The value that will be inserted
     * \sa push_float
     * \sa pop_double
     */
    void push_double(double value);

    /**
     * \brief Retrieves and removes a double from the chunk
     * \return The contained double integer
     * \sa push_double
     */
    double pop_double();

    /**
     * \brief Insert a string into the chunk
     * \param[in] value The string that will be inserted
     * \sa pop_string
     */
    void push_string(const std::string& value);

    /**
     * \brief Retrieves and removes a string from the chunk
     * \return The contained string integer
     * \sa push_string
     */
    std::string pop_string();

private:
    //ID of the chunk
    uint16_t id;
    //Queue containing the chunk data
    std::queue<uint8_t> data;
};


#endif
