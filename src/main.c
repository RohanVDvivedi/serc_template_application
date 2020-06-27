#include<stdio.h>
#include<stdlib.h>

#include<http_server.h>

int main()
{
	// HTTP server without SSL on port 80
	//http_server_run(80, 0);

	// HTTP server with SSL on port 443
	http_server_run(443, 1);

	return 0;
}