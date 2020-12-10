#include <stdio.h>
#include "ifaddrs.h"

void get_ip_info(void);

int main(){
   get_ip_info();
   return 0;
}
void get_ip_info() {
    struct ifaddrs* interfaces = NULL;
    struct ifaddrs* temp_addr = NULL;
    struct ifaddrs* wifi_addr = NULL;
    struct ifaddrs* cellular_addr = NULL;
    int success = getifaddrs(&interfaces);
    if (success == 0)
    {
        // Loop through linked list of interfaces
        temp_addr = interfaces;
        while (temp_addr != NULL)
        {
          if (temp_addr->ifa_addr->sa_family == AF_INET || temp_addr->ifa_addr->sa_family == AF_INET6) // internetwork only
          {
              printf("interface name:%s address:%s\n", temp_addr->ifa_name, inet_ntoa(((struct sockaddr_in*)temp_addr->ifa_addr)->sin_addr));
              if (strncmp(temp_addr->ifa_name, "lo", 2) == 0) {
                  temp_addr = temp_addr->ifa_next;
                  continue;
              }
              if (strcmp(temp_addr->ifa_name, "en0") == 0) {
                  wifi_addr = temp_addr;
              }
              if (strcmp(temp_addr->ifa_name, "pdp_ip0") == 0) {
                  cellular_addr = temp_addr;
              }
          }
          temp_addr = temp_addr->ifa_next;
        }
    }
    freeifaddrs(interfaces);
    
    printf("====================\n");
    if (wifi_addr == NULL) {
        printf("wifi_addr null ptr!");
    }
    else {
        printf("interface name:%s address:%s\n", wifi_addr->ifa_name, inet_ntoa(((struct sockaddr_in*)wifi_addr->ifa_addr)->sin_addr));
    }
    if (cellular_addr == NULL) {
        printf("cellular_addr null ptr!");
    }
    else {
        printf("interface name:%s address:%s\n", cellular_addr->ifa_name, inet_ntoa(((struct sockaddr_in*)cellular_addr->ifa_addr)->sin_addr));
    }
}

