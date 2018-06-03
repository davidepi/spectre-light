# Input File format

The file format expected by *spectre-light* is similar in fashion to a JSON file,
with the following differences:

- Keys are reserved keywords and thus cannot be neither user-defined nor quoted
- A comma is not required between each `key:value` pair, a whitespace is sufficient
- The toplevel object can not be enclosed in curly braces

Recall that every relative path declared inside the input file is resolved from the position of the input file itself, instead of the current working directory. This was done in order to depend just by the initial position of the input file.
Relative paths are OS independent: a `folder\file` path can be used on Linux/MacOS and a `folder/file` path can be used on Windows aswell

Here is an example of the file structure
```
out: "output.tga"
resolution: {
    width: 1280
    height: 1024
}
filter:{type: lanczos, value0: 3.5}
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

texture:{name:'Wall',src:"folder/wall.tga"}
material: {
  name: "Red Oren-Nayar"
  type: matte
  diffuse: "Wall"
  specular: [255,255,255]
  roughness: 0.2
}
material: "another_file.txt"
material: "another_file2.txt"

```
## Missing .mtl

As already stated in the [README](../../README.md), this renderer supports `
.obj` files but not their companion `.mtl`. The reason of this discrepancy lies in the tight bound that `.mtl` specification has with the Phong illumination model that greatly limits the expressiveness of a physically based material system.

In order to overcome this limitation, the `mtllib` keyword is ignored while parsing. However, the `usemtl` is still used and the name of the material is searched in the Material Library that contains the materials defined in the main input file.

### Chained (Children) Files

It is possible to load additional configuration files with the following syntax
`material: "path/to/another/file.txt"`. This was intended to mitigate the missing of `.mtl` files by allowing the separation of configuration files from material files. However note the following things:
- Multiple children files are possible, however, this does not hold recursively. Children declared inside childrens are ignored
- Children files are **NOT** exclusively material files. Every keyword will work the same way inside children files, and could potentially add more assets or even overwrite parent's settings

## Primitives

For every key described in the [keyword](#keywords) section, the following values
can be used where specified

Value | Description | Examples
---|---|---
int | An integer number, negative or non-negative | -2147483647
int+ | A positive integer number | 2147483647
float | A floating point number | 1.5   .5  1e18    .1E-3  E10
quoted string | A string delimited by a pair of " or '. Escaping is not supported | "Hello world"   'Hello world'
float[n] | An array of n floats delimited by [ ] | [1.5,0.5,0]
object | An object containing `key:values` pair delimited by { }. The possible keys are described in the [Keywords](#keywords) section | {type:perspective, fov:55.0}
enum | A keyword used as an enum. The keywords change from object to object, so for a complete list refer to the object description where the enum is required | perspective  lanczos

## Key(word)s
### Toplevel keys
The possible keys are described in this section. Note that there are some dependency between the keywords and the following are parsed after reading every file:
- `material` -> depending on `texture`
- `shape` -> depending on `material`
- `light` -> depending on `shape`
- `world` -> depending on `shape`

Key | Type | Usage | Default value
---|---|---|---
out| quoted string | The file that will be written when rendering the current scene | out.ppm
resolution | [object](#resolution) | The resolution of the final rendered image | [Check object description](#resolution)
filter | [object](#filter) | The filter used to process the final image after gathering each sample value | [Check object description](#filter)
spp | int+ | The number of samples per pixel | 121
integrator | enum | The type of integrator used to solve the rendering equation. The only possible value is `path` for path trace | path
sampler | enum | The type of sampler used to gather samples. Possible values are `random` for a pure random sampler or `stratified` for a sampler that subdivides a region in strata and picks a random sample for each strata. The latter is the suggested value | stratified
camera | [object](#camera) | A description of the camera used to render the current scene | [Check object description](#camera)
shape | quoted string | A path to an obj file containing mesh descriptions. The actual mesh/es are not used in the scene until positioned with the `world` keyword | -
light | [object](#light) | Description of a light positioned into the scene | -
world | [object](#world) | Description of a shape positioned into the scene | -
texture | [object](#texture) | Texture that will be loaded into the library | -
material | [object](#material) or quoted string | Description of a material that will be put in the Material Library. The quoted string will chain another file to this one to be parsed, see section [Chained Files](#chained-children-files) for more information | -

### Objects
These are the various keys that can be used for objects described in the previous section. These objects must be enclosed in curly braces

#### Resolution
Keys for Resolution objects

Key | Type | Usage | Default value
---|---|---|---
width | int+ | The width of the rendered image | 800
height | int+ | The height of the rendered image | 600

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
value0 | float | The parameter for the filters. Unused in box and tent filter, this value is the σ (falloff) value of the gaussian filter (a value of 2 is suggested), the B parameter of the Mitchell-Netravali and the 𝜏 parameter of the Lanczos-Sinc filter (a value of 3 is suggested) | 0.33
value1 | float | Used only in the Mitchell-Netravali filter as the C parameter | 0.33
texture | enum | Defines the type of filter used for texture filtering. The values can be `unfiltered`, `trilinear` or `ewa` | trilinear

#### Light
Keys for Light objects

Key | Type | Usage | Default value
---|---|---|---
name | quoted string | The name of the light model. This is the name of a mesh previously parsed with the `shape` keyword | Syntax error
temperature | int+ | The temperature in kelvin of the light. This value will set the light color based on its temperature and thus should not be used in conjunction with the `color` keyword | This value is mutually exclusive with the `color` one. The latter is the one used as default
color | float[3] | The spectrum emitted by this light. The spectrum is represented as a 3 values RGB number in range [0-255] |  [255,255,255]
position | float[3] | The position of the light in the scene | [0,0,0]
rotation | float[3] | The rotation of the light in the scene, in degrees | [0,0,0]
scale | float[3] or float | The scaling applied to the light in the scene. The single float value applies uniform scaling to every dimension | 1

#### World
Keys for World objects

Key | Type | Usage | Default value
---|---|---|---
name | quoted string | The name of the model previously parsed with the `shape` keyword. The name "Sphere" can also be used to reference a sphere without any input obj file. Radius can be set with `scale` keyword | Syntax error
material | quoted string | The name of the material that will be applied to the model. This overrides any material parsed in the .obj file. However, if the original mesh used multiple materials, setting this keyword will override EVERY material with the specified one. Useful only for single-material mesh | Materials parsed in the .obj file
position | float[3] | The position of the model in the scene | [0,0,0]
rotation | float[3] | The rotation of the model in the scene, in degrees | [0,0,0]
scale | float[3] or float | The scaling applied to the model in the scene. The single float value applies uniform scaling to every dimension | 1

#### Texture
Keys for Texture objects

Key | Type | Usage | Default value
---|---|---|---
name | quoted string | The name of the texture as it will appear in the Texture Library | filename without extension
src | quoted string | The path to the texture on the disk that will be stored in the Texture Library | Syntax error
scale | float[2] | Scaling factor of the texture uv coordinates. Note that this factor scales the uv coordinates and not the texture itself. Thus higher numbers will visually produce a smaller texture wrapped on the object | [1,1]

#### Material
Keys for Material objects

Key | Type | Usage | Default value
---|---|---|---
name | quoted string | The name of the material that will be added to the Library | Syntax error
type | enum | The type of material that will be used. Possible values are `matte`, `glossy`, `metal` or `glass` (used for transmittive materials included water). `metal` type materials do not support textures but instead will use `element` keyword to define their appareance | matte
ior | float or float[2] or float[3] or float[3]float[3] | Refractive index of the material. Used in `glass` typed materials. The index of refraction is wavelength dependent and can be issued with a single number, a 2-values array, a 3-values array or two 3-values array. The first will use the same value for every wavelength, the second and third will use Cauchy equation with parameters `ior:[B,C]` and `ior:[B,C,D]` respectively to calculate the values. The third one, used as `ior:[B1,B2,B3][C1,C2,C3]` will use Sellmeier equation instead. The supplied values for Cauchy's `C` and `D` parameters and for Sellmeier's `C1`, `C2` and `C3` parameters are expected in μm. Note that despite having wavelength dependent index of refractions, light dispersion is still not supported  | [1.45,0]
element | enum | For `metal` typed materials, this will specify a metal from the periodic table for which sampled data will be used. [More informations here](#metals) | Au
roughness | float | single value in range [0-1] used to calculate the roughness of a material | 0
anisotropy | float | single value in range [0-1] used to calcualte the y roughness of a material for surfaces that exhibit anisotropic reflections like hairs or brushed steel. If this equals the roughness value or is unset, the surface is assumed isotropic | roughness value
distribution | enum | If the material has a roughness higher than 0, the distribution that will be used to simulate the roughness. Possible values are `blinn`, `beckmann`, `ggx`. If the anisotropy value is set and is different from the roughness, the distribution value will always be `ggx` since it is the only distribution implemented for anisotropic materials | beckmann
diffuse | quoted string or float[3] | The texture map that will be used for the spectrum. If a string is given, the texture name is searched inside the Texture Library and if not found the same string is used as a path to directly load the texture from disk. If also this can't be found, the "Default" texture is used. If an array of values is given an uniform coloured texture is created with the given values, expected as RGB values in range [0-255]. Not supported for `metal` typed materials. In `glass` typed materials the diffuse component is the transmitted one | "Default" (white texture)
specular | quoted string or float[3] | Same input of the diffuse component. Not supported for `metal` typed materials. In `glass` typed materials the specular component is the reflected one| "Default" (white texture)

##### Metals
Possible values for materials with the `metal` keyword. These should be passed as keywords (case insensitive) to the `element` key of the material object. Note that these will override the `diffuse` and `specular`  parameters which are not supported for metals. Roughness, distribution and anisotropy can still be used

Value | Element
---|---
Ag | Silver
Al | Aluminium
Au | Gold
Be | Beryllium
Bi | Bismuth
Co | Cobalt
Cr | Chromium
Cu | Copper
Fe | Iron
Ge | Germanium
Hg | Mercury
K | Potassium
Li | Lithium
Mg | Magnesium
Mn | Manganese
Mo | Molybdenum
Na | Sodium
Nb | Niobium
Ni | Nickel
Pb | Lead
Pd | Palladium
Pt | Platinum
Rh | Rhodium
Ta | Tantalum
Ti | Titanium
V | Vanadium
W | Tungsten
Zn | Zinc
Zr | Zirconium
