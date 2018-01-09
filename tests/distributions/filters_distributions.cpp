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

void generate_data(const char* out_path, const char* filename, int extent, 
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

int main(int argc, char* argv[])
{
    const float inc = 0.01f;
    if(argc!=2)
    {
        fprintf(stderr,"Missing output path\n");
        exit(EXIT_FAILURE);
    }
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
    generate_data(argv[1],"box",BOX_FILTER_EXTENT,box,inc);
    generate_data(argv[1],"tent",TENT_FILTER_EXTENT,tent,inc);
    generate_data(argv[1],"gaussian",GAUSSIAN_FILTER_EXTENT,gauss,inc);
    generate_data(argv[1],"mitchell",MITCHELL_FILTER_EXTENT,mitch,inc);
    generate_data(argv[1],"lanczos",LANCZOS_FILTER_EXTENT,sinc,inc);

    delete box;
    delete tent;
    delete gauss;
    delete mitch;
    delete sinc;
    return 0;
}
