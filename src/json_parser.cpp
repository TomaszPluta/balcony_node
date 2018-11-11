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


std::string intToString(uint32_t intVal){
	/*due to not available "to_string()" c++11 func*/
	const uint8_t intSize = 8;
	char charVal[intSize];
	snprintf(charVal, intSize, "%u", intVal);
	std::string strVal(charVal);
	return strVal;
}


std::string intToString(int32_t intVal){
	/*due to not available "to_string()" c++11 func*/
	const uint8_t intSize = 8;
	char charVal[intSize];
	snprintf(charVal, intSize, "%d", intVal);
	std::string strVal(charVal);
	return strVal;
}





void tokenT::UpdateId(std::string id){
	this->id = id;
	this->content = "\"" + id + "\""  + ":";
}
void tokenT::UpdateVal(uint32_t uIntVal){
	this->strVal = intToString(uIntVal);
	this->content = "\"" + this->id + "\""  + ":" +  this->strVal;
}
void tokenT::UpdateVal(int32_t IntVal){
	this->strVal = intToString(IntVal);
	this->content = "\"" + this->id + "\""  + ":" +  this->strVal;
}
void tokenT::UpdateVal(std::string stringVal){
	this->strVal = stringVal;
	this->content = "\"" + this->id + "\""  + ":" +   "\"" + this->strVal + "\"" ;
}
std::string tokenT::GetId(void){
	return this->content;
}
std::string tokenT::GetContent(void){
	return this->content;
}


void tokenT::UpdateContnent(){
	this->content = "\"" + id + "\""  + ":" +   "\"" + stringVal + "\"" ;
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
