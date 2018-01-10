#include<iostream>
#include<cstdio>
#include<random>
#include "primitives/shape.hpp"
#include "primitives/sphere.hpp"
#include "primitives/box.hpp"
#define SAMPLES 1000

static void gen_data(const char* out_path, const char* filename, Shape* sp)
{
    std::uniform_real_distribution<float> unif(0.f,1.f);
    std::default_random_engine engine{static_cast<unsigned int>
            (0x2b427b177f8333d1U)};
    //+9 for data_***.csv
    //+1 because path could be missing the trailing slash
    //+1 obviously for \0
    char* full_path = (char*) malloc (sizeof(char)*
            (strlen(out_path)+strlen(filename)+9+1+1));
    strcpy(full_path,out_path);
    if(full_path[strlen(full_path)-1]!='/') //append / if not present
    {
        full_path[strlen(full_path)+1]='\0';
        full_path[strlen(full_path)]='/';
    }
    strcat(full_path,"data_");
    strcat(full_path,filename);
    strcat(full_path,".csv");
    FILE* f = fopen(full_path,"w");
    if(f!=NULL)
    {
        Matrix4 mat;
        mat.set_identity();
        float* densities = (float*)malloc(sizeof(float)*sp->get_faces_number());
        sp->get_densities_array(&mat,densities);
        Point3 sample;
        Normal sn;
        for(float i=0;i<SAMPLES;i++)
        {
            sp->sample_point(unif(engine),unif(engine),densities,&sample,&sn);
            fprintf(f,"%f,%f,%f\n",sample.x,sample.y,sample.z);
        }
        free(densities);
        fflush(f);
        fclose(f);
    }
    else
        perror("Error: ");
    free(full_path);
}

void generate_primitives_data(const char* out_path)
{
    Shape* sphere = new Sphere;
    Shape* aabb = new Box;
    gen_data(out_path,"sphere",sphere);
    gen_data(out_path,"aabb",aabb);
    delete sphere;
    delete aabb;
}
