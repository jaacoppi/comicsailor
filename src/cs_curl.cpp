#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

// curl helper functions
size_t curlwriter(char *data, size_t size, size_t nmemb, void *writerdata);
int getcurldata(char *url, struct curl_inputstruct *chunk);

char *errorbuffer = NULL;

// get data from url. No comic specific code!
int getcurldata(char *url, struct curl_inputstruct *chunk) {
	CURL *connection = NULL;
	CURLcode retcode;
	connection = curl_easy_init();

	if (connection == NULL) {
		printf("Error initializing CURL\n");
		exit(EXIT_FAILURE);
		}

	retcode = curl_easy_setopt(connection, CURLOPT_URL, url);
	if (retcode != CURLE_OK) {
		printf("Error setting CURL URL to %s\n", url);
		exit(EXIT_FAILURE);
		}

	retcode = curl_easy_setopt(connection,CURLOPT_ERRORBUFFER, &errorbuffer);
	if (retcode != CURLE_OK) {
		printf("Error setting CURL URL to %s\n", url);
		exit(EXIT_FAILURE);
		}

	retcode = curl_easy_setopt(connection, CURLOPT_WRITEFUNCTION, curlwriter);
	if (retcode != CURLE_OK) {
		printf("Error setting curlwriter callback function\n");
		exit(EXIT_FAILURE);
		}

	retcode = curl_easy_setopt(connection, CURLOPT_WRITEDATA, (void *)chunk);
	if (retcode != CURLE_OK) {
		printf("Error setting curl writedata\n");
		exit(EXIT_FAILURE);
		}

	retcode = curl_easy_perform(connection);
	if (retcode != CURLE_OK) {
		printf("Error performing curl: ERR #%d, %s\n", retcode, errorbuffer);
		printf("URL was: %s\n", url);
		exit(EXIT_FAILURE);
		}

	//printf("got content in getcurldata:\n%s\n", chunk->memory);
	curl_easy_cleanup(connection);
	return 1;
	}

// from http://curl.haxx.se/libcurl/c/getinmemory.html 
// curlwriter gets writerdata and puts it to curl_inputstruct mem
size_t curlwriter(char *data, size_t size, size_t nmemb, void *writerdata) {
	if (writerdata == NULL)
		return 0;

	size_t realsize = size * nmemb;
	struct curl_inputstruct *mem = (struct curl_inputstruct *)writerdata;
	mem->memory = (char *)realloc(mem->memory, (mem->size + realsize + 1));

	if(mem->memory == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
		}

	memcpy(&(mem->memory[mem->size]), data, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	// if this is not done, curl_easy_perform() fails
	return realsize;
	}
