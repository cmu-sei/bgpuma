#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>

using namespace std;


unsigned long IPtoInt(string IP);
int cidr_overlap(uint32_t ip1, int n1, uint32_t ip2, int n2);
