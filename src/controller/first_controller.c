#include<http_request.h>
#include<http_response.h>

int first_controller(HttpRequest* hrq, HttpResponse* hrp)
{
	concatenate_dstring(&(hrp->body), &get_literal_cstring("Hello World"));
	return 0;
}