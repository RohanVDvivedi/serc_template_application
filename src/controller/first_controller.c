#include<http_request.h>
#include<http_response.h>

int first_controller(HttpRequest* hrq, HttpResponse* hrp)
{
	printRequest(hrq);
	concatenate_dstring(&(hrp->body), dstring_DUMMY_CSTRING("Hello World"));
	return 0;
}