/* Comic Sailor - Diesel Sweeties */
#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

char diesel_baseurl[] = "http://www.dieselsweeties.com/";
char diesel_license[] = "https://creativecommons.org/licenses/by-nc/2.5/";
char diesel_archiveurl[100] = "http://www.dieselsweeties.com/archive/";
// curl  helper functions
extern int getcurldata(char *url, struct curl_inputstruct *chunk);

extern char *fillstring(char *ptr, char *beg, int nr, char *end);



// return the url for newest comic - fill in struct Selectedcomic_data
int Selectedcomic::diesel_getcurrent() {
    char tempstr[100] = "";
	char *ptr;

	// http://curl.haxx.se/libcurl/c/getinmemory.html
	struct curl_inputstruct chunk;
	chunk.memory = (char *) malloc(1);
	chunk.size = 0; // no data at this point

	// step 0: get the front page
	// if 0, this is the first time this function runs and we need to init current
	if (newest == 0) {
	        // diesel api gives the newest here:
		// get the front page
            if (getcurldata(diesel_baseurl, &chunk) == EXIT_FAILURE)
                    return EXIT_FAILURE;
		// in dieselsweeties, the source looks like this:
		// <a href="/archive/3748"><img src="/hstrips/0/3/7/4/03749.png"
		// get the number of newest
		ptr = strstr(chunk.memory, "/archive/");
		ptr = ptr + 9;
		int i;
		for (i = 0; i < 6; i++)	{
			// until .png
			if (*ptr >= 48 && *ptr <= 57) {
				tempstr[i] = *ptr;
				}
			else {// not a number, exit
				tempstr[i] = '\0';
				break;
				}
			ptr++;
			}
		newest = atoi(tempstr);
		current = newest;
		// get newest url
		current_url = fillstring(current_url, diesel_archiveurl, newest, NULL);
		}
	else // get current url by #id, not from startpage (init)
		{
		// get current url
		current_url = fillstring(current_url, diesel_archiveurl, current, NULL);
		// get current page
            if (getcurldata(current_url, &chunk) == EXIT_FAILURE)
                return EXIT_FAILURE;
		// we need to reload the correct page
		}

	// get current img
	ptr = strstr(chunk.memory, "hstrips/");
    unsigned int i;
    for (i = 0; i < sizeof(tempstr); i++)	{
		// it's a number
        if (*ptr != '"' ) {
			tempstr[i] = *ptr;
			}
		else { // found the .png ending, finish
            tempstr[i] = '\0';
			break;
			}
		ptr++;
		}

	current_img = fillstring(current_img, diesel_baseurl, (long int) NULL, NULL);
	current_img = (char *) realloc(current_img, strlen(current_img) + strlen(tempstr) +1);
	strncat(current_img, tempstr, strlen(tempstr));
	free (chunk.memory);
    return EXIT_SUCCESS;
}
