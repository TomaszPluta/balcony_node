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




tokenT::tokenT (std::string id, uint32_t uIntVal){
	this->id = id;
	this->strVal = intToString(uIntVal);
	this->updateContnent();
}
tokenT::tokenT (std::string id, std::string stringVal){
	this->id = id;
	this->strVal = stringVal;
	this->content = "\"" + id + "\""  + ":" +   "\"" + stringVal + "\"" ;
}
tokenT::tokenT (std::string id){
	this->id = id;
	this->content = "\"" + id + "\""  + ":";
}
tokenT::tokenT (void){
	this->id.clear();
	this->strVal.clear();
	this->content.clear();
}
void tokenT::UpdateId(std::string id){
	this->id = id;
	this->updateContnent();
}
void tokenT::UpdateContent(uint32_t uIntVal){
	this->strVal = intToString(uIntVal);
	this->updateContnent();
}
void tokenT::UpdateContent(std::string stringVal){
	this->strVal = stringVal;
	this->updateContnent();
}
std::string tokenT::GetId(void){
	return this->content;
}
std::string tokenT::GetContent(void){
	return this->content;
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
