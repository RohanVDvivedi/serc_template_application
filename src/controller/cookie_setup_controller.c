#include<http_request.h>
#include<http_response.h>

#include<stdio.h>

// this global varibale is not protected, since it is only for an example for testing cooking get and set fnctionality
int client_count = 0;

int cookie_setup_controller(HttpRequest* hrq, HttpResponse* hrp)
{
	dstring* cookie = getCookie(hrq);
	if(cookie == NULL || cookie->cstring[0] == '\0')
	{
		client_count++;

		dstring SetCookie;init_dstring(&SetCookie, NULL, 0);
		snprintf_dstring(&SetCookie, "client_count=%d", client_count);
			setSetCookie(hrp, &SetCookie);
		deinit_dstring(&SetCookie);
	}

	concatenate_dstring(&(hrp->body), dstring_DUMMY_CSTRING("I got a Cookie for you"));
	return 0;
}