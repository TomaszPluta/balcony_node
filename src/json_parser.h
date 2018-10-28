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




enum tokenType_t {
	tokenString ,
	tokenInt,
};



class token{
	std::string tokenId;
	tokenType_t tokenType;
public:
	token(std::string id, tokenType_t tokenType){		; //add initializer list
		 this->tokenId =id;
		 this->tokenType = tokenType;
	}
	std::string getTokenId(){
		return tokenId;
	}
	tokenType_t getTokenType(){
		return tokenType;
	}
};




class json{
	std::string jsonBuff;
	std::string jsonFormat;
	std::vector<token> tokens;
	//json(string format);
public:
	json(std::vector<token> tokens);
};






#endif /* JSON_PARSER_H_ */
