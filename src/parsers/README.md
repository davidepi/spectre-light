# Input File format

The file format expected by *spectre-light* is similar in fashion to a JSON file,
with the following differences:

- Keys are reserved keywords and thus cannot be neither user-defined nor quoted
- Commas can not be inserted between each `key:value` pair
- The toplevel object can not be enclosed in curly braces

Here is an example of the file structure
```
out: "output.tga"
resolution: {
    width: 1280
    height: 1024
}
filter: {
    type: lanczos
    value0: 3.5
}
spp: 36
integrator: pt
sampler: stratified
camera: {
    type: perspective
    position: [0,0,0]
    target: [-1.5,0.0,.9]
    up: [0,1,0]
    fov: 0.55
}
shape: "lamp.obj"
shape: "scene.obj"

light: {
    name: "normal lamp"
    temperature: 5500
}

world: {
    name: "box001"
    position: [-1,0,0]
    scale: 1.5
}

texture: "folder/containing/textures"

```
## Primitives

For every keys the following are the values that can be used

Value | Description | Examples
---|---|---
int | An integer number, negative or non-negative | -2147483647
float | A floating point number | 1.5   .5  1e18    .1E-3  E10
quoted string | A string delimited by a pair of " or '. Escaping is not supported | "Hello world"   'Hello world'
float[n] | An array of n floats delimited by [ ] | [1.5,0.5,0]
object | An object containing `key:values` pair delimited by { }. The possible keys are described in the [Keywords]() section | {type:perspective, fov:55.0}
enum | A keyword used as an enum. The keywords change from object to object, so for a complete list refer to the object description where the enum is required | perspective  lanczos

## Key(word)s
### Toplevel keys
The possible keys are the following:

Key | Type | Usage | Default value
---|---|---|---
out| quoted string | The file that will be written when rendering the current scene | out.ppm
resolution | [object](#resolution) | The resolution of the final rendered image | [Check object description](#resolution)
filter | [object](#filter) | The filter used to process the final image after gathering each sample value | [Check object description](#filter)
spp | int | The number of samples per pixel | 121
integrator | enum | The type of integrator used to solve the rendering equation. The only possible value is `pt` for path trace | pt
sampler | enum | The type of sampler used to gather samples. Possible values are `random` for a pure random sampler or `stratified` for a sampler that subdivides a region in strata and picks a random sample for each strata. The latter is the suggested value | stratified
camera | [object](#camera) | A description of the camera used to render the current scene | [Check object description](#camera)
shape | quoted string | A path to an obj file containing mesh descriptions. The actual mesh/es are not used in the scene until positioned with the `world` keyword | -
light | [object](#light) | Description of a light positioned into the scene | -
world | [object](#world) | Description of a shape positioned into the scene | -
texture | [object](#texture) or quoted string | Path to the texture on disk that will be added to the Texture Library. If the quoted string version is used, the filename without extension will be also the name of the texture. **Be aware of naming conflicts!** If a folder is specified, every image inside the folder will be loaded | -
material | [object](#material) | Description of a material that will be put in the Material Library | -

### Objects
These are the various keys that can be used for objects described in the previous section. These objects must be enclosed in curly braces

#### Resolution
Keys for Resolution objects

Key | Type | Usage | Default value
---|---|---|---
width | int | The width of the rendered image | 800
height | int | The height of the rendered image | 600

#### Camera
Keys for Camera objects

Key | Type | Usage | Default value
---|---|---|---
type | enum | Defines the type of camera. The values can be `perspective`, `orthographic` or `panorama` | perspective
position |float[3] | The position of the camera | [0,0,0]
target | float[3] | The target of the camera |  [0,0,1]
up | float[3] | A vector representing the upward direction seen from the camera | [0,1,0]
fov | float | Used only by perspective cameras, the field of view in degrees | 55

#### Filter
Keys for Filter objects

Key | Type | Usage | Default value
---|---|---|---
type | enum | Defines the type of filter. The values can be `box`, `tent`, `gaussian`, `mitchell` and `lanczos` |  mitchell
value0 | float | The parameter for the filters. Unused in box and tent filter, this value is the σ (falloff) value of the gaussian filter, the B parameter of the Mitchell-Netravali and the 𝜏 parameter of the Lanczos-Sinc filter | Gaussian: 2, Mitchell-Netravali: 0.33,    Lanczos-Sinc: 3
value1 | float | Used only in the Mitchell-Netravali filter as the C parameter | 0.33

#### Light
Keys for Light objects

Key | Type | Usage | Default value
---|---|---|---
name | quoted string | The name of the light model. This is the name of a mesh previously parsed with the `shape` keyword | Syntax error
temperature | int | The temperature in kelvin of the light. This value will set the light color based on its temperature and thus should not be used in conjunction with the `color` keyword | This value is mutually exclusive with the `color` one. The latter is the one used as default
color | float[3] | The spectrum emitted by this light. The spectrum is represented as a 3 values RGB number where `[0,0,0]` is full black and `[1,1,1]` is full white |  [1,1,1]
position | float[3] | The position of the light in the scene | [0,0,0]
rotation | float[3] | The rotation of the light in the scene, in degrees | [0,0,0]
scale | float[3] or float | The scaling applied to the light in the scene. The single float value applies uniform scaling to every dimension | 1

#### World
Keys for World objects

Key | Type | Usage | Default value
---|---|---|---
name | quoted string | The name of the model previously parsed with the `shape` keyword | Syntax error
material | quoted string | The name of the material that will be applied to the model | "Default" material
position | float[3] | The position of the model in the scene | [0,0,0]
rotation | float[3] | The rotation of the model in the scene, in degrees | [0,0,0]
scale | float[3] or float | The scaling applied to the model in the scene. The single float value applies uniform scaling to every dimension | 1

#### Texture
Keys for Texture objects

Key | Type | Usage | Default value
---|---|---|---
name | quoted string | The name of the texture as it will appear in the Texture Library | filename without extension
src | quoted string | The path to the texture on the disk that will be stored in the Texture Library. To load everything inside a folder do not use this object but directly the `texture:"folder"` at toplevel | Syntax error

#### Material
Keys for Material objects

Key | Type | Usage | Default value
---|---|---|---
name | quoted string | The name of the material that will be added to the Library | Syntax error
type | enum | The type of material that will be used. Possible values are `matte`, `glossy`, `metal` or `glass` (used for transmittive materials such as glass or water) | glossy
ior | float | Refractive index of the material. Used in `glass` typed materials | 1.5
element | quoted string | For `metal` typed materials, this will specify a metal from the periodic table for which sampled data will be used. [More informations here](#metals) | -
roughness | float | single value in range [0-1] used to calculate the roughness of a material | 0
anisotropy | float | single value in range [0-1] used to calcualte the y roughness of a material for surfaces that exhibit anisotropic reflections | roughness value
distribution | enum | If the material has a roughness higher than 0, the distribution that will be used to simulate the roughness. Possible values are `blinn`, `beckmann`, `ggx`. If the anisotropy value is set and is different from the roughness, the distribution value will always be `ggx` because it is the only distribution implemented for anisotropic materials | beckmann
diffuse | float[3] or quoted string | RGB values for the diffuse spectrum or name of the texture map that will be used (should be loaded in the library first) | [1,1,1]
specular | float[3] or quoted string | RGB values for the specular spectrum or name of the texture map that will be used (should be loaded in the library first) | [1,1,1]

##### Metals
Possible values for materials with the `metal` keyword. These should be passed as string (case insensitive) to the `element` key of the material object. Note that these will override the `diffuse` and `specular`  parameters. Roughness, distribution and anisotropy can still be used

Value | Element
---|---
Ag | Silver
Al | Aluminium
Au | Gold
Cu | Copper
Fe | Iron
Hg | Mercury
Pb | Lead
Pt | Platinum

