### V0.1 FOUNDATIONS ###
- basic framework (vectors, matrices, rays) *DONE*
- spheres, boxes sdl *DONE*
- kd-tree accelerator *DONE*
- basic materials (lambert, perfect reflection/refraction) *DONE*
- area lights *DONE*
- direct lighting tracer *DONE*
- path tracer *DONE*
- simple parser *DONE*
- dispersion *POSTPONED: difficult to test without bdpt*
- bdpt *POSTPONED: there are more important features*
- triangle meshes *Missing area light sampling* **<-**
- bvh aac accelerator *DONE*
- microfacet reflection and transmission (blinn, beckmann, ggx isotropic, ggx anisotropic) *DONE*

### V0.2 ###
- bdpt
- mlt and erpt (depending on the effort)
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
