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
#include <array>
#include <cstdlib>
#include <string>

#define MAX_JSON_TOKENS				(6)


std::string intToString(uint32_t intVal);





class tokenT {
private:
	std::string id;
	std::string strVal;
	std::string content;

public:
	tokenT (void){
		this->id.clear();
		this->strVal.clear();
		this->content.clear();
	}
	tokenT (std::string id, uint32_t uIntVal){
		this->id = "\"" + id + "\"";
		this->strVal = intToString(uIntVal);
		this->UpdateContent();
	}
	tokenT (std::string id, std::string stringVal){
		this->id = "\"" + id + "\"";
		this->strVal = "\"" + stringVal + "\"";
		this->UpdateContent();
	}
	tokenT (std::string id){
		this->id = "\"" + id + "\"";
		this->UpdateContent();
	}


	void UpdateId(std::string id);
	void UpdateVal(uint32_t uIntVal);
	void UpdateVal(int32_t IntVal);
	void UpdateVal(std::string stringVal);
	std::string GetId(void);
	std::string GetValue(void);
	std::string GetContent(void);
	void UpdateContent(void);
};






class json{
	std::array <tokenT, MAX_JSON_TOKENS> tokens;
	std::string content;
public:

	json (){
		this ->content.clear();
	}

	std::string parse(void){
		this->content = "{";
		for (auto & it : tokens){
			this->content += it.GetContent() + ",";
		}
		this->content.back() = '}';
		return this->content;
	}

	std::string  update (tokenT tokenNew){
		for (auto & it : tokens){
			if (it.GetId() == tokenNew.GetId()){
				it = tokenNew;
				break;
			}
		}
		return this->parse();
	}

	bool add (tokenT newToken){
		for (auto & it : tokens){
			if (it.GetId().empty()){
				it = newToken;
				return true;
			}
		}
		return false;
	}

	std::string GetContent (){
		return this->content;
	}
};






#endif /* JSON_PARSER_H_ */
