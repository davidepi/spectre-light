/** Created 13-9-2018 */

#ifndef __PARSED_STRUCTS_H__
#define __PARSED_STRUCTS_H__

#include <stdlib.h> /* NULL */
#include <string.h> /* memcpy */
#include "lights/types_light.h"
#include "materials/types_metal.h"
#include "materials/types_microfacet.h"
#include "textures/types_imgchannel.h"
#include "samplers/types_sampler.h"
#include "cameras/types_camera.h"

/** Type of materials that can be created */
enum mat_t
{
    MATTE, GLOSSY, METAL, GLASS
};

/** Struct used to hold information about a material parsed by bison */
struct ParsedMaterial
{
    /** Name of the material */
    char* name;
    
    /** Element of the material, used only if ParsedMaterial::type is METAL */
    enum metal_t elem;
    
    /** Type of material */
    enum mat_t type;
    
    /** Distribution of the material */
    enum microfacet_t dist;
    
    /** Index of refraction of the material (if cauchy is used) */
    float ior[3];
    
    /** Index of refraction of the material (if sellmeier is used) */
    float ior_sell[3];
    
    /** Roughness of the materials */
    float rough_x;
    
    /** Roughness of the materials in the y axis, -1 if material is isotropic */
    float rough_y;
    
    /** Name of the diffuse texture, as it can be found in the TextureLibrary */
    char* diffuse;
    
    /** Uniform texture if the material is going to use an uniform value */
    uint8_t diffuse_uniform[3];
    
    /** Name of the specular texture, as it is found in the TextureLibrary */
    char* specular;
    
    /** Uniform texture if the material is going to use an uniform value */
    uint8_t specular_uniform[3];
    
    /** Name of the normal texture, as it can be found in the TextureLibrary */
    char* normal;
};

/**
 *  \brief Initialize a ParsedMaterial struct (no allocation involved)
 *  \param[in,out] val The struct that will be initialized
 */
void init_ParsedMaterial(struct ParsedMaterial* val);

/** Struct used to hold information about a mask parsed by bison */
struct ParsedMask
{
    /** Name of the texture used as mask */
    char* mask_tex;
    
    /** Channel of the texture used as mask */
    enum imgchannel_t mask_chn;
    
    /** true if the texture used as mask should be inverted */
    uint8_t mask_inv;
};

/**
 *  \brief Initialize a ParsedMask struct (no allocation involved)
 *  \param[in,out] val The struct that will be initialized
 */
void init_ParsedMask(struct ParsedMask* val);

/** Struct used to hold information about a texture parsed by bison */
struct ParsedTexture
{
    /** Temp val for the name of the current texture being parsed */
    char* name;
    
    /** Temp val for the location on disk of the current texture being parsed */
    char* src;
    
    /** Temp val, the RGB color of the TextureUniform currently being parsed */
    uint8_t color[3];
    
    /** Scaling factor of the texture */
    float scale[2];
    
    /** Shift factor of the texture */
    float shift[2];
    
    /** Type of filtering that will be used on the textures */
    enum texturefilter_t filtering;
};

/**
 *  \brief Initialize a ParsedTexture struct (no allocation involved)
 *  \param[in,out] val The struct that will be initialized
 */
void init_ParsedTexture(struct ParsedTexture* val);

/** Struct used to hold information about a light parsed by bison */
struct ParsedLight
{
    /** Name of the MeshObject in object space if AreaLight */
    char* name;
    
    /** The light type */
    enum light_t type;
    
    /** Translation of the world space light from the origin of the scene */
    float position[3];
    
    /** Rotation of the world space light from the object space origin */
    float rotation[3];
    
    /** Scaling of the world space light from the object space origin */
    float scale[3];
    
    /** Temperature of the light if it is a blackbody */
    int temperature;
    
    /** Color of the light, that will be converted to the emitted spectrum */
    uint8_t color[3];
    
    /** If this class is a LightSpot, the radius of the spot */
    float radius;
    
    /** If this class is a LightSpot, the radius not exhibiting falloff */
    float falloff;
};

/**
 *  \brief Initialize a ParsedLight struct (no allocation involved)
 *  \param[in,out] val The struct that will be initialized
 */
void init_ParsedLight(struct ParsedLight* val);

/** Struct used to hold information about a dualmaterial parsed by bison */
struct ParsedDualMaterial
{
    /** Name of the current material */
    char* name;
    
    /** Name of the first material composing the dual material */
    char* first;
    
    /** Name of the second material composing the dual material */
    char* second;
    
    /** Mask used in the material */
    struct ParsedMask mask;
};

/**
 *  \brief Initialize a ParsedDualMaterial struct (no allocation involved)
 *  \param[in,out] val The struct that will be initialized
 */
void init_ParsedDualMaterial(struct ParsedDualMaterial* val);

struct ParsedMeshWorld
{
    /** Name of the MeshObject in object space */
    char* name;
    
    /** Name of the material, if the object space material will be overridden */
    const char* material_name;
    
    /** Translation of the world space mesh from the origin of the scene */
    float position[3];
    
    /** Rotation of the world space mesh from the original object space */
    float rotation[3];
    
    /** Scaling of the world space mesh from the original object space origin */
    float scale[3];
    
    /** Mask used for the object */
    struct ParsedMask mask;
};

/**
 *  \brief Initialize a ParsedMeshWorld struct (no allocation involved)
 *  \param[in,out] val The struct that will be initialized
 */
void init_ParsedMeshWorld(struct ParsedMeshWorld* val);

/** Every parsable element wrapped in a single union */
union ParsedElement
{
    struct ParsedMaterial mat;
    struct ParsedLight light;
    struct ParsedMask mask;
    struct ParsedDualMaterial dualmat;
    struct ParsedTexture texture;
    const char* mesh_o;
    struct ParsedMeshWorld mesh_w;
};

/**
 *  \brief Auto resizable stack containing the parsed elements
 *  This stack is written over an array structure and is NOT thread safe.
 */
struct ResizableParsed
{
    /** Actual array of elements */
    union ParsedElement* array;
    
    /** Number of allocated elements */
    uint32_t allocated;
    
    /** Index of the next element that will be added */
    uint32_t index;
};

/**
 *  \brief Auto resizable stack containing a generic pointer
 *  This stack is written over an array structure and is NOT thread safe.
 */
struct ResizableStack
{
    /** Actual array of elements */
    void** array;
    
    /** Number of allocated elements */
    uint32_t allocated;
    
    /** Index of the next element that will be added */
    uint32_t index;
};

/**
 *  \brief Initialize a ResizableParsed stack
 *  Remember to use deinit_ResizableParsed in order to free the memory!
 *  \param[in,out] arr The struct that will be initialized
 */
void init_ResizableParsed(struct ResizableParsed* arr);

/**
 *  \brief Initialize a ResizableStack stack
 *  Remember to use deinit_ResizableStack in order to free the memory!
 *  \param[in,out] arr The struct that will be initialized
 */
void init_ResizableStack(struct ResizableStack* arr);

/**
 *  \brief Push an element into a ResizableParsed stack
 *  \param[in,out] arr The stack where the element will be push
 *  \param[in] val The element that will be push by copy onto the stack
 */
void push_ResizableParsed(struct ResizableParsed* arr, union ParsedElement* val);

/**
 *  \brief Push an element into a ResizableStack stack
 *  \param[in,out] arr The stack where the element will be push
 *  \param[in] val The element that will be push by copy onto the stack
 */
void push_ResizableStack(struct ResizableStack* arr, void* val);

/**
 *  \brief Pop an element from a ResizableParsed stack
 *  \param[in,out] arr The stack from where the element will be popped
 */
void pop_ResizableParsed(struct ResizableParsed* arr);

/**
 *  \brief Pop an element from a ResizableStack stack
 *  \param[in,out] arr The stack from where the element will be popped
 */
void pop_ResizableStack(struct ResizableStack* arr);

/**
 *  \brief Get the element on top of the ResizableParsed stack
 *  \param[in] arr The stack from where the top element will be copied
 *  \param[out] val The value of the top element of the stack
 */
void top_ResizableParsed(const struct ResizableParsed* arr, union ParsedElement* val);

/**
 *  \brief Get the element on top of the ResizableStack stack
 *  \param[in] arr The stack from where the top element will be copied
 *  \return The value of the top element of the stack
 */
void* top_ResizableStack(const struct ResizableStack* arr);

/**
 *  \brief Deallocate the ResizableParsed stack
 *  \param[in,out] arr The stack that will be deallocated
 */
void deinit_ResizableParsed(struct ResizableParsed* arr);

/**
 *  \brief Deallocate the ResizableStack stack
 *  \param[in,out] arr The stack that will be deallocated
 */
void deinit_ResizableStack(struct ResizableStack* arr);

/** Struct containing the parsed settings for an entire scene */
struct ParsedScene
{
    /*------------------.
    |   Temp instances  |
    `------------------*/
    
    /** Temp material that will be copied where needed */
    struct ParsedMaterial cur_mat;
    
    /** Temp dualmaterial that will be copied where needed */
    struct ParsedDualMaterial cur_dualmat;
    
    /** Temp mask that will be copied where needed */
    struct ParsedMask cur_mask;
    
    /** Temp texture that will be copied where needed */
    struct ParsedTexture cur_tex;
    
    /** Temp mesh in world space that will be copied where needed */
    struct ParsedMeshWorld cur_mesh;
    
    /** Temp light that will be copied where needed */
    struct ParsedLight cur_light;
    
     /*----------------.
     |   Image params  |
     `----------------*/
    
    /** The name of the output image that will be created by the renderer */
    char* output;
    
    /** The width of the output image that will be created by the renderer */
    int width;
    
    /** The heigth of the output image that will be created by the renderer */
    int height;
    
    /** Number of samples per pixel that will be used when rendering */
    int spp;
    
     /*-----------.
     |   Camera   |
     `-----------*/
    
    /** Position of the camera in the space */
    float camera_pos[3];
    
    /** Target of the camera */
    float camera_tar[3];
    
    /** Up vector of the camera */
    float camera_up[3];
    
    /** Field of View of the camera */
    float fov;
    
    enum camera_t camera_type;
    
     /*-------------------------.
     |   Samplers and Filters   |
     `-------------------------*/
    
    /** Used sampler, values are found in individual sampler files */
    enum sampler_t sampler_type;
    
    /** Type of filter, possible values are found in individual filter files */
    enum filter_t filter_type;
    
    /** Param for the filter: sigma(Gaussian), B(Mitchell) or tau(Lanczos) */
    float value0;
    
    /** C param for the Mitchell filter */
    float value1;
    
    /** Filter used for every texture */
    enum texturefilter_t tex_filter;
    
    /*--------------.
    |   Containers  |
    `--------------*/
    
    /** Arrat containing every parsed texture */
    struct ResizableParsed parsed_textures;
    
    /** Arrat containing every parsed material */
    struct ResizableParsed parsed_materials;
    
    /** Arrat containing every parsed dualmaterial */
    struct ResizableParsed parsed_dualmaterials;
    
    /** Arrat containing every parsed object space model */
    struct ResizableStack parsed_mesh_object;
    
    /** Arrat containing every parsed world space model */
    struct ResizableParsed parsed_mesh_world;
    
    /** Arrat containing every parsed light */
    struct ResizableParsed parsed_lights;
    
    /** Arrat containing every parsed children */
    struct ResizableStack children;
    
};

/**
 *  \brief Initialize a ParsedScene
 *  \param[in,out] val The struct that will be initialized
 */
void init_ParsedScene(struct ParsedScene* val);

/**
 *  \brief Frees the memory of objects inside a ParsedScene
 *  \warning This does not frees the memory of the string contained inside the
 *  ParsedScene! Those must be handled by the programmer!
 *  \param[in,out] val The ParsedScene that will be deallocated
 */
void deinit_ParsedScene(struct ParsedScene* val);

#endif
