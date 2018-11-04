/*
 * json_parser.cpp
 *
 *  Created on: 28.10.2018
 *      Author: tomek
 */




#include "json_parser.h"
using namespace std;




typedef struct{
	char* id;
	uint8_t temp;
	uint16_t press;
	uint16_t light;
	uint16_t hum;
}nodeResult_t;



//json::json(vector<class token> tokens){
//	Format.append("{");
//	for (auto it  = tokens.begin(); it != tokens.end(); it++){
//		Format.append("\"");
//		Format.append((*it).getTokenId());
//		Format.append("\":");
//		if ((*it).getTokenType() == tokenString){
//			Format.append("%s");
//		}else {
//			Format.append("%d");
//		}
//		zrobic sprintfy dla poszczegolnych tokenow i tutaj je tylko laczyc.
//	}
//	Format.append("}");
//
//	Buff.append(snprintf(Format, 10,    );
//}




//myObj = { "id":"balcony", "temp":30, "press":1024, "light":500, "hum":60,};

void funct (string name, uint8_t size){
	//token_t token(name, size);
	string format =  "\"id\":%s\",\"temp\": %d,\"press\":%d,\"light\":%d,\"hum\"%d";

    // Create a vector containing integers
    std::vector<int> v = {7, 5, 16, 8};

    // Add two more integers to vector
    v.push_back(25);
    v.push_back(13);


}


/*
 *
myObj = { "id":"balcony", "temp":30, "press":1024, "light":500, "hum":60,};


myObj = { "name":"John", "age":30, "car":null };
x = myObj["name"];



myObj = {
    "name":"John",
    "age":30,
    "cars": {
        "car1":"Ford",
        "car2":"BMW",
        "car3":"Fiat"
    }
 }
*/
