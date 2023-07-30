#include<http_request.h>
#include<http_response.h>
#include<http_header_util.h>

#include<stacked_stream.h>
#include<stream_util.h>

int redirect_to_google_controller(http_request_head* hrq, stream* strm, void* per_request_param, const void* server_param)
{
	int close_connection = 0;

	// initialize response head
	http_response_head hrp;
	if(!init_http_response_head_from_http_request_head(&hrp, hrq, 303, 0))
	{
		close_connection = 1;
		goto EXIT_C_0;
	}
	if(!insert_in_dmap(&(hrp.headers), &get_dstring_pointing_to_literal_cstring("location"), &get_dstring_pointing_to_literal_cstring("http://google.com")))
	{
		close_connection = 1;
		goto EXIT_C_1;
	}

	// write http response head
	if(HTTP_NO_ERROR != serialize_http_response_head(strm, &hrp))
	{
		close_connection = 1;
		goto EXIT_C_1;
	}

	EXIT_C_1:;
	deinit_http_response_head(&hrp);

	EXIT_C_0:;
	return close_connection;
}