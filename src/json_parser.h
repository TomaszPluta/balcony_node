/*
 * json_parser.h
 *
 *  Created on: 28.10.2018
 *      Author: tomek
 */

#ifndef JSON_PARSER_H_
#define JSON_PARSER_H_

#include <vector>
#include <string>
#include <sstream>




template <class T>
class tokenT {
	std::string id;
	T Val;
	std::string pair;
public:
	tokenT (std::string id, uint32_t uIntVal){
		this->id = id;
		this->Val = uIntVal;
		const uint8_t intSize = 8;
		char stringVal[intSize];
		snprintf(stringVal, intSize, "%d", this->Val );
		this->pair = "\"" + id + "\"" + ":" + stringVal;
	}
	tokenT (std::string id, std::string stringVal){
		this->id = id;
		this->Val = stringVal;
		this->pair = "\"" + id + "\""  + ":" +   "\"" + stringVal + "\"" ;
	}
	void actualizeId(std::string id){
		this->id = id;
	}
	void updateValue(uint32_t uIntVal){
		this->Val = uIntVal;
	}
	void updateValue(std::string stringVal){
		this->Val = stringVal;
	}
	void updateString(void){
		;
	}
};





class json{
	std::string jsonBuff;
	std::vector <std::string> tokensStrings;
public:
	void parse(void);
};






#endif /* JSON_PARSER_H_ */
