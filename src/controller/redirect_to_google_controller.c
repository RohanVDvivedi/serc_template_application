#include<httpparser/http_request.h>
#include<httpparser/http_response.h>
#include<httpparser/http_header_util.h>

#include<connman/stacked_stream.h>
#include<cutlery/stream_util.h>

#include<cutlery/deferred_callbacks.h>

int redirect_to_google_controller(http_request_head* hrq, stream* strm, void* per_request_param, const void* server_param)
{
	NEW_DEFERRED_CALLS(16);

	int close_connection = 0;

	// initialize response head
	http_response_head hrp;
	if(!init_http_response_head_from_http_request_head(&hrp, hrq, 303, 0))
	{
		close_connection = 1;
		goto EXIT;
	}
	DEFER(deinit_http_response_head, &hrp);
	if(!insert_in_dmap(&(hrp.headers), &get_dstring_pointing_to_literal_cstring("location"), &get_dstring_pointing_to_literal_cstring("http://google.com")))
	{
		close_connection = 1;
		goto EXIT;
	}

	// write http response head
	if(HTTP_NO_ERROR != serialize_http_response_head(strm, &hrp))
	{
		close_connection = 1;
		goto EXIT;
	}

	EXIT:;
	CALL_ALL_DEFERRED();
	return close_connection;
}