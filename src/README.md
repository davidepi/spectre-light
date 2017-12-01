### Three executables

The main renderer is composed by three applications: spectre, spectre-rgb and spectre-full.
As explained in the [spectrum.hpp](./utility/spectrum.hpp) file, this is due to the fact that
spectrum class needs to be fast since it is used in a lot of basic calculations. Subclassing
it in order to have an RGB spectrum and a full spectrum comes with an high price and for
this reason this specialization is decided at compile time. The `spectre` executable, after
parsing the input file, decides whether to call `spectre-rgb` or `spectre-full`

### Main and renderer

The [main.cpp](./main.cpp) parses the input file and instantiates a `Renderer` class, then sets
the parameters of this class based on the results of the parsing and finally starts the rendering
by calling the `render(Scene*)` method.

The renderer class creates the various threads and divides the image in sub-images (in order
to maximize the caching). The size of these sub-images is defined in the file [settings.h](./settings.h)
with the name `SPLIT_SIZE`. Then the rendering pipeline is called for every sub-image

### Rendering pipeline

Without going too much in the detail, the rendering pipeline takes a pixel as input and
produces the rgb color for that pixel as output. This is done in the following steps (recall that
ray tracing is performed by tracing a light ray from the pixel to the light)
- A sampler generates a sample position in the pixel. This is done because the pixels are discrete,
while a scene is continuous. Sampling always the same point for a pixel would create very high
aliasing
- A camera takes a sample as input and generates a light ray. Depending on the type of camera
the direction and origin of the ray are created
- An integrator takes the light ray and calculates the amount of radiance carried by it.
This involves calculating every interaction with the lights and the materials
- A filter weights the calculated radiance and affects several pixels near the sample. Filters
are defined in the same folder of the samplers.
-If the pixel does not interfere with other threads' works the radiance converted to rgb is added
to the average.
Otherwise a mutex is checked and if it is locked, instead of stopping the thread, the value is
put into a queue and will be added to the image in the next lock attempt

When every sub-image has been processed the image is saved onto the disk

### Other files
Here is an explanation of the other files not mentioned in the previous sections
- [application_starter.cpp](./application_starter.cpp)
The main file for the `spectre` executable, that will forward the request to `spectre-rgb` or `spectre-full`
- [localization.h](./localization.h) contains the strings for every message that will be printed by the console
- [settings.h](./settings.h) contains several defines and global settings used throughout the whole project
- [validator.h](./validator.h) this file is automatically included by the file settings.h and contains the definition of
several constants and some security checks
