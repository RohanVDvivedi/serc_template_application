#include<httpparser/http_request.h>
#include<httpparser/http_response.h>
#include<httpparser/http_header_util.h>

#include<connman/stacked_stream.h>
#include<cutlery/stream_util.h>

#include<cutlery/deferred_callbacks.h>

int first_controller(http_request_head* hrq, stream* strm, void* per_request_param, const void* server_param)
{
	NEW_DEFERRED_CALLS(16);

	int close_connection = 0;

	// initialize response head
	http_response_head hrp;
	if(!init_http_response_head_from_http_request_head(&hrp, hrq, 200, TRANSFER_CHUNKED))
	{
		close_connection = 1;
		goto EXIT;
	}
	DEFER(deinit_http_response_head, &hrp);
	if(!insert_in_dmap(&(hrp.headers), &get_dstring_pointing_to_literal_cstring("content-type"), &get_dstring_pointing_to_literal_cstring("text/plain")))
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

	stacked_stream sstrm;
	if(!initialize_stacked_stream(&sstrm))
	{
		close_connection = 1;
		goto EXIT;
	}
	DEFER(deinitialize_stacked_stream, &sstrm);

	if(0 > intialize_http_body_and_encoding_streams_for_writing(&sstrm, strm, &(hrp.headers)))
	{
		close_connection = 1;
		goto EXIT;
	}
	DEFER(close_deinitialize_free_all_from_WRITER_stacked_stream, &sstrm);

	int error = 0;

	write_dstring_to_stream(get_top_of_stacked_stream(&sstrm, WRITE_STREAMS), &get_dstring_pointing_to_literal_cstring("Hello World!!"), &error);
	if(error)
	{
		close_connection = 1;
		goto EXIT;
	}

	flush_all_from_stream(get_top_of_stacked_stream(&sstrm, WRITE_STREAMS), &error);
	if(error)
	{
		close_connection = 1;
		goto EXIT;
	}

	EXIT:;
	CALL_ALL_DEFERRED();
	return close_connection;
}