#include<iostream>
#include<cstdio>
#include<random>
#include<cstring>
#include "samplers/sampler.hpp"
#include "samplers/sampler_random.hpp"
#include "samplers/sampler_stratified.hpp"

static void gen_data(const char* out_path, const char* filename, Sampler* sam,
        int spp)
{
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
    Sample* sample = new Sample[spp];
    FILE* f = fopen(full_path,"w");
    if(f!=NULL)
    {
        sam->get_samples(sample);
        for(int i=0;i<spp;i++)
            fprintf(f,"%f,%f\n",sample[i].posx,sample[i].posy);
        fflush(f);
        fclose(f);
    }
    else
        perror("Error: ");
    free(full_path);
}

void generate_samplers_data(const char* out_path)
{
    unsigned int seed[32];
    for(int i=0;i<32;i++)
        seed[i] = i;
    Sampler* strat9jitt = new SamplerStratified(0,1,0,1,9,seed,true);
    Sampler* strat100jitt = new SamplerStratified(0,1,0,1,100,seed,true);
    Sampler* strat1024jitt = new SamplerStratified(0,1,0,1,1024,seed,true);
    Sampler* strat10000jitt = new SamplerStratified(0,1,0,1,10000,seed,true);
    Sampler* strat9 = new SamplerStratified(0,1,0,1,9,seed,false);
    Sampler* strat100 = new SamplerStratified(0,1,0,1,100,seed,false);
    Sampler* strat1024 = new SamplerStratified(0,1,0,1,1024,seed,false);
    Sampler* strat10000 = new SamplerStratified(0,1,0,1,10000,seed,false);
    Sampler* rand9 = new SamplerRandom(0,1,0,1,9,seed);
    Sampler* rand100 = new SamplerRandom(0,1,0,1,100,seed);
    Sampler* rand1024 = new SamplerRandom(0,1,0,1,1024,seed);
    Sampler* rand10000 = new SamplerRandom(0,1,0,1,10000,seed);
    gen_data(out_path,"stratified_jittered_9",strat9jitt,9);
    gen_data(out_path,"stratified_jittered_100",strat100jitt,100);
    gen_data(out_path,"stratified_jittered_1024",strat1024jitt,1024);
    gen_data(out_path,"stratified_jittered_10000",strat10000jitt,10000);
    gen_data(out_path,"stratified_9",strat9,9);
    gen_data(out_path,"stratified_100",strat100,100);
    gen_data(out_path,"stratified_1024",strat1024,1024);
    gen_data(out_path,"stratified_10000",strat10000,10000);
    gen_data(out_path,"random_9",rand9,9);
    gen_data(out_path,"random_100",rand100,100);
    gen_data(out_path,"random_1024",rand1024,1024);
    gen_data(out_path,"random_10000",rand10000,10000);
    delete strat9jitt;
    delete strat100jitt;
    delete strat1024jitt;
    delete strat10000jitt;
    delete strat9;
    delete strat100;
    delete strat1024;
    delete strat10000;
    delete rand9;
    delete rand100;
    delete rand1024;
    delete rand10000;
}
