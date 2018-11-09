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


#define MAX_JSON_TOKENS				(4)


std::string intToString(uint32_t intVal);





class tokenT {
private:
	std::string id;
	std::string strVal;
	std::string content;
	void updateContnent(void){}
public:
	tokenT (void);
	tokenT (std::string id, uint32_t uIntVal);
	tokenT (std::string id, std::string stringVal);
	void UpdateId(std::string id);
	void UpdateContent(uint32_t uIntVal);
	void UpdateContent(std::string stringVal);
	std::string GetId(void);
	std::string GetContent(void);
};






class json{
	std::array <tokenT, MAX_JSON_TOKENS> tokens;
	std::string content;
public:

	std::string parse(void){
		this->content = "{";
		for (auto & it : tokens){
			this->content += it.GetContent();
		}
		this->content += "}";
		return this->content;
	}

	std::string  update (tokenT token){
		for (auto & it : tokens){
			if (it.GetId() == token.GetId()){
				it.UpdateContent(token.GetContent());
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
	json (){
		this ->content.clear();
	}
};






#endif /* JSON_PARSER_H_ */
