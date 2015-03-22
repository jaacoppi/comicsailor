/* Comic Sailor - Peebles Lab */
#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


char peebles_baseurl[] = "http://www.peebleslab.com/";
char peebles_license[] = "http://creativecommons.org/licenses/by-nc-sa/3.0/us/";
char peebles_archiveurl[] = "http://www.peebleslab.com/comics/";

// helper functions
extern char *fillstring(char *ptr, char *beg, int nr, char *end);

// return the url for newest comic - fill in struct Selectedcomic_data
int Selectedcomic::peebleslab_getcurrent() {
    // step 0: DON'T CHECK FOR CURRENT.
    // Peebleslab probably won't update anymore, the latest is #100 from Jan 17th, 2011.
    // We could parse the website source for "Latest" to be sure. We won't.
    if (newest == 0) {
    newest = 100;
    current = 100;
    }
    current_url = fillstring(current_url, peebles_baseurl, (long int) NULL, (char *) NULL);
    current_img = fillstring(current_img, peebles_archiveurl, (long int) current, (char *) ".png");

    return 1;
    }
