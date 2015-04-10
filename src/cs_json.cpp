#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QJsonObject>
#include <QtCore>

// QtCore implementation draws from http://doc.qt.io/qt-5/json.html and
// https://gist.github.com/cckwes/6435552

// json helpers
int parse_json_int(char *key, char *jsondata);
char* parse_json_string(char *key, char *jsondata);
QJsonObject json_convert(char *jsondata);

int parse_json_int(char *key, char *jsondata) {
    QJsonObject jsonobj = json_convert(jsondata);
	return jsonobj[key].toInt();
	}

char *parse_json_string(char *key, char *jsondata) {
    QJsonObject jsonobj = json_convert(jsondata);
    // spaghetti code for returning a char* from jsonobj(key)
    QString str1 = jsonobj[key].toString();
    QByteArray ba = str1.toLocal8Bit();
    return ba.data();
    }

// this function is needed because the rest of Comic Sailor code is C instead of Qt.
// it converts char* to QJsonObject
QJsonObject json_convert(char *jsondata) {
    QByteArray bytearray;
    bytearray.append((QString) jsondata);
    QJsonDocument doc = QJsonDocument::fromJson(bytearray);
    // TODO: error checking, doc.isNull(), doc.isEmpty etc etc
    QJsonObject jsonobj = doc.object();
    return jsonobj;
    }
