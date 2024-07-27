#include<http_request.h>
#include<http_response.h>
#include<http_header_util.h>

#include<stream_util.h>

#include<stdio.h>
#include<stdint.h>

// this global varibale is not protected, since it is only for an example for testing cooking get and set fnctionality
int client_count = 0;

int cookie_setup_controller(http_request_head* hrq, stream* strm, void* per_request_param, const void* server_param)
{
	int close_connection = 0;

	dmap cookies;
	if(!init_dmap(&cookies, 0))
	{
		close_connection = 1;
		goto EXIT_C_0;
	}
	if(HTTP_NO_ERROR != parse_cookies_from_cookie_header(&cookies, &(hrq->headers)))
	{
		close_connection = 1;
		goto EXIT_C_1;
	}

	// initialize response head
	http_response_head hrp;
	if(!init_http_response_head_from_http_request_head(&hrp, hrq, 200, TRANSFER_CHUNKED))
	{
		close_connection = 1;
		goto EXIT_C_1;
	}
	if(!insert_in_dmap(&(hrp.headers), &get_dstring_pointing_to_literal_cstring("content-type"), &get_dstring_pointing_to_literal_cstring("text/plain")))
	{
		close_connection = 1;
		goto EXIT_C_2;
	}

	if(get_element_count_hashmap(&cookies) == 0)
	{
		client_count++;

		dstring set_cookie_value;
		init_dstring(&set_cookie_value, NULL, 0);
		snprintf_dstring(&set_cookie_value, "client_count=%d", client_count);
		if(!insert_in_dmap(&(hrp.headers), &get_dstring_pointing_to_literal_cstring("set-cookie"), &set_cookie_value))
		{
			deinit_dstring(&set_cookie_value);
			close_connection = 1;
			goto EXIT_C_2;
		}
		deinit_dstring(&set_cookie_value);
	}

	// write http response head
	if(HTTP_NO_ERROR != serialize_http_response_head(strm, &hrp))
	{
		close_connection = 1;
		goto EXIT_C_2;
	}

	stacked_stream sstrm;
	if(!initialize_stacked_stream(&sstrm))
	{
		close_connection = 1;
		goto EXIT_C_2;
	}

	if(0 > intialize_http_body_and_encoding_streams_for_writing(&sstrm, strm, &(hrp.headers)))
	{
		close_connection = 1;
		goto EXIT_C_3;
	}

	int error = 0;

	write_dstring_to_stream(get_top_of_stacked_stream(&sstrm, WRITE_STREAMS), &get_dstring_pointing_to_literal_cstring("I got a Cookie for you"), &error);
	if(error)
	{
		close_connection = 1;
		goto EXIT_C_4;
	}

	flush_all_from_stream(get_top_of_stacked_stream(&sstrm, WRITE_STREAMS), &error);
	if(error)
	{
		close_connection = 1;
		goto EXIT_C_4;
	}

	EXIT_C_4:;
	close_deinitialize_free_all_from_stacked_stream(&sstrm, WRITE_STREAMS);

	EXIT_C_3:;
	deinitialize_stacked_stream(&sstrm);

	EXIT_C_2:;
	deinit_http_response_head(&hrp);

	EXIT_C_1:;
	deinit_dmap(&cookies);

	EXIT_C_0:;
	return close_connection;
}