#include "parsed_structs.h"
#include <stdlib.h> /* NULL */
#include <string.h> /* memcpy */

void init_ParsedMaterial(struct ParsedMaterial* val)
{
    val->name = NULL;
    val->type = MATTE;
    val->elem = METAL_GOLD;
    val->ior[0] = 1.45f;
    val->ior[1] = 0.f;
    val->ior[2] = 0.f;
    val->rough_x = 0.f;
    val->rough_y = -1.f;
    val->dist = BECKMANN;
    val->diffuse = NULL;
    val->specular = NULL;
    val->normal = NULL;
}

void init_ParsedMask(struct ParsedMask* val)
{
    val->mask_tex = NULL;
    val->mask_chn = ALPHA;
    val->mask_inv = 0;
}

void init_ParsedTexture(struct ParsedTexture* val)
{
    val->name = NULL;
    val->src = NULL;
    val->color[0] = 255;
    val->color[1] = 255;
    val->color[2] = 255;
    val->scale[0] = 1.f;
    val->scale[1] = 1.f;
    val->shift[0] = 0.f;
    val->shift[1] = 0.f;
    val->filter = TRILINEAR;
}

void init_ParsedLight(struct ParsedLight* val)
{
    val->name = NULL;
    val->time = NULL;
    val->type = AREA;
    val->position[0] = 0.f;
    val->position[1] = 0.f;
    val->position[2] = 0.f;
    val->rotation[0] = 0.f;
    val->rotation[1] = 0.f;
    val->rotation[2] = 0.f;
    val->scale[0] = 1.f;
    val->scale[1] = 1.f;
    val->scale[2] = 1.f;
    val->temperature = -1;
    val->color[0] = 255;
    val->color[1] = 255;
    val->color[2] = 255;
}

void init_ParsedDualMaterial(struct ParsedDualMaterial* val)
{
    val->name = NULL;
    val->first = NULL;
    val->second = NULL;
    init_ParsedMask(&(val->mask));
}

void init_ParsedMeshWorld(struct ParsedMeshWorld* val)
{
    val->name = NULL;
    val->material_name = NULL;
    val->position[0] = 0.f;
    val->position[1] = 0.f;
    val->position[2] = 0.f;
    val->rotation[0] = 0.f;
    val->rotation[1] = 0.f;
    val->rotation[2] = 0.f;
    val->scale[0] = 1.f;
    val->scale[1] = 1.f;
    val->scale[2] = 1.f;
    init_ParsedMask(&(val->mask));
}

void init_ParsedScene(struct ParsedScene* val)
{
    val->successful = 0;
    val->error_msg = NULL;
    val->output = NULL;
    val->sky = NULL;
    val->width = 800;
    val->height = 600;
    val->spp = 121;
    val->camera_pos[0] = 0.f;
    val->camera_pos[1] = 0.f;
    val->camera_pos[2] = 0.f;
    val->camera_tar[0] = 0.f;
    val->camera_tar[1] = 0.f;
    val->camera_tar[2] = 1.f;
    val->camera_up[0] = 0.f;
    val->camera_up[1] = 1.f;
    val->camera_up[2] = 0.f;
    val->fov = 55.f;
    val->camera_type = PERSPECTIVE;
    val->sampler_type = STRATIFIED;
    val->filter_type = MITCHELL;
    val->value0 = 0.33f;
    val->value1 = 0.33f;
    init_ParsedMaterial(&(val->cur_mat.mat));
    init_ParsedDualMaterial(&(val->cur_dualmat.dualmat));
    init_ParsedMask(&(val->cur_mask));
    init_ParsedTexture(&(val->cur_tex.tex));
    init_ParsedMeshWorld(&(val->cur_mesh.mesh));
    init_ParsedLight(&(val->cur_light.light));
    init_ResizableParsed(&(val->parsed_textures));
    init_ResizableParsed(&(val->parsed_materials));
    init_ResizableParsed(&(val->parsed_dualmaterials));
    init_ResizableParsed(&(val->parsed_mesh_world));
    init_ResizableParsed(&(val->parsed_lights));
    init_ResizableStack(&(val->parsed_mesh_object));
    init_ResizableStack(&(val->children));
}

void deinit_ParsedScene(struct ParsedScene* val)
{
    if(val->output != NULL)
    {
        free(val->output);
        val->output = NULL;
    }
    if(val->error_msg != NULL)
    {
        free(val->error_msg);
        val->error_msg = NULL;
    }
    if(val->sky != NULL)
    {
        free(val->sky);
        val->sky = NULL;
    }
    deinit_ResizableParsed(&val->parsed_textures);
    deinit_ResizableParsed(&val->parsed_materials);
    deinit_ResizableParsed(&val->parsed_dualmaterials);
    deinit_ResizableParsed(&val->parsed_mesh_world);
    deinit_ResizableParsed(&val->parsed_lights);
    deinit_ResizableStack(&val->parsed_mesh_object);
    deinit_ResizableStack(&val->children);
}

void merge_ParsedScene(struct ParsedScene* dst, struct ParsedScene* src)
{
    union ParsedElement element;
    while(!empty_ResizableParsed(&src->parsed_textures))
    {
        top_ResizableParsed(&src->parsed_textures, &element);
        pop_ResizableParsed(&src->parsed_textures);
        push_ResizableParsed(&dst->parsed_textures, &element);
    }
    while(!empty_ResizableParsed(&src->parsed_materials))
    {
        top_ResizableParsed(&src->parsed_materials, &element);
        pop_ResizableParsed(&src->parsed_materials);
        push_ResizableParsed(&dst->parsed_materials, &element);
    }
    while(!empty_ResizableParsed(&src->parsed_dualmaterials))
    {
        top_ResizableParsed(&src->parsed_dualmaterials, &element);
        pop_ResizableParsed(&src->parsed_dualmaterials);
        push_ResizableParsed(&dst->parsed_dualmaterials, &element);
    }
    while(!empty_ResizableParsed(&src->parsed_mesh_world))
    {
        top_ResizableParsed(&src->parsed_mesh_world, &element);
        pop_ResizableParsed(&src->parsed_mesh_world);
        push_ResizableParsed(&dst->parsed_mesh_world, &element);
    }
    while(!empty_ResizableParsed(&src->parsed_lights))
    {
        top_ResizableParsed(&src->parsed_lights, &element);
        pop_ResizableParsed(&src->parsed_lights);
        push_ResizableParsed(&dst->parsed_lights, &element);
    }
    while(!empty_ResizableStack(&src->parsed_mesh_object))
    {
        void* val = top_ResizableStack(&src->parsed_mesh_object);
        top_ResizableStack(&src->parsed_mesh_object);
        push_ResizableStack(&dst->parsed_mesh_object, val);
    }
    /* children ignored on purpose -> no recursive parsing */
}

void realloc_ResizableParsed(struct ResizableParsed* arr)
{
    union ParsedElement* tmp = arr->array;
    arr->allocated = arr->allocated << 1;
    arr->array = (union ParsedElement*)malloc(
            sizeof(union ParsedElement)*arr->allocated);
    memcpy(arr->array, tmp, arr->index*sizeof(union ParsedElement));
    free(tmp);
}

void realloc_ResizableStack(struct ResizableStack* arr)
{
    void** tmp = arr->array;
    arr->allocated = arr->allocated << 1;
    arr->array = (void**)malloc(sizeof(void*)*arr->allocated);
    memcpy(arr->array, tmp, arr->index*sizeof(void*));
    free(tmp);
}

void init_ResizableParsed(struct ResizableParsed* arr)
{
    arr->allocated = 1;
    arr->array = (union ParsedElement*)malloc(
            sizeof(union ParsedElement)*arr->allocated);
    arr->index = 0;
}

void init_ResizableStack(struct ResizableStack* arr)
{
    arr->allocated = 1;
    arr->array = (void**)malloc(sizeof(void*)*arr->allocated);
    arr->index = 0;
}

void push_ResizableParsed(struct ResizableParsed* arr, union ParsedElement* val)
{
    if(arr->index == arr->allocated)
        realloc_ResizableParsed(arr);
    arr->array[arr->index++] = *val;
}

void push_ResizableStack(struct ResizableStack* arr, void* val)
{
    if(arr->index == arr->allocated)
        realloc_ResizableStack(arr);
    arr->array[arr->index++] = val;
}

void pop_ResizableParsed(struct ResizableParsed* arr)
{
    arr->index--;
}

void pop_ResizableStack(struct ResizableStack* arr)
{
    arr->index--;
}

void
top_ResizableParsed(const struct ResizableParsed* arr, union ParsedElement* val)
{
    *val = arr->array[arr->index-1];
}

void* top_ResizableStack(const struct ResizableStack* arr)
{
    return arr->array[arr->index-1];
}

void deinit_ResizableParsed(struct ResizableParsed* arr)
{
    if(arr->array != NULL)
    {
        free(arr->array);
        arr->array = NULL;
    }
}

void deinit_ResizableStack(struct ResizableStack* arr)
{
    if(arr->array != NULL)
    {
        free(arr->array);
        arr->array = NULL;
    }
}

int empty_ResizableParsed(const struct ResizableParsed* arr)
{
    return arr->index == 0;
}

int empty_ResizableStack(const struct ResizableStack* arr)
{
    return arr->index == 0;
}
