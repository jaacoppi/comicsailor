#ifndef _common_h
#define _common_h
#include <QObject>

typedef enum {XKCD, PEEBLES, DIESEL, SPIKED} comics;
extern comics current_comic;
#define NRCOMICS 4
extern char comic_names[NRCOMICS][40];

// this is the struct where curl loads the output
struct curl_inputstruct {
	char *memory; // actual contents
	size_t size; // size of memory
	};

class Selectedcomic : public QObject {
    Q_OBJECT

	public:
   Selectedcomic(QObject *parent = 0);


        char *current_url; // url to website of current comic
        char *name;


	// stuff interfacing with the QML UI
    Q_INVOKABLE int changecomic(comics comic);
    // dirty hacks due to lack of QML know-how
    Q_INVOKABLE int changecomic_peebles();
    Q_INVOKABLE int changecomic_diesel();
    Q_INVOKABLE int changecomic_xkcd();
    Q_INVOKABLE int changecomic_spiked();
	// UI for browsing
    Q_INVOKABLE int comic_next();
    Q_INVOKABLE int comic_prev();
    Q_INVOKABLE int comic_first();
    Q_INVOKABLE int comic_last();
    Q_INVOKABLE int comic_bynr(int nr);


    // QML access to C++ variables
     // when QML accesses imgurl, C++ invokes get_imgurl()

     Q_PROPERTY(qint32 current READ get_current NOTIFY currentChanged)
     qint32 get_current();
     // qint32 set_current(qint32 number);
     Q_PROPERTY(qint32 newest READ get_newest)
     qint32 get_newest();
     Q_PROPERTY(QString imgurl READ get_imgurl NOTIFY imgurlChanged)
    QString get_imgurl();
    Q_PROPERTY(QString license READ get_license)
    QString get_license();
    Q_PROPERTY(QString homepage READ get_homepage)
    QString get_homepage();

    int newest; // point to the newest published comic
    int current; // point to currently shown comic
	private:

    char *current_img;  // url of current img
    char *homepage;		// for a link to the home page of the comic
    char *license;		// for a link to the license of the comic


	// functions and their pointer
    int (Selectedcomic::*getcurrent)();
	int xkcd_getcurrent();
	int peebleslab_getcurrent();
	int diesel_getcurrent();
	int spiked_getcurrent();

    signals:
    void currentChanged();
    void imgurlChanged();
    };

#endif


