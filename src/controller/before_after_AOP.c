#include<http_request.h>
#include<http_response.h>

#include<stdio.h>

int call_before_controller(HttpRequest* hrq, HttpResponse* hrp)
{
	printRequest(hrq);
	return 0;
}

int call_after_controller(HttpRequest* hrq, HttpResponse* hrp)
{
	printResponse(hrp);
	return 0;
}