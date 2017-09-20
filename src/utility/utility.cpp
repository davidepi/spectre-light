#include "utility.hpp"

void formatSeconds(unsigned int secs, char* out)
{
    if(secs >= 8640000)
        strcpy(out,"> 100 days");
    else if (secs == 0)
        strcpy(out,"< 1 s");
    else
    {
        out[0] = 0x0;
        int s = secs;
        int mins = s/60;
        s%=60;
        int hours = mins/60;
        mins%=60;
        int days = hours/24;
        hours%=24;
        
        //not the most efficient sol, but this is used once in the whole program
        if(days>0)
            sprintf(out,"%dd ",days);
        if(hours>0)
            sprintf(out, "%s%dh ",out,hours);
        if(mins>0)
            sprintf(out, "%s%dm ",out,mins);
        if(s>0)
            sprintf(out, "%s%ds",out,s);
    }
}
