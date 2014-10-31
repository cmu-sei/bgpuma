#include "cidrutils.h"

unsigned long IPtoInt(string IP)
{
        unsigned long a,b,c,d;
        sscanf(IP.c_str(),"%ld.%ld.%ld.%ld",&a,&b,&c,&d);
        return ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
}

int cidr_overlap(uint32_t ip1, int n1,
                  uint32_t ip2, int n2)
{
        if (ip1 <= ip2 && ip2+ 1<<(32-n2)-1 <= ip1+(1<<(32-n1)-1)) return 1;
        if (ip2 <= ip1 && ip1+ 1<<(32-n1)-1 <= ip2+(1<<(32-n2)-1)) return 1;
        return 0;
}
