//Created,  24 Mar 2018
//Last Edit 24 Mar 2018

enum camera_t{ORTHOGRAPHIC_CAMERA,
              PERSPECTIVE_CAMERA,
              PANORAMA_CAMERA};
enum sampler_t{STRATIFIED_SAMPLER,
               RANDOM_SAMPLER};
enum filter_t{BOX_FILTER,
              TENT_FILTER,
              GAUSSIAN_FILTER,
              MITCHELL_FILTER,
              LANCZOS_FILTER};
enum integrator_t{PATH_TRACE};

typedef struct
{
    char* output;
    int resolution[2];
    int spp;
    enum camera_t type_camera;
    float camera_fov;
    float camera_up[3];
    float camera_target[3];
    float camera_position[3];
    enum sampler_t type_sampler;
    enum filter_t type_filter;
    enum integrator_t type_integrator;
    float filter_val[2];
}Settings;
