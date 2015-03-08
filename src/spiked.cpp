/* Comic Sailor - Spiked Math */
#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

char spiked_baseurl[] = "http://www.spikedmath.com/";
char spiked_license[] = "http://creativecommons.org/licenses/by-nc-sa/2.5/ca/";
// curl  helper functions
extern int getcurldata(char *url, struct curl_inputstruct *chunk);

extern char *fillstring(char *ptr, char *beg, int nr, char *end);


// return the url for newest comic - fill in struct Selectedcomic_data
int Selectedcomic::spiked_getcurrent() {
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
	        getcurldata(spiked_baseurl, &chunk);
		// in dieselsweeties, the source looks like this:
		// <h1 id="page-title" class="asset-name entry-title">573</h1>"
		// get the number of newest
		ptr = strstr(chunk.memory, "entry-title");
		ptr = ptr + 13;
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
		current_url = fillstring(current_url, spiked_baseurl, newest, (char *) ".html");
		}
	else // get current url by #id, not from startpage (init)
		{
		// get current url
		if (current < 100) { // special case with Spiked Math urls: "099.html" instead of "99.html"
			current_url = fillstring(current_url, spiked_baseurl, (long int) NULL, (char *)NULL);
			current_url = (char *) realloc(current_url, strlen(current_url) + strlen(tempstr) + 20);
			strcat(current_url, "0");
			char nr[5];
			sprintf(nr, "%d", current);
			strcat(current_url, nr);
			strcat(current_url, ".html");
			}
		else {
			current_url = fillstring(current_url, spiked_baseurl, current, (char *) ".html");
		}
		// get current page
	        getcurldata(current_url, &chunk);
		// we need to reload the correct page
		}
	// get current img
	ptr = strstr(chunk.memory, "http://spikedmath.com/comics/");
	ptr=ptr+29;
	int i;
	for (i = 0; i < 40; i++)	{
		// it's a number
		if (*ptr != 'g' ) {
			tempstr[i] = *ptr;
			}
		else { // found the .png ending, finish
			tempstr[i] = 'g';
			tempstr[i+1] = '\0';
			break;
			}
		ptr++;
		}

	current_img = fillstring(current_img, spiked_baseurl, (long int) NULL, NULL);
	current_img = (char *) realloc(current_img, strlen(current_img) + strlen(tempstr) + 5);
	strcat(current_img, tempstr);
	strcat(current_img, ".png");
	free (chunk.memory);
    return 1;
    }
