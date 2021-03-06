/* Comic Sailor - XKCD */
#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "common.h"

char xkcd_baseurl[] = "http://www.xkcd.com/";
char xkcd_license[] = "https://xkcd.com/license.html";

// curl and json helper functions
extern int getcurldata(char *url, struct curl_inputstruct *chunk);
extern int parse_json_int(char *key, char *jsondata);
extern char* parse_json_string(char *key, char *jsondata);

extern char *fillstring(char *ptr, char *beg, int nr, char *end);

// return the url for newest comic - fill in class Selectedcomic_data
int Selectedcomic::xkcd_getcurrent() {
    // http://curl.haxx.se/libcurl/c/getinmemory.html
    struct curl_inputstruct chunk;
    chunk.memory = (char *) malloc(1);
    chunk.size = 0; // no data at this point

    // if 0, this is the first time this function runs and we need to init current
    if (newest == 0) {
        // xkcd api gives the newest here:
        char url[] = "http://xkcd.com/info.0.json";
        current_url = fillstring(current_url, url, (long int)NULL, (char *)NULL);
        // step 1: get the json object for current
        if (getcurldata(current_url, &chunk) == EXIT_FAILURE)
            return EXIT_FAILURE;

        // step 2: parse the json to get num and url attributes (xkcd value for comic nr and url)
        newest = parse_json_int((char *)"num", chunk.memory);
        current = newest;
        }
    else { // no need to init, just get the json
    // create an url of the form: http://xkcd.com/nr/info.0.json
        char url_beg[17] = "http://xkcd.com/";
        char url_end[13] = "/info.0.json";
        char url_current[5] = "";
        char url_full[35] = "";
        sprintf(url_current, "%d", current);
        strncat(url_full, url_beg, strlen(url_beg));
        strncat(url_full, url_current, strlen(url_current));
        strncat(url_full, url_end, strlen(url_end));
//		printf("full url is %s\n", url_full);
        current_url = fillstring(current_url,url_full, (long int)NULL, (char *)NULL);
        // step 1: get the json object for current
        if (getcurldata(current_url, &chunk) == EXIT_FAILURE)
            return EXIT_FAILURE;
        }

    // get image url from the corresponding json key
    // this used to be like this:
    //    current_img = fillstring(current_img, parse_json_string((char *)"img", chunk.memory), (long int) NULL, (char *)NULL);
    // but since fiddling with getcurldata code, the first run always put garbage to the beginning.
    char *ptr = parse_json_string((char *) "img", chunk.memory);
    current_img = (char *) realloc(current_img, strlen(ptr));
    strcpy(current_img, ptr);

    free (chunk.memory);
    if (current_img == NULL)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
    }
