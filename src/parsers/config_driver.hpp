//Created,  31 Mar 2018
//Last Edit  6 Jun 2018

/**
 *  \file      config_driver.hpp
 *  \brief     Bridge between bison parser and the application
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      27 May 2018
 *  \copyright GNU GPLv3
 */


#ifndef __CONFIG_DRIVER_HPP__
#define __CONFIG_DRIVER_HPP__

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "parsers/parser_obj.hpp"
#include "primitives/mesh.hpp"
#include "primitives/sphere.hpp"
#include "utility/console.hpp"
#include "utility/utility.hpp"
#include "utility/file.hpp"
#include "utility/imageIO.hpp"
#include "geometry/vec3.hpp"
#include "geometry/point3.hpp"
#include "cameras/camera_orthographic.hpp"
#include "cameras/camera_perspective.hpp"
#include "cameras/camera360.hpp"
#include "samplers/filter_box.hpp"
#include "samplers/filter_tent.hpp"
#include "samplers/filter_gaussian.hpp"
#include "samplers/filter_mitchell.hpp"
#include "samplers/filter_lanczos.hpp"
#include "integrators/path_tracer.hpp"
#include "parsers/config_parser.tab.hh"
#include "textures/texture_library.hpp"
#include "textures/texture_image.hpp"
#include "materials/bdf.hpp"
#include "materials/metals.hpp"
#include "materials/lambertian.hpp"
#include "materials/oren_nayar.hpp"
#include "materials/microfacet.hpp"
#include "materials/microfacet_distributions.hpp"
#include "materials/reflection.hpp"
#include "materials/refraction.hpp"
#include "utility/scene.hpp"
#include "validator.h"
#include "renderer.hpp"

#define YY_DECL \
yy::ConfigParser::symbol_type yylex(ConfigDriver& driver)

YY_DECL;

/// Type of materials that can be created
enum mat_t
{
    MATTE, GLOSSY, METAL, GLASS
};

/// Struct used to hold information about a material parsed by ConfigParser
class ParsedMaterial
{
public:

    ///name of the material
    std::string name;

    ///element of the material, used only if ParsedMaterial::type is METAL
    metal_t elem;

    /// Type of material
    mat_t type;

    ///Index of refraction of the material
    Spectrum ior;

    ///Roughness of the materials
    float rough_x;

    ///Roughness of the materials in the y axis, -1 if material is isotropic
    float rough_y;

    ///Distribution of the material
    char dist;

    ///Name of the diffuse texture, as it can be found in the TextureLibrary
    std::string diffuse;

    ///Uniform texture if the material is going to use an uniform value
    const TextureUniform* diffuse_uniform;

    ///Name of the specular texture, as it can be found in the TextureLibrary
    std::string specular;

    ///Uniform texture if the material is going to use an uniform value
    const TextureUniform* specular_uniform;

    ///Initialize the class with default values for materials
    ParsedMaterial();
};

/// Struct used to bind a mesh and its materials. A mesh in object space
struct MeshObject
{
    ///The shape in object space. SDLs can also be used
    Shape* mesh;

    ///Array of materials used by this shape
    const Bsdf** materials;

    ///Length of the MeshObject::materials array
    unsigned char materials_len;

    /**
     *  \brief Array of associations triangle-material, represented as offsets
     *  The ith value of this array is the offset in the MeshObject::materials
     *  array to know the material for the ith triangle
     */
    unsigned char* association;
};

///Class used to represent a mesh in WorldSpace. Called Asset in the renderer
class MeshWorld
{
public:

    ///Name of the MeshObject in object space
    std::string name;

    ///Name of the material, if the object space material should be overridden
    std::string material_name;

    ///Translation of the world space mesh from the origin of the scene
    Vec3 position;

    ///Rotation of the world space mesh from the original object space origin
    Vec3 rotation;

    ///Scaling of the world space mesh from the original object space origin
    Vec3 scale;

    ///True if this asset is an area light
    bool is_light;

    ///Temperature of the light if it is a blackbody
    int temperature;

    ///Color of the light, that will be converted to the emitted spectrum
    Vec3 color;

    ///Initialize the class with default values for world space meshes
    MeshWorld():scale(1), is_light(false), temperature(-1), color(255, 255, 255)
    {};
};

/**
 *  \brief Parse an input file
 *
 *  This class is used to parse the main input file received from the user,
 *  describing the scene and the assets used. It automatically includes every
 *  dependency required by the file and allocates a Renderer class ready to
 *  generate the output image.
 */
class ConfigDriver
{
    //ConfigParser accesses some members that other classes shouldn't touch
    friend yy::ConfigParser;

public:

    ///Initialize parsed objects with default values
    ConfigDriver();

    ///Default destructor
    virtual ~ConfigDriver() = default;

    /**
     *  \brief Parse the file specified as parameter
     *
     *  Open a descriptor to the file passed as parameter and parse it and every
     *  subsequent dependency. If errors are encountered, depending on their
     *  gravity, it could even terminate the program. Returns an allocated
     *  Renderer ready to generate the output image
     *
     *  \note Note that the returned Renderer is heap allocated and requires a
     *  call to delete to avoid memory leaks. This is not a good practice but
     *  Renderer class depends on some user defined parameters for its
     *  construction
     *
     *  \param[in] f The file that will be parsed
     *  \param[in,out] scene The scene that will be built, must be already
     *  allocated
     *  \return An heap allocated Renderer
     */
    CHECK_RETVAL_USED
    Renderer* parse(const std::string& f, Scene* scene);

    /**
     *  \brief Error routine called by bison
     *
     *  Output information about a parsing error and terminates the program
     *
     * \param[in] l Location of the error
     * \param[in] m Message describing the error
     */
    void error(const yy::location& l, const std::string& m);

    /**
     *  \brief Error routine called by flex
     *
     *  Output information about an unexpected character and terminates the
     *  program
     *
     *  \param[in] l Location of the unexpected character
     *  \param[in] c The unexpected character
     */
    void unknown_char(const yy::location& l, char c);

//dirty hack because this class is impossible to test otherwise
#ifndef TESTS
private:
#endif

    ///The name of the output image that will be created by the renderer
    std::string output;

    ///The width of the output image that will be created by the renderer
    int width;

    ///The heigth of the output image that will be created by the renderer
    int height;

    ///Performs checks on the resolution (mulitple of SPLIT_SIZE)
    void check_resolution();

    ///Number of samples per pixel that will be used when rendering
    int spp;

    ///Performs checks on the spps, depending on the used sampler
    void check_spp();

    ///The scene, where everything will be added
    Scene* current_scene;

    ///The directory where the input file was found. Used to locate dependencies
    File current_dir;

    ///An SDL representing a Sphere. Used when the MeshObject name is "Sphere"
    Sphere* default_sphere;

    ///Begin the scannin routine. Defined in the file generated by flex
    void scan_begin();

    ///End the scanning routine. Defined in the file generated by flex
    void scan_end();

    ///Get the current scanned line. Defined in the file generated by flex
    int get_line(char* buf, int len);

    /*-----------.
    |   Camera   |
    `-----------*/

    ///Position of the camera in the spcea
    Point3 camera_pos;

    ///Target of the camera
    Point3 camera_tar;

    ///Up vector of the camera
    Vec3 camera_up;

    ///Field of View of the camera
    float fov;

    ///Type of camera, possible values are found in individual camera files
    char camera_type;

    ///Allocate the camera with parsed parameters
    CHECK_RETVAL_USED
    Camera* build_camera();

    /*-------------------------.
    |   Samplers and Filters   |
    `-------------------------*/

    ///Used sampler, values are found in individual sampler files
    char sampler_type;

    ///Type of filter, possible values are found in individual filter files
    char filter_type;

    ///Param for the filter: sigma(Gaussian), B(Mitchell) or tau(Lanczos)
    float value0;

    ///C param for the Mitchell filter
    float value1;

    ///Allocate the filter with parsed parameters
    CHECK_RETVAL_USED
    Filter* build_filter();

    /*---------------.
    |   Integrator   |
    `---------------*/

    ///The integrator that will be used to solve the rendering equation
    LightIntegrator* integrator;

    /*-------------.
    |   Textures   |
    `-------------*/

    ///Temp val for the name of the current texture being parsed
    std::string tex_name;

    ///Temp val for the location on disk of the current texture being parsed
    std::string tex_src;

    ///Temp val, the RGB color of the TextureUniform currently being parsed
    Vec3 tex_color;

    ///Scaling factor of the texture
    Vec2 tex_scale;

    ///Shift factor of the texture
    Vec2 tex_shift;

    ///Load a texture and the corresponding map given the path on disk
    const Texture* load_texture(std::string& path);

    ///Hold all the maps, used to set them the filter after parsing
    std::vector<ImageMap*> all_textures;

    ///Type of filtering that will be used on the textures
    TextureFilter_t tex_filter;

    /**
     * \brief Creates and returns a TextureUniform
     *
     * This texture will be added as anonymous texture since UniformTexture
     * won't be reused (no point in doing that since they are so small). This
     * method is added as anonymous texture to ensure its deallocation when
     * the program is terminated
     *
     * \return The newly created TextureUniform
     */
    const TextureUniform* load_texture_uniform();

    /*--------------.
    |   Materials   |
    `--------------*/

    ///Temp val of the current material being parsed
    ParsedMaterial cur_mat;

    ///List of materials that will be added after adding every texture
    std::vector<ParsedMaterial> deferred_materials;

    ///Add the materials contained in the ConfigDriver::deferred_materials array
    void build_materials();

    ///Other input files that should be parsed along this one
    std::vector<std::string> children;

    /*---------------------------------.
    |   Object space models (Shapes)   |
    `---------------------------------*/

    ///List of shapes that will be added after adding every material
    std::vector<std::string> deferred_shapes;

    ///Map of added shapes (a sort of ShapeLibrary)
    std::unordered_map<std::string, MeshObject> shapes;

    ///Parse an .obj file and add it to ConfigDriver::shapes
    void parse_and_allocate_obj(const char* obj_file);

    /*-----------------------------------------------.
    |   World space models (Assets and AreaLights)   |
    `-----------------------------------------------*/

    ///Mesh or Light in world space currently being parsed
    MeshWorld cur_mesh;

    ///List of meshes/lights that will be added after adding every shape
    std::vector<MeshWorld> deferred_meshes;

    ///Set of used shapes in the scene. The other will be deleted
    std::unordered_set<std::string> used_shapes;

    ///The currently parsed file
    std::string file;

    ///Build meshes and add them to scene
    void build_meshes();
};

#endif
