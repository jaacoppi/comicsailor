#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

// json helpers
int parse_json_int(char *key, char *jsondata);
char* parse_json_string(char *key, char *jsondata);
struct json_object *parse_json(char *key, char *jsondata);
//int parse_json(struct json_object *object);

// from http://www.jroller.com/RickHigh/entry/json_parsing_with_c_simple
int parse_json_int(char *key, char *jsondata) {
	struct json_object *jsonobj;
	jsonobj = parse_json(key, jsondata);
	if (jsonobj == NULL) {
		return -1;
		}

	return json_object_get_int(jsonobj);
	}

	char *parse_json_string(char *key, char *jsondata) {
	struct json_object *jsonobj;
	jsonobj = parse_json(key, jsondata);
	if (jsonobj == NULL) {
		return NULL;
		}
	return (char *)json_object_to_json_string(jsonobj);
	}


struct json_object *parse_json(char *key, char *jsondata) {
	// for debug
	// printf("parse_json looking for %s in JSON string: %s\n\n", search, jsondata);
	struct json_object *jsonobj;
	jsonobj = json_tokener_parse(jsondata);
	
	jsonobj = json_object_object_get(jsonobj,key);
	if (!jsonobj) {
		return NULL;
		}
	// for debug
	//printf("new_obj.to_string()=%s\n", json_object_to_json_string(jsonobj));
	return jsonobj;
	}
