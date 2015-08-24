/*
Copyright 2015 Carnegie Mellon University

This material is based upon work funded and supported by Department of Homeland Security under Contract No. FA8721-05-C-0003 with Carnegie Mellon University for the operation of the Software Engineering Institute, a federally funded research and development center sponsored by the United States Department of Defense.

Any opinions, findings and conclusions or recommendations expressed in this material are those of the author(s) and do not necessarily reflect the views of Department of Homeland Security or the United States Department of Defense.

NO WARRANTY. THIS CARNEGIE MELLON UNIVERSITY AND SOFTWARE ENGINEERING INSTITUTE MATERIAL IS FURNISHED ON AN AS-IS BASIS. CARNEGIE MELLON UNIVERSITY MAKES NO WARRANTIES OF ANY KIND, EITHER EXPRESSED OR IMPLIED, AS TO ANY MATTER INCLUDING, BUT NOT LIMITED TO, WARRANTY OF FITNESS FOR PURPOSE OR MERCHANTABILITY, EXCLUSIVITY, OR RESULTS OBTAINED FROM USE OF THE MATERIAL. CARNEGIE MELLON UNIVERSITY DOES NOT MAKE ANY WARRANTY OF ANY KIND WITH RESPECT TO FREEDOM FROM PATENT, TRADEMARK, OR COPYRIGHT INFRINGEMENT.

This material has been approved for public release and unlimited distribution.

CERT® is a registered mark of Carnegie Mellon University.
*/
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
