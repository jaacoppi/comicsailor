#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include <QObject>
#include <ctime>

char comic_names[NRCOMICS][40] = { "XKCD", "Peebles Lab", "Diesel Sweeties", "Spiked Math"};
class Selectedcomic comic_data[NRCOMICS];

// constructor - connect with QML
Selectedcomic::Selectedcomic(QObject *parent) : QObject (parent) {
    return;
    }


// For comics - all must  have a getcurrent()
// getcurrent also gets newest if newest is set to 0
extern char xkcd_baseurl[];
extern char xkcd_license[];
extern char peebles_baseurl[];
extern char peebles_license[];
extern char diesel_baseurl[];
extern char diesel_license[];
extern char spiked_baseurl[];
extern char spiked_license[];

char *fillstring(char *ptr, char *beg, int nr, char *end);

// this changes function pointers so the currently shown comic can use them
// note that different comics can keep their own pointer data intact so we
// avoid the cost of init every time a user switches between them
int Selectedcomic::changecomic(QString comic) {
    if (comic == "XKCD") {
            getcurrent = &Selectedcomic::xkcd_getcurrent;
            homepage = xkcd_baseurl;
            license = xkcd_license;
            }
    if (comic == "PEEBLES") {
            getcurrent = &Selectedcomic::peebleslab_getcurrent;
            homepage = peebles_baseurl;
            license = peebles_license;
            }
    if (comic == "DIESEL") {
            getcurrent = &Selectedcomic::diesel_getcurrent;
            homepage = diesel_baseurl;
            license = diesel_license;
			}
    if (comic == "SPIKED") {
            getcurrent = &Selectedcomic::spiked_getcurrent;
            homepage = spiked_baseurl;
            license = spiked_license;
			}


    this->newest = 0;
    this->current = 0;
    this->current_url = NULL;
    this->current_img = NULL;

    // load newest
   if ((this->*getcurrent)() == EXIT_FAILURE) {
        this->current = 0;
        this->current_img = NULL;
        }


        emit currentChanged();
        emit imgurlChanged();

    return EXIT_SUCCESS;
	}


int Selectedcomic::comic_random() {
	srand(time(NULL));
	current = 1 + rand() % newest; // rnd between 1 and newest
    (this->*getcurrent)();
    emit currentChanged();
    emit imgurlChanged();
    return -1;
	}

int Selectedcomic::comic_next() {
	if (current != newest)
		{
		current++;
        (this->*getcurrent)();
        emit currentChanged();
        emit imgurlChanged();
		}
	return -1;
	}

int Selectedcomic::comic_prev() {
	if (current > 1)
		{
		current--;
        (this->*getcurrent)();
        emit currentChanged();
        emit imgurlChanged();
		}
	return -1;
	}

int Selectedcomic::comic_first() {
	if (current > 1)
		{
		current = 1;
        (this->*getcurrent)();
        emit currentChanged();
        emit imgurlChanged();
		}
	return -1;
	}

int Selectedcomic::comic_last() {
	if (current != newest)
		{
		current = newest;
        (this->*getcurrent)();
        emit currentChanged();
        emit imgurlChanged();
		}
	return -1;
	}

int Selectedcomic::comic_bynr(int nr) {
        current = nr;
      return (this->*getcurrent)();
        }



// get the image from url in current_url
QString Selectedcomic::get_imgurl() {
    return (QString) current_img;
    }

QString Selectedcomic::get_license() {
    return (QString) license;
    }


QString Selectedcomic::get_homepage() {
    return (QString) homepage;
    }

qint32 Selectedcomic::get_current() {
    return (qint32) current;
    }


qint32 Selectedcomic::get_newest() {
    return (qint32) newest;
    }


// used quite a few times for setting comic->current_url and current_img
char *fillstring(char *ptr, char *beg, int nr, char *end) {
    /* three use cases:
	ptr, beg, NULL, NULL 	-> only set a string
	ptr, beg, nr, NULL	-> combine a string and a number
	ptr, beg, nr, end	-> combine a string, a number and a string
	*/
	if (nr == (long int)  NULL && end == NULL) {
		int len = strlen(beg);
		ptr = (char *) realloc(ptr, len +1);
		ptr = (char *) memset(ptr, 0, len +1 );
        memcpy(ptr, beg, len );
		return ptr;
	 	}
	if (nr != (long int)NULL && end == NULL) {
		char nr_str[10] = "";
		sprintf(nr_str, "%d", nr);
		int len = strlen(beg) + strlen(nr_str);
		ptr = (char *) realloc(ptr, len +1 );
		ptr = (char *) memset(ptr, 0, len +1 );
		strcpy(ptr, beg);
		strcat(ptr, nr_str);
		return ptr;
	 	}
	else {
		char nr_str[10] = "";
		sprintf(nr_str, "%d", nr);
		int len = strlen(beg) + strlen(nr_str) + strlen(end);
		ptr = (char *) realloc(ptr, len +1 );
		ptr = (char *) memset(ptr, 0, len +1 );
		strcpy(ptr, beg);
		strcat(ptr, nr_str);
		strcat(ptr, end);
		return ptr;
		}
return ptr;
}

