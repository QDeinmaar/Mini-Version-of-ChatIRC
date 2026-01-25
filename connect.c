#include "includes.h"

int connect_to_server(const char* hostname_or_ip){
    int sockfd = -1;

    struct addrinfo hints, *result, *ptr;
    char port_str[] = "6667";
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = 0;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;

    status = getaddrinfo(hostname_or_ip, port_str, &hints, &result);
    if(status != 0){
        char error_msg[256];
        snprintf(error_msg, sizeof(error_msg), "getaddrinfo has failed : %s", gai_strerror(status));
        log_error(error_msg);

        return -1;
    }


    for(ptr = result; ptr != NULL; ptr = ptr->ai_next){

        sockfd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sockfd == -1)
        {
	    perror("socket");
            continue;
        }

        if (connect(sockfd, ptr->ai_addr, (int)ptr->ai_addrlen) == -1)
        {
	  // for hadlling  errors

           perror("connect");
	   close(sockfd);
	   sockfd = -1;

	   continue;
        }

        break;

    }


    int family = ptr->ai_family;
    void *addr = NULL;

    if (family == AF_INET)
        addr = &((struct sockaddr_in*)ptr->ai_addr)->sin_addr;
    else if (family == AF_INET6)
        addr = &((struct sockaddr_in6*)ptr->ai_addr)->sin6_addr;


    freeaddrinfo(result);

    if (sockfd == -1) {
        log_error("Failed to connect to any address");
    return -1;
    }

        char ip_str[INET6_ADDRSTRLEN];
        inet_ntop(family, addr, ip_str, sizeof(ip_str));

        char log_msg[256];
        snprintf(log_msg, sizeof(log_msg),
         "Connected to %s (%s:6667)", hostname_or_ip, ip_str);
        log_infos(log_msg);

    return sockfd;
  
}
