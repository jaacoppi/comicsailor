/* Comic Sailor - Peebles Lab */
#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


char peebles_baseurl[] = "http://www.peebleslab.com/";
char peebles_license[] = "http://creativecommons.org/licenses/by-nc-sa/3.0/us/";

// helper functions
extern char *fillstring(char *ptr, char *beg, int nr, char *end);

// return the url for newest comic - fill in struct Selectedcomic_data
int Selectedcomic::peebleslab_getcurrent() {

    // for init

    if (newest == 0) {
        // step 0: DON'T CHECK FOR CURRENT.
        // Peebleslab probably won't update anymore, the latest is #100 from Jan 17th, 2011.
        // We could parse the website source for "Latest" to be sure. We won't.
        newest = 100;
        current = 100;
        char img[] = "http://www.peebleslab.com/comics/100.png\0";
        current_url = fillstring(current_url, peebles_baseurl, (long int) NULL, (char *) NULL);
        current_img = fillstring(current_img, img, (long int) NULL, (char *) NULL);

        // we could do this, but it's not needed since we do a static init
        //peebleslab_changecurrent(data, newest);
        }
	else {
        current_url = fillstring(current_url, peebles_baseurl, current, (char *)NULL);
        }

    // current_img
	// create an url of the form: http://peebleslab.com/nr.png
    char img_beg[] = "http://www.peebleslab.com/comics/";
    char img_end[] = ".png";
    fillstring(current_img, img_beg, current, img_end);
    return 1;
    }
