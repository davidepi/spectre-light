#include<iostream>
#include<cstdio>
#include "settings.h"
#include "samplers/filter.hpp"
#include "samplers/box_filter.hpp"
#include "samplers/tent_filter.hpp"
#include "samplers/gaussian_filter.hpp"
#include "samplers/mitchell_filter.hpp"
#include "samplers/lanczos_filter.hpp"

//used to generate the filters data

static void gen_data(const char* out_path, const char* filename, int extent, 
        Filter* filter, float incr)
{

    //+9 for data_***.csv
    //+1 because path could be missing the trailing slash
    //+3 for the _x, _y or _xy
    //+1 obviously for \0
    char* full_path = (char*) malloc (sizeof(char)*
            (strlen(out_path)+strlen(filename)+9+1+3+1));
    strcpy(full_path,out_path);
    if(full_path[strlen(full_path)-1]!='/') //append / if not present
    {
        full_path[strlen(full_path)+1]='\0';
        full_path[strlen(full_path)]='/';
    }
    strcat(full_path,"data_");
    strcat(full_path,filename);
    int filename_index = strlen(full_path);

    //x, 2D
    strcat(full_path,"_x.csv");
    FILE* f = fopen(full_path,"w");
    if(f!=NULL)
    {
        for(float i=-extent;i<=extent;i+=incr)
            fprintf(f,"%f,%f\n",i,filter->weight(i,0.f));
        fflush(f);
        fclose(f);
    }
    else
        perror("Error: ");

    //y, 2D
    full_path[filename_index+1] = 'y';
    f = fopen(full_path,"w");
    if(f!=NULL)
    {
        for(float i=-extent;i<=extent;i+=incr)
            fprintf(f,"%f,%f\n",i,filter->weight(0.f,i));
        fflush(f);
        fclose(f);
    }
    else
        perror("Error: ");

    incr *= 10; //decrease resolution for 3d plots
    //xy, 3D
    full_path[filename_index+1] = 'x';
    full_path[filename_index+2] = 'y';
    full_path[filename_index+3] = '\0';
    strcat(full_path,".csv");
    f = fopen(full_path,"w");
    if(f!=NULL)
    {
        for(float i=-extent;i<=extent;i+=incr)
        {
            for(float j=-extent;j<=extent;j+=incr)
                fprintf(f,"%f,%f,%f\n",i,j,filter->weight(i,j));
            fprintf(f,"\n");
        }
        fflush(f);
        fclose(f);
    }
    else
        perror("Error: ");
    free(full_path);
}

void generate_filters_data(const char* out_path)
{
    const float inc = 0.01f;
    Filter* box = new BoxFilter(BOX_FILTER_EXTENT,
                                BOX_FILTER_EXTENT);
    Filter* tent = new TentFilter(TENT_FILTER_EXTENT,
                                  TENT_FILTER_EXTENT);
    Filter* gauss = new GaussianFilter(GAUSSIAN_FILTER_EXTENT,
                                       GAUSSIAN_FILTER_EXTENT, 2.f);
    Filter* mitch = new MitchellFilter(MITCHELL_FILTER_EXTENT,
                                       MITCHELL_FILTER_EXTENT, .33f, .33f);
    Filter* sinc = new LanczosFilter(LANCZOS_FILTER_EXTENT,
                                     LANCZOS_FILTER_EXTENT, 3.f);
    gen_data(out_path,"box",BOX_FILTER_EXTENT,box,inc);
    gen_data(out_path,"tent",TENT_FILTER_EXTENT,tent,inc);
    gen_data(out_path,"gaussian",GAUSSIAN_FILTER_EXTENT,gauss,inc);
    gen_data(out_path,"mitchell",MITCHELL_FILTER_EXTENT,mitch,inc);
    gen_data(out_path,"lanczos",LANCZOS_FILTER_EXTENT,sinc,inc);
    delete box;
    delete tent;
    delete gauss;
    delete mitch;
    delete sinc; 
}
