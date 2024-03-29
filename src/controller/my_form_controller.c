#include<http_request.h>
#include<http_response.h>
#include<http_header_util.h>
#include<http_path_and_path_params.h>
#include<http_multipart_form_data.h>

#include<stacked_stream.h>
#include<stream_util.h>

#include<stdio.h>

int my_form_controller(http_request_head* hrq, stream* strm, void* per_request_param, const void* server_param)
{
	int close_connection = 0;

	print_http_request_head(hrq);

	stacked_stream sstrm;
	initialize_stacked_stream(&sstrm);

	if(hrq->method == POST)
	{
		if(0 > intialize_http_body_and_decoding_streams_for_reading(&sstrm, strm, &(hrq->headers)))
		{
			close_connection = 1;
			goto EXIT_C_1;
		}

		int error = 0;

		int is_boundary_present = 0;
		dstring boundary;
		init_empty_dstring(&boundary, 0);

		if(has_url_encoded_params_in_body(&(hrq->headers)))
		{
			dmap params;
			init_dmap(&params, 0);

			printf("attempting to print the params from url encoded body\n");

			if(HTTP_NO_ERROR == (error = parse_url_encoded_params(get_top_of_stacked_stream(&sstrm, READ_STREAMS), &params)))
				for_each_in_dmap(e, &params)
					printf("\t<" printf_dstring_format "> -> <" printf_dstring_format ">\n", printf_dstring_params(&(e->key)), printf_dstring_params(&(e->value)));

			deinit_dmap(&params);
		}
		else if(has_multipart_form_data_in_body(&(hrq->headers), &is_boundary_present, &boundary))
		{
			if(is_boundary_present)
			{
				printf("boundary of multipart/form-data = " printf_dstring_format "\n", printf_dstring_params(&boundary));

				if((error = read_prefix_multipart_form_data(get_top_of_stacked_stream(&sstrm, READ_STREAMS), &boundary)))
					goto MPFD_0;

				while(error == 0)
				{
					multipart_form_data_segment* seg = parse_next_multipart_form_data(get_top_of_stacked_stream(&sstrm, READ_STREAMS), &boundary, &error);

					if(seg == NULL || error)
						break;

					dstring name;		init_empty_dstring(&name, 0);
					dstring filename;	init_empty_dstring(&filename, 0);

					get_name_n_filename_from_content_disposition_header(seg, &name, &filename);

					printf("Multipart field, name = " printf_dstring_format ", filename = " printf_dstring_format "\n", printf_dstring_params(&name), printf_dstring_params(&filename));

					printf("Multipart form data body : \n");
					#define BUFFER_SIZE 1024
					char buffer[BUFFER_SIZE];
					size_t bytes_read = 0;
					while((bytes_read = read_from_stream(&(seg->body_stream), buffer, BUFFER_SIZE, &error)) && error == 0)
					{
						printf("\t<");
						for(size_t i = 0; i < bytes_read; i++)
							printf("%c", buffer[i]);
						printf(">\n");
					}
					printf("\n");

					destroy_multipart_form_data_segment(seg);

					deinit_dstring(&name);
					deinit_dstring(&filename);
				}

				MPFD_0:;
			}
			else
			{
				printf("boundary of multipart/form-data absent\n");

				#define BUFFER_SIZE 1024
				char buffer[BUFFER_SIZE];
				size_t bytes_read = 0;
				while((bytes_read = read_from_stacked_stream(&sstrm, buffer, BUFFER_SIZE, &error)) && error == 0)
				{
					printf("<");
					for(size_t i = 0; i < bytes_read; i++)
						printf("%c", buffer[i]);
					printf(">\n");
				}
			}
		}
		else
		{
			#define BUFFER_SIZE 1024
			char buffer[BUFFER_SIZE];
			size_t bytes_read = 0;
			while((bytes_read = read_from_stacked_stream(&sstrm, buffer, BUFFER_SIZE, &error)) && error == 0)
			{
				printf("<");
				for(size_t i = 0; i < bytes_read; i++)
					printf("%c", buffer[i]);
				printf(">\n");
			}
		}

		close_deinitialize_free_all_from_stacked_stream(&sstrm, READ_STREAMS);

		deinit_dstring(&boundary);

		if(error)
		{
			close_connection = 1;
			goto EXIT_C_1;
		}
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

	// write http response head
	if(HTTP_NO_ERROR != serialize_http_response_head(strm, &hrp))
	{
		close_connection = 1;
		goto EXIT_C_2;
	}

	if(0 > intialize_http_body_and_encoding_streams_for_writing(&sstrm, strm, &(hrp.headers)))
	{
		close_connection = 1;
		goto EXIT_C_2;
	}

	int error = 0;

	write_dstring_to_stream(get_top_of_stacked_stream(&sstrm, WRITE_STREAMS), &get_dstring_pointing_to_literal_cstring("Hello, the form was submitted!!"), &error);
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
	deinit_http_response_head(&hrp);

	EXIT_C_1:;
	deinitialize_stacked_stream(&sstrm);

	//EXIT_C_0:;
	return close_connection;
}