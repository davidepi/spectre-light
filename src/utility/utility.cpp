//author: Davide Pizzolotto
//license: GNU GPLv3

#include "utility.hpp"

void format_seconds(unsigned int secs, char* out)
{
    out[0] = '\0';
    if(secs >= 8640000)
        strcpy(out,MESSAGE_MORE_THAN_100_DAYS);
    else if (secs == 0)
        strcpy(out,MESSAGE_LESS_THAN_1_SECOND);
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
