#include<iostream>
#include<cstdio>
#include<random>
#include "materials/lambertian.hpp"
#include "materials/oren_nayar.hpp"

static void gen_data(const char* out_path, const char* filename, Bdf* mat)
{
    //+12 for data_***_val.csv
    //+1 because path could be missing the trailing slash
    //+1 obviously for \0
    char* full_path = (char*) malloc (sizeof(char)*
            (strlen(out_path)+strlen(filename)+12+1+1));
    char* full_path_pdf = (char*)malloc(sizeof(char)*
            (strlen(out_path)+strlen(filename)+12+1+1));
    strcpy(full_path,out_path);
    if(full_path[strlen(full_path)-1]!='/') //append / if not present
    {
        full_path[strlen(full_path)+1]='\0';
        full_path[strlen(full_path)]='/';
    }
    strcat(full_path,"data_");
    strcat(full_path,filename);
    strcpy(full_path_pdf,full_path);
    strcat(full_path,"_val.csv");
    strcat(full_path_pdf,"_pdf.csv");
    FILE* f1 = fopen(full_path,"w");
    FILE* f2 = fopen(full_path_pdf,"w");
    if(f1!=NULL)
        if(f2!=NULL)
        {
            const Vec3 wo(-1.f,0.f,.5f);
            Vec3 wi;
            float pdf;
            for(float i=0.f;i<=1.f;i+=0.03f)
            {
                for(float j=0.f;j<=1.f;j+=0.03f)
                {
                    mat->sample_value(&wo, &wi, i, j, &pdf);
                    fprintf(f1,"%f,%f,%f\n",wi.x,wi.y,wi.z);
                    fprintf(f2,"%f,%f,%f\n",i,j,pdf);
                }
                fprintf(f2,"\n");
            }
            fflush(f1);
            fflush(f2);
            fclose(f1);
            fclose(f2);
        }
        else
            perror("Error: ");
    else
        perror("Error: ");
    free(full_path);
    free(full_path_pdf);
}

void generate_materials_data(const char* out_path)
{
    Bdf* lamb = new Lambertian(ColorRGB(1.f,0.f,0.f));
    Bdf* on = new OrenNayar(ColorRGB(1.f,0.f,0.f),15.f);
    gen_data(out_path,"lambertian",lamb);
    gen_data(out_path,"oren_nayar",on);
    delete lamb;
    delete on;
}
