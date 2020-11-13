#include<http_request.h>
#include<http_response.h>

int wildcard_controller(HttpRequest* hrq, HttpResponse* hrp)
{
	printRequest(hrq);
	concatenate_dstring(&(hrp->body), dstring_DUMMY_CSTRING("Hello, from the wildcard_controller"));
	return 0;
}