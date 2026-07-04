#ifndef IRC_H
#define IRC_H

#include "includes.h"
#include <pthread.h>

#define MAX_MSG_LENGTH 512
#define MAX_Nick_LENGTH 32
#define MAX_CHANNEL_LENGTH 64

typedef struct {
    char nick_name[MAX_Nick_LENGTH];
    char channel[MAX_CHANNEL_LENGTH];
    char server[INET6_ADDRSTRLEN];
    int sockfd ;
    pthread_t input_thread;
    pthread_t server_thread;
} irc_config_t ;

    extern irc_config_t config;

    void send_command(const char* cmd);
    void* send_input(void* arg);
    void* send_server_demand(void* arg);

    int send_initial_command(const char* nick_name, const char* channel);
    int startups(const char* server, const char* nick_name, const char* channel);
    int parse_arg(int argc, char** argv, irc_config_t* config );

    void cleanup(int sig);


#endif
