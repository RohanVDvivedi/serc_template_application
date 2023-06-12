#include<http_request.h>
#include<http_response.h>

#include<stdio.h>
#include<stdlib.h>

int call_before_controller(http_request_head* hrq, stream* strm, void** per_request_param, const void* server_param)
{
	*per_request_param = malloc(sizeof(int));
	*((int*)(*per_request_param)) = rand();
	printf("before : %d\n", *((int*)(*per_request_param)));
	print_http_request_head(hrq);
	return 0;
}

int call_after_controller(http_request_head* hrq, stream* strm, void** per_request_param, const void* server_param)
{
	printf("before : %d\n", *((int*)(*per_request_param)));
	print_http_request_head(hrq);
	free(*per_request_param);
	return 0;
}