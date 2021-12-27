#include<http_request.h>
#include<http_response.h>

int wildcard_controller(HttpRequest* hrq, HttpResponse* hrp)
{
	concatenate_dstring(&(hrp->body), &get_literal_cstring("Hello, from the wildcard_controller"));
	return 0;
}