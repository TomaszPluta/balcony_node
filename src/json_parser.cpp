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

/* valid json examples
{
   "name":"John",
   "age":30,
   "cars":{
      "id":"balcony",
      "temp":30,
      "press":1024,
      "light":500,
      "hum":60
   }
}


{"id":"balcony", "temp":30, "press":1024, "light":500, "hum":60}
*/


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
