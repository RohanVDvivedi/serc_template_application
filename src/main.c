#include<stdio.h>
#include<stdlib.h>

#define SERC_ROOT_PATH			"./public"
#define SSL_KEYS_AND_CERTS		"./.serc_config/server"

#include<http_server.h>

int main()
{
	// HTTP server on port 80
	http_server_run(80, SERC_ROOT_PATH, NULL);

	// HTTPS server on port 443
	//http_server_run(443, SERC_ROOT_PATH, SSL_KEYS_AND_CERTS);

	return 0;
}