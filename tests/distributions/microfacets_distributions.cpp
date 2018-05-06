#include<iostream>
#include<cstdio>
#include<random>
#include "materials/microfacet_distributions.hpp"
#include "utility/utility.hpp"

static void gen_data(const char* out_path, const char* filename, 
                    MicrofacetDist* md)
{
    //+13 for data_***_pdf.csv
    //+1 because path could be missing the trailing slash
    //+1 obviously for \0
    char* full_path = (char*) malloc (sizeof(char)*
            (strlen(out_path)+strlen(filename)+13+1+1));
    strcpy(full_path,out_path);
    if(full_path[strlen(full_path)-1]!='/') //append / if not present
    {
        full_path[strlen(full_path)+1]='\0';
        full_path[strlen(full_path)]='/';
    }
    strcat(full_path,"data_");
    strcat(full_path,filename);
    strcat(full_path,"_d.csv");
    //D
    FILE* f = fopen(full_path,"w");
    float res;
    if(f!=NULL)
    {
        Vec3 wo(0.f,0.f,0.f);
        for(float i=-1.f;i<=1.f;i+=0.002)
        {
            wo.z = i;
            res = md->D(&wo);
            fprintf(f,"%f,%f\n",i,res);
        }
        fflush(f);
        fclose(f);
    }
    else
        perror("Error: ");
    //G
    full_path[strlen(full_path)-5]='g';
    f = fopen(full_path,"w");
    if(f!=NULL)
    {
        Vec3 wo(0.f,0.f,0.f);
        Vec3 wi(0.f,0.f,0.f);
        float res;
        for(float i=-1.f;i<=1.f;i+=0.03)
        {
            wo.z = i;
            for(float j=-1.f;j<=1.f;j+=0.03)
            {
                wi.z = j;
                res = md->G(&wo,&wi);
                fprintf(f,"%f,%f,%f\n",i,j,res);
            }
            fprintf(f,"\n");
        }
    }
    else
        perror("Error: ");
    //pdf
    full_path[strlen(full_path)-5]='\0';
    strcat(full_path,"pdf.csv");
    f = fopen(full_path,"w");
    if(f!=NULL)
    {
        Vec3 wo(0.f,0.f,1.f);
        Vec3 wh(0.f,0.f,0.f);
        for(float i=-1.f;i<=1.f;i+=0.002)
        {
            wh.z = i;
            res = md->pdf(&wo,&wh);
            fprintf(f,"%f,%f\n",i,res);
        }
        fflush(f);
        fclose(f);
    }
    else
        perror("Error: ");
    free(full_path);
}

static void gen_data_nocos(const char* out_path, const char* filename, 
                    MicrofacetDist* md)
{
    //+19 for data_***_pdf_nocos.csv
    //+1 because path could be missing the trailing slash
    //+1 obviously for \0
    char* full_path = (char*) malloc (sizeof(char)*
            (strlen(out_path)+strlen(filename)+19+1+1));
    strcpy(full_path,out_path);
    if(full_path[strlen(full_path)-1]!='/') //append / if not present
    {
        full_path[strlen(full_path)+1]='\0';
        full_path[strlen(full_path)]='/';
    }
    strcat(full_path,"data_");
    strcat(full_path,filename);
    strcat(full_path,"_d_nocos.csv");
    //G
    FILE* f = fopen(full_path,"w");
    float res;
    if(f!=NULL)
    {
        Vec3 wo(0.f,0.f,0.f);
        for(float i=-40;i<=40;i+=0.5f)
        {
            wo.z = cosf(radians(i));
            res = md->D(&wo);
            fprintf(f,"%f,%f\n",i,res);
        }
        fflush(f);
        fclose(f);
    }
    else
        perror("Error: ");
    //G
    full_path[strlen(full_path)-11]='g';
    f = fopen(full_path,"w");
    if(f!=NULL)
    {
        Vec3 wo(0.f,0.f,0.f);
        Vec3 wi(0.f,0.f,0.f);
        float res;
        for(int i=-90;i<=90;i++)
        {
            wo.z = cosf(radians(i));
            for(int j=-90;j<=90;j++)
            {
                wi.z = cosf(radians(j));
                res = md->G(&wo,&wi);
                fprintf(f,"%d,%d,%f\n",i,j,res);
            }
            fprintf(f,"\n");
        }
    }
    else
        perror("Error: ");
    //pdf
    full_path[strlen(full_path)-11]='\0';
    strcat(full_path,"pdf_nocos.csv");
    f = fopen(full_path,"w");
    if(f!=NULL)
    {
        Vec3 wo(0.f,0.f,1.f);
        Vec3 wh(0.f,0.f,0.f);
        for(float i=-40;i<=40;i+=0.5f)
        {
            wh.z = cosf(radians(i));
            res = md->pdf(&wo,&wh);
            fprintf(f,"%f,%f\n",i,res);
        }
        fflush(f);
        fclose(f);
    }
    else
        perror("Error: ");
    free(full_path);
}

void generate_microfacetdistributions_data(const char* out_path)
{
    MicrofacetDist* blinn = new Blinn(48.f);
    MicrofacetDist* beckmann = new Beckmann(0.2f);
    MicrofacetDist* ggx = new GGXiso(0.2f);
    gen_data(out_path,"blinn",blinn);
    gen_data_nocos(out_path,"blinn",blinn);
    gen_data(out_path,"beckmann",beckmann);
    gen_data_nocos(out_path,"beckmann",beckmann);
    gen_data(out_path,"ggxiso",ggx);
    gen_data_nocos(out_path,"ggxiso",ggx);
    delete blinn;
    delete beckmann;
    delete ggx;
}
