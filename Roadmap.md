### V0.1 FOUNDATIONS ###
- [x] basic framework (vectors, matrices, rays)
- [x] spheres, boxes sdl
- [x] kd-tree accelerator
- [x] cameras (orthographic, perpsective, 360 panorama)
- [x] samplers (stratified and pure random)
- [x] filters (box, tent, gaussian, mitchell, lanczos)
- [x] basic materials (lambert, perfect reflection/refraction)
- [x] area lights
- [x] direct lighting tracer
- [x] path tracer
- [x] simple parser
- [x] dispersion **POSTPONED ->** difficult to test without bdpt
- [x] bdpt **POSTPONED ->** there are more important features
- [x] triangle meshes
- [x] bvh aac accelerator
- [x] microfacet reflection and transmission (blinn, beckmann, ggx isotropic, ggx anisotropic)

### V0.2 ###
- bdpt
- mlt and erpt (depending on the effort)
- unit testing
- better parser (lex/yacc, .3ds parsing, .mtl parsing)
- better image IO (at least .jpg and .tiff input and output)
- diffuse textures
- bump/normal textures (depending on the required effort, probably the material system must be changed a bit to include the new "fake" normal)
- displacement/tessellation system?
- environment (sky) system
- sun position and sunlight

### V0.3 ###
- bvh exporter/importer/generator
- texture caching
- memory checks
- memory manager
- load and unload models from memory
- better occlusion testing
- ad hoc intersection methods for occlusion testing
- more?

### V0.4 ###
- volume rendering
- gpu?
