#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

#define SERC_ROOT_PATH			"./public"
#define SSL_KEYS_AND_CERTS		"./.serc_config/server"

#include<serc/http_server.h>

int main()
{
	// you handle EPIPE errors of stream and not rely on SIGPIPE
	signal(SIGPIPE, SIG_IGN);

	// HTTP server on port 80
	http_server_run(80, SERC_ROOT_PATH, 1, NULL, 6000, NULL); // soket timeout of 6 seconds

	// HTTPS server on port 443
	//http_server_run(443, SERC_ROOT_PATH, 1, SSL_KEYS_AND_CERTS, NULL);

	return 0;
}