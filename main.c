#include "includes.h"

int main(int argc, char** argv) {

    memset(&config, 0, sizeof(config));

    if (parse_arg(argc, argv, &config) != 0)
        return 1;

    signal(SIGINT, cleanup);
    signal(SIGTERM, cleanup);

    if (config.server[0] == '\0' ||
        config.nick_name[0] == '\0' ||
        config.channel[0] == '\0') {
        fprintf(stderr, "Error: server, nick or channel not set!\n");
        return 1;
    }

    printf("Connecting to %s as %s to %s\n",
           config.server, config.nick_name, config.channel);

    if (startups(config.server, config.nick_name, config.channel) != 0) {
        log_error("Failed to start !");
        return 1;
    }

    /* Wait for input thread (QUIT or Ctrl+C) */
    if (config.input_thread)
        pthread_join(config.input_thread, NULL);

    log_infos("Shutting down IRC client !");

    if (config.sockfd > 0) {
        send_command("QUIT : Client is shutting down!\r\n");
        close(config.sockfd);
    }

    if (config.server_thread)
        pthread_cancel(config.server_thread);

    log_infos("IRC client shut down !");
    return 0;
}
