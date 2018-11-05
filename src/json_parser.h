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

std::string intToString(uint32_t intVal);


class tokenT {
private:
	std::string id;
	std::string strVal;
	std::string content;
	void updateContnent(void){
		this->content = "\"" + this->id + "\"" + ":" + this->strVal;
	}
public:
	tokenT (std::string id, uint32_t uIntVal){
		this->id = id;
		this->strVal = intToString(uIntVal);
		this->updateContnent();
	}
	tokenT (std::string id, std::string stringVal){
		this->id = id;
		this->strVal = stringVal;
		this->content = "\"" + id + "\""  + ":" +   "\"" + stringVal + "\"" ;
	}
	tokenT (std::string id){
		this->id = id;
		this->content = "\"" + id + "\""  + ":";
	}
	void UpdateId(std::string id){
		this->id = id;
		this->updateContnent();
	}
	void updateValue(uint32_t uIntVal){
		this->strVal = intToString(uIntVal);
		this->updateContnent();
	}
	void updateValue(std::string stringVal){
		this->strVal = stringVal;
		this->updateContnent();
	}
};





class json{
	std::string jsonBuff;
	std::vector <std::string> tokens;
	std::string content;
public:
	std::string parse(void){
		this->content = "{";
		for (auto it : tokens){
			this->content += it;
		}
		this->content += "}";
		return this->content;
	}
	void add (std::string newToken){
		tokens.push_back(newToken);
	}
//	json ();
};






#endif /* JSON_PARSER_H_ */
