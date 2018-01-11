#include<iostream>
#include<cstdio>
#include<random>
#include "primitives/shape.hpp"
#include "primitives/sphere.hpp"
#include "primitives/box.hpp"
#include "primitives/mesh.hpp"
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
    Shape* box = new Box;
    Mesh* icosahedron = new Mesh(20);

    gen_data(out_path,"sphere",sphere);
    gen_data(out_path,"box",box);

    //hardcoded icosahedron
    Point3 p01 = Point3(0.000000,-0.525731,0.850651);
    Point3 p02 = Point3(0.850651,0.000000,0.525731);
    Point3 p03 = Point3(0.850651,0.000000,-0.525731);
    Point3 p04 = Point3(-0.850651,0.000000,-0.525731);
    Point3 p05 = Point3(-0.850651,0.000000,0.525731);
    Point3 p06 = Point3(-0.525731,0.850651,0.000000);
    Point3 p07 = Point3(0.525731,0.850651,0.000000);
    Point3 p08 = Point3(0.525731,-0.850651,0.000000);
    Point3 p09 = Point3(-0.525731,-0.850651,0.000000);
    Point3 p10 = Point3(0.000000,-0.525731,-0.850651);
    Point3 p11 = Point3(0.000000,0.525731,-0.850651);
    Point3 p12 = Point3(0.000000,0.525731,0.850651);

    Normal n01 = Normal(0.934172,0.356822,0.000000);
    Normal n02 = Normal(0.934172,-0.356822,0.000000);
    Normal n03 = Normal(-0.934172,0.356822,0.000000);
    Normal n04 = Normal(-0.934172,-0.356822,0.000000);
    Normal n05 = Normal(0.000000,0.934172,0.356822);
    Normal n06 = Normal(0.000000,0.934172,-0.356822);
    Normal n07 = Normal(0.356822,0.000000,-0.934172);
    Normal n08 = Normal(-0.356822,0.000000,-0.934172);
    Normal n09 = Normal(0.000000,-0.934172,-0.356822);
    Normal n10 = Normal(0.000000,-0.934172,0.356822);
    Normal n11 = Normal(0.356822,0.000000,0.934172);
    Normal n12 = Normal(-0.356822,0.000000,0.934172);
    Normal n13 = Normal(0.577350,0.577350,-0.577350);
    Normal n14 = Normal(0.577350,0.577350,0.577350);
    Normal n15 = Normal(-0.577350,0.577350,-0.577350);
    Normal n16 = Normal(-0.577350,0.577350,0.577350);
    Normal n17 = Normal(0.577350,-0.577350,-0.577350);
    Normal n18 = Normal(0.577350,-0.577350,0.577350);
    Normal n19 = Normal(-0.577350,-0.577350,-0.577350);
    Normal n20 = Normal(-0.577350,-0.577350,0.577350);

    icosahedron->add_triangle(p02,p03,p07,n01);
    icosahedron->add_triangle(p02,p08,p03,n02);
    icosahedron->add_triangle(p04,p05,p06,n03);
    icosahedron->add_triangle(p05,p04,p09,n04);
    icosahedron->add_triangle(p07,p06,p12,n05);
    icosahedron->add_triangle(p06,p07,p11,n06);
    icosahedron->add_triangle(p10,p11,p03,n07);
    icosahedron->add_triangle(p11,p10,p04,n08);
    icosahedron->add_triangle(p08,p09,p10,n09);
    icosahedron->add_triangle(p09,p08,p01,n10);
    icosahedron->add_triangle(p12,p01,p02,n11);
    icosahedron->add_triangle(p01,p12,p05,n12);
    icosahedron->add_triangle(p07,p03,p11,n13);
    icosahedron->add_triangle(p02,p07,p12,n14);
    icosahedron->add_triangle(p04,p06,p11,n15);
    icosahedron->add_triangle(p06,p05,p12,n16);
    icosahedron->add_triangle(p03,p08,p10,n17);
    icosahedron->add_triangle(p08,p02,p01,n18);
    icosahedron->add_triangle(p04,p10,p09,n19);
    icosahedron->add_triangle(p05,p09,p01,n20);
    icosahedron->finalize();
    gen_data(out_path,"mesh",icosahedron);
    delete sphere;
    delete box;
    delete icosahedron;
}
