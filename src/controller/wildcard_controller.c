#include<http_request.h>
#include<http_response.h>

int wildcard_controller(HttpRequest* hrq, HttpResponse* hrp)
{
	printRequest(hrq);
	append_to_dstring(&(hrp->body), "Hello, from the wildcard_controller");
	return 0;
}