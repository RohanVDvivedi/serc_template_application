#include<http_request.h>
#include<http_response.h>

int first_controller(HttpRequest* hrq, HttpResponse* hrp)
{
	printResponse(hrp);
	append_to_dstring(hrp->body, "Hello World");
	return 0;
}