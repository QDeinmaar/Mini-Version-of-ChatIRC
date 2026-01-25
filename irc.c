#include "includes.h"


    irc_config_t config;

void send_command(const char* cmd) {
    if (!cmd) return;

    if (config.sockfd <= 0) {
        log_error("Socket not connected !");
        return;
    }

    if (send(config.sockfd, cmd, strlen(cmd), 0) < 0) {
        log_error("Failed to send command !");
    }
}





 /*void send_command(const char* cmd){
    if(send(config.sockfd, cmd, strlen(cmd), 0) < 0){

        log_error("Failed to send command !");
    }
} */

void* handle_input(void* arg){
    (void)arg;
    char buffer[256];
    char cmd_buffer[MAX_MSG_LENGTH];


    while (1)
    {
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            log_error("Failed to read the input !");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if(strlen(buffer) == 0){
            continue;
        }

        if(buffer[0] == '/'){
            if(strncmp(buffer, "/QUIT", 5) == 0){
                send_command("QUIT : Leaving\r\n");
                break;
            } else if(strncmp(buffer, "/JOIN", 5) == 0){

	if(config.channel[6] == '#'){
                snprintf(cmd_buffer, sizeof(cmd_buffer), "JOIN %s\r\n", buffer + 6);
	} else {
		snprintf(cmd_buffer, sizeof(cmd_buffer), "JOIN #%s\r\n", buffer + 6);
	     }
                send_command(cmd_buffer);

                strncpy(config.channel, buffer + 6, MAX_CHANNEL_LENGTH - 1);
                config.channel[MAX_CHANNEL_LENGTH - 1] = '\0';

                continue;
            }
        }

	if(config.channel[0] == '\0')
	{
	log_error("Cannot send message : no channel joined");
	continue;
	}

       memset(cmd_buffer, 0, sizeof(cmd_buffer));  // cmd_buffer to 0 maybe it s the mistake 

	if(config.channel[0] == '#'){
        snprintf(cmd_buffer, sizeof(cmd_buffer), "PRIVMSG %s :%s\r\n", config.channel, buffer);
	} 
	printf("--> SENDING :%s ", cmd_buffer);  // just to check the sending msg 
        send_command(cmd_buffer);

	}

        return NULL;

}

void* handle_server_response(void* arg){
    (void)arg;
    char buffer[MAX_MSG_LENGTH];
    int bytes_received;

    while((bytes_received = recv(config.sockfd, buffer, sizeof(buffer) - 1, 0)) > 0){
        buffer[bytes_received] = '\0';

        if(strncmp(buffer, "PING", 4) == 0){
            char pong [MAX_MSG_LENGTH];

            snprintf(pong, sizeof(pong), "PONG%s", buffer + 4);
            send_command(pong);

        } else {
            printf("%s", buffer);
            fflush(stdout);
        } 
        

        if(bytes_received <= 0){

            log_error("You have lost connexion to the server !");
        }

      }
        return NULL;
}

int send_initial_command(const char* nick_name, const char* channel) {
    char cmd_buffer[MAX_MSG_LENGTH];

    snprintf(cmd_buffer, sizeof(cmd_buffer), "NICK %s\r\n", nick_name);
    send_command(cmd_buffer);

    snprintf(cmd_buffer, sizeof(cmd_buffer), "USER %s 0 * : %s\r\n", nick_name, nick_name);
    send_command(cmd_buffer);

    #ifdef POSIX_C_SOURCE
        usleep(100000);
     #else 
        struct timespec ts = {0, 100000000};
        nanosleep(&ts, NULL);
    #endif

    snprintf(cmd_buffer, sizeof(cmd_buffer), "JOIN %s\r\n", channel);
    send_command(cmd_buffer);

    log_infos("Initial command have been sent !");

    return 0;

}

int startups(const char* server, const char* nick_name, const char* channel){

    config.sockfd = connect_to_server(server);

    if(config.sockfd < 0){
        log_infos("Connexion to server failed !");
        return 1;
    }

    send_initial_command(nick_name, channel);


    if (pthread_create(&config.server_thread, NULL, handle_server_response, NULL) != 0){
        log_error("Failed to create a server response !");
        close(config.sockfd);
        return 1;
    }
        

    if (pthread_create(&config.input_thread, NULL, handle_input, NULL) != 0){
        log_error("Failed to handle input !");
        pthread_cancel(config.server_thread);
        close(config.sockfd);
        return 1;
    }

    log_infos("IRC client started successfully !");
    return 0;

}

int parse_arg(int argc, char** argv, irc_config_t* config ){
    int opt;
    int server_set = 0, nick_name_set = 0, channel_set = 0;

    while((opt = getopt(argc, argv, "s:n:c:")) != -1){
        switch (opt)
        {
        case 's':
            strncpy(config->server, optarg, INET6_ADDRSTRLEN - 1);
            config->server[INET6_ADDRSTRLEN - 1] = '\0';
            server_set = 1;            
            break;

        case 'n':
            strncpy(config->nick_name, optarg, MAX_Nick_LENGTH - 1);
            config->nick_name[MAX_Nick_LENGTH - 1] = '\0';
            nick_name_set = 1;
            break;

        case 'c':
            strncpy(config->channel, optarg, MAX_CHANNEL_LENGTH - 1);
            config->channel[MAX_CHANNEL_LENGTH - 1] = '\0';
            channel_set = 1;
            break;

        default:
            printf("Usage : %s -s <irc-server> -n <nick> -c <channel>\n", argv[0]);
            return 1;
        }
    }


    if(!server_set || !nick_name_set || !channel_set){

        printf(" Error: all field are required (-s,-n,-c)\n");
        printf("Usage : %s -s <irc-server> -n <nick> -c <channel>\n", argv[0]);
        return 1;
    }

    return 0;

    }
