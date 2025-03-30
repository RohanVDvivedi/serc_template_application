#include<httpparser/http_request.h>
#include<httpparser/http_response.h>

#include<stdio.h>
#include<stdlib.h>

void* new_per_request_param(const void* server_param)
{
	int* prp = malloc(sizeof(int));
	*prp = rand();
	return prp;
}

int call_before_controller(http_request_head* hrq, stream* strm, void* per_request_param, const void* server_param)
{
	printf("before : %d\n", *((int*)(per_request_param)));
	print_http_request_head(hrq);
	return 0;
}

int call_after_controller(http_request_head* hrq, stream* strm, void* per_request_param, const void* server_param)
{
	printf("after : %d\n", *((int*)(per_request_param)));
	print_http_request_head(hrq);
	return 0;
}

void del_per_request_param(void* per_request_param, const void* server_param)
{
	free(per_request_param);
}