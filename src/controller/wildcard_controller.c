#include<http_request.h>
#include<http_response.h>
#include<http_header_util.h>

#include<stacked_stream.h>
#include<stream_util.h>

int wildcard_controller(http_request_head* hrq, stream* strm, void* per_request_param, const void* server_param)
{
	int close_connection = 0;

	// initialize response head
	http_response_head hrp;
	init_http_response_head_from_http_request_head(&hrp, hrq, 200, TRANSFER_CHUNKED);
	insert_in_dmap(&(hrp.headers), &get_dstring_pointing_to_literal_cstring("content-type"), &get_dstring_pointing_to_literal_cstring("text/plain"));

	// write http response head
	if(-1 == serialize_http_response_head(strm, &hrp))
	{
		close_connection = 1;
		goto EXIT_C_1;
	}

	stacked_stream sstrm;
	initialize_stacked_stream(&sstrm);

	if(0 > intialize_http_body_and_encoding_streams_for_writing(&sstrm, strm, &(hrp.headers)))
	{
		close_connection = 1;
		goto EXIT_C_2;
	}

	int error = 0;

	write_dstring_to_stream(get_top_of_stacked_stream(&sstrm, WRITE_STREAMS), &get_dstring_pointing_to_literal_cstring("Hello, from the wildcard_controller"), &error);
	if(error)
	{
		close_connection = 1;
		goto EXIT_C_3;
	}

	flush_all_from_stream(get_top_of_stacked_stream(&sstrm, WRITE_STREAMS), &error);
	if(error)
	{
		close_connection = 1;
		goto EXIT_C_3;
	}

	EXIT_C_3:;
	close_deinitialize_free_all_from_stacked_stream(&sstrm, WRITE_STREAMS);

	EXIT_C_2:;
	deinitialize_stacked_stream(&sstrm);

	EXIT_C_1:;
	deinit_http_response_head(&hrp);

	//EXIT_C_0:;
	return close_connection;
}