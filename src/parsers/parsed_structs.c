#include "parsed_structs.h"

void init_ParsedMaterial(struct ParsedMaterial* val)
{
    val->name = NULL;
    val->elem = METAL_GOLD;
    val->ior[0] = 1.45f;
    val->ior[1] = 0.f;
    val->ior[2] = 0.f;
    val->ior_sell[0] = 0.f;
    val->ior_sell[1] = 0.f;
    val->ior_sell[2] = 0.f;
    val->rough_x = 0;
    val->rough_y = -1;
    val->dist = BECKMANN;
    val->diffuse = NULL;
    val->diffuse_uniform[0] = 255;
    val->diffuse_uniform[1] = 255;
    val->diffuse_uniform[2] = 255;
    val->specular = NULL;
    val->specular_uniform[0] = 255;
    val->specular_uniform[1] = 255;
    val->specular_uniform[2] = 255;
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
    val->filtering = TRILINEAR;
}

void init_ParsedLight(struct ParsedLight* val)
{
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

void realloc_ResizableParsed(struct ResizableParsed* arr)
{
    union ParsedElement* tmp = arr->array;
    arr->allocated = arr->allocated<<1;
    arr->array = (union ParsedElement*)malloc(sizeof(union ParsedElement)*arr->allocated);
    memcpy(arr->array,tmp,arr->index*sizeof(union ParsedElement));
    free(tmp);
}

void realloc_ResizableStack(struct ResizableStack* arr)
{
    void** tmp = arr->array;
    arr->allocated = arr->allocated<<1;
    arr->array = (void**)malloc(sizeof(void*)*arr->allocated);
    memcpy(arr->array,tmp,arr->index*sizeof(void*));
    free(tmp);
}

void init_ResizableParsed(struct ResizableParsed* arr)
{
    arr->allocated = 1;
    arr->array = (union ParsedElement*)malloc(sizeof(union ParsedElement)*arr->allocated);
    arr->index = 0;
}

void init_ResizableStack(struct ResizableStack* arr)
{
    arr->allocated = 1;
    arr->array = (void**)malloc(sizeof(void*)*arr->allocated);
    arr->index = 0;
}

void push_ResizableParsed(struct ResizableParsed* arr, const union ParsedElement* val)
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

void top_ResizableParsed(const struct ResizableParsed* arr, union ParsedElement* val)
{
    *val = arr->array[arr->index-1];
}

void* top_ResizableStack(const struct ResizableStack* arr)
{
    return arr->array[arr->index-1];
}

void deinit_ResizableParsed(struct ResizableParsed* arr)
{
    free(arr->array);
}

void deinit_ResizableStack(struct ResizableStack* arr)
{
    free(arr->array);
}
