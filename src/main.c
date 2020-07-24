#include<stdio.h>
#include<stdlib.h>

#include<config.h>

#include<http_server.h>

int main()
{
	// HTTP server without SSL on port 80
	//http_server_run(80, SERC_ROOT_PATH, 0 NULL, NULL, NULL);

	// HTTP server with SSL on port 443
	http_server_run(443, SERC_ROOT_PATH, 1, NULL, NULL, NULL);

	return 0;
}