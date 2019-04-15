//Created,   7 Apr 2019
//Last Edit 14 Apr 2019

/**
 *  \file      chunk.hpp
 *  \brief     Class containing arbitrary binary data
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      14 Apr 2019
 *  \copyright GNU GPLv3
 */


#ifndef __CHUNK_HPP__
#define __CHUNK_HPP__

#include <cstdint>
#include <vector>
#include <string>

//Forward declarations, both these classes needs to read the Chunk data
class ChunkWrapper;

class ChunkNamed;

/**
 * \brief Class containing data in binary form.
 *
 * This is a generic class embedding some binary data. It can be seen as an
 * array that can handle multiple types and endianness. The class consist of
 * methods that can be used to push or pop values inside the chunk. The
 * underlying data structure is vector for the following reasons:
 * <ul>
 *      <li>push has to be done at back</li>
 *      <li>pop has to be done at front</li>
 *      <li>it needs to be iterable</li>
 * </ul>
 * The queue is not iterable, and a list wasted too much data on pointers
 * (given that the structure encloses single bytes means 1600% overhead). For
 * this reason, a vector is used and values are never actually removed, a
 * pointer to the head is moved. Usually once all the values are popped, the
 * chunk can be thrown away
 *
 * This class has the ability to wrap a single Chunk, like a
 * normal array of bytes, although the size must be explicitly provided.
 * Again this is because of overheads and the fact that usually a chunk size
 * should be known at compile time (for example, Matrix4 will always be 16*4
 * bytes). In case the size is dynamic, it can be manually inserted as a
 * number before the actual data, thus only when needed and only of the
 * needed size.
 */
class Chunk
{
    friend ChunkWrapper;
    friend ChunkNamed;
public:

    /**
     * \brief Default constructor
     */
    Chunk() = default;

    /**
     * \brief Default destructor
     */
    ~Chunk() = default;

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

    /**
     * \brief Push a chunk inside this class
     *
     * Recall that the chunk size will NOT be pushed and it is required to
     * retrieve the chunk
     *
     * \warning do not attempt to push ChunkNamed inside this class! Ok, you
     * can do it but the ID will be ignored and it will be impossible to
     * retrieve the class as a ChunkNamed
     *
     * \param[in] chunk The chunk that will be pushed inside this one
     */
    void push_chunk(const Chunk* chunk);

    /**
     * \brief Retrieves a chunk from this one
     * \param[out] chunk The chunk that will be filled
     * \param[in] size The size of the retrieved chunk. You should take care
     * of this value.
     */
    void pop_chunk(Chunk* chunk, uint64_t size);

    /**
     * \brief Returns the size in bytes of the data contained by this chunk
     * \return The amount of data of this chunk
     */
    uint64_t size() const;

protected:

    /**
     * \brief Vector containing the chunk data.
     *
     * An explanation of why not a list is written in the class documentation
     */
    std::vector<uint8_t> data;

    /**
     * \brief Head of the vector
     *
     * An index to the next member that will be popped
     */
    uint64_t head = 0;
};

/**
 * \brief A Chunk with an ID
 *
 * This chunk is essentially identical to the Chunk one, except for the fact
 * that it contains an ID. Despite this simple difference this class exists only
 * because of overheads.
 *
 * <ul>
 * <li>Having an ID that can be used to ``name`` a class, implies adding 2
 * bytes of overhead to every instance of ChunkNamed, over the raw data
 * provided by Chunk. Although this seeming negligible, the smallest class that
 * can be serialized in this project is Point2 which is composed by
 * 2 floats for a total of 8 bytes. Then, Point2 can be wrapped inside a
 * Vertex class, which contains a Point3, a Normal, and a Point2 for a
 * total of 32 bytes.
 * Adding a tiny 2 bytes of overhead for every class means that
 * every Vertex will have 6 extra bytes of overhead, that could be used
 * to store something else, given that having an ID on those classes is
 * really unnecessary. A Triangle then wraps 3 Vertex and becomes 96 bytes
 * of data with 20 bytes of IDs. This number grows
 * linearly but it is still an additional ~17% of space required. Imagine
 * having to store a lot of
 * primitives with million of triangles. For this reason, simple classes like
 * Vec3 or Matrix4 should use the normal Chunk without ID, where more complex
 * classes like Camera or Bdf should use the version with ID, so a
 * parser can entirely skip classes that it does not understand (or are not
 * yet implemented/version dependent/whatever).</li>
 * </ul>
 */
class ChunkNamed : public Chunk
{
    friend ChunkWrapper;
public:

    /**
     * \brief Default constructor
     */
    ChunkNamed() = default;

    /**
     * \brief Default destructor
     */
    ~ChunkNamed() = default;

    /**
     * \brief Sets the ID for the current chunk
     * \param id
     */
    void set_id(uint16_t id);

    /**
     * \brief Returns the ID of the current chunk
     * \return the ID of the current chunk
     */
    uint16_t get_id() const;

private:
    //ID of the chunk
    uint16_t id = 0;
};


#endif
