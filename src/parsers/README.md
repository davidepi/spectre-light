# Input File format

The file format expected by *spectre-light* is similar in fashion to a JSON file,
with the following differences:

- Keys are reserved keywords and thus cannot be neither user-defined nor quoted
- A comma is not required between each `key:value` pair, a whitespace is sufficient
- The toplevel object cannot be enclosed in curly braces

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
```
## Primitives

For every keys the following are the values that can be used

Value | Description | Examples
---|---|---
int | An integer number, negative or non-negative | -2147483647
float | A floating point number | 1.5   .5  1e18    .1E-3  E10
quoted string | A string delimited by a pair of " or '. Escaping is not supported | "Hello world"   'Hello world'
3 values float array | An array of 3 floats delimited by [ ] | [1.5,0.5,0]
object | An object containing `key:values` pair delimited by { }. The possible keys are described in the [Keywords]() section | {type:perspective, fov:55.0}
enum | A keyword used as an enum. The keywords change from object to object, so for a complete list refer to the object description where the enum is required | perspective    lanczos

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
shape | quoted string | A path to an obj file containing mesh descriptions. The actual mesh/es are not used in the scene until positioned with the `world` keyword | Not mandatory, if not defined the list of shapes will be empty
light | [object](#light) | Description of a light positioned into the scene | Not mandatory, if not defined the scene will be black (no lights)
world | [object](#world) | Description of a shape positioned into the scene | Not mandatory, if not defined the scene will be empty

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
position | 3 values float array | The position of the camera | [0,0,0]
target | 3 values float array | The target of the camera |  [0,0,1]
up | 3 values float array | A vector representing the upward direction seen from the camera | [0,1,0]
fov | float | Used only by perspective cameras, the field of view in degrees | 55.0

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
name | quoted string | The name of the light model. This is the name of a mesh previously parsed with the `shape` keyword | No default value, syntax error if not user supplied
temperature | int | The temperature in kelvin of the light. This value will set the light color based on its temperature and thus should not be used in conjunction with the `color` keyword | This value is mutually exclusive with the `color` one. The latter is the one used as default
color | 3 values float array | The spectrum emitted by this light. The spectrum is represented as a 3 values RGB number where `[0,0,0]` is full black and `[1,1,1]` is full white |  [1,1,1]
position | 3 values float array | The position of the light in the scene | [0,0,0]
rotation | 3 values float array | The rotation of the light in the scene, in degrees | [0,0,0]
scale | 3 values float array or single float value | The scaling applied to the light in the scene. The single float value applies uniform scaling to every dimension | 1.0

#### World
Keys for World objects

Key | Type | Usage | Default value
---|---|---|---
name | quoted string | The name of the model previously parsed with the `shape` keyword | No default value, syntax error if not user supplied
material | quoted string | The name of the material that will be applied to the model | "Default" material
position | 3 values float array | The position of the model in the scene | [0,0,0]
rotation | 3 values float array | The rotation of the model in the scene, in degrees | [0,0,0]
scale | 3 values float array or single float value | The scaling applied to the model in the scene. The single float value applies uniform scaling to every dimension | 1.0
