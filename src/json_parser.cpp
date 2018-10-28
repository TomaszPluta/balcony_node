/*
 * json_parser.cpp
 *
 *  Created on: 28.10.2018
 *      Author: tomek
 */


#include <vector>
#include <string>

using namespace std;

class token{
	string tokenId;
	uint8_t tokenSize;
	token(string name, uint8_t size);
};


class json{
	string jsonBuff;
	string jsonFormat;
	vector<token> tokens;
	json(string format);
};


typedef struct{
	char* id;
	uint8_t temp;
	uint16_t press;
	uint16_t light;
	uint16_t hum;
}nodeResult_t;


//string format =  "\"id\ : ":,temp,press,light,hum";

//myObj = { "id":"balcony", "temp":30, "press":1024, "light":500, "hum":60,};

void funct (string name, uint8_t size){
	//token_t token(name, size);


    // Create a vector containing integers
    std::vector<int> v = {7, 5, 16, 8};

    // Add two more integers to vector
    v.push_back(25);
    v.push_back(13);


}


/*
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
