#pragma once
#include "scene.h"
#include <ctype.h>
#include <string>
#include <memory>
#include <regex>
using  namespace std;
struct Token
{
	int tag;
	string value;
	Token(int _tag = 0, string _value = "") :tag(_tag), value(_value) {}
	string ToString() { return "tag: " + to_string(tag) + ",value: " + value; }
};
class Parser
{
private:
	Token currentToken;
	string toParse;
	int index;
public:
	Parser() { index = 0; }
	Parser(const string &str) { toParse = str; index = 0; }
	Parser(string && rval) { toParse = std::move(rval); index = 0; }
	Parser(const  Parser& rhs) = delete;
	Parser& operator=(const Parser& rhs) = delete;
	~Parser() {}
	Token GetNextToken();
	Token GetCurToken() { return currentToken; }
	void  Move();
	bool Match(const string& pattern);
	bool Match(int _tag);
	bool Finished() { return index == toParse.size(); }
	bool isFilePathChar(char ch) { return ch == '.'|| ch == '\\' || ch == ':' || isalnum(ch); }
	static std::regex fileRegex;
	
	shared_ptr<Scene> scene(); //Scene-> camera{light|primitive}*;
	Vector3 vec3();
	shared_ptr<Camera> camera(); //camera->....
	shared_ptr<Light> light();   //light->AreaLight|PointLight
	shared_ptr<AreaLight> arealgiht();  //arealight->"AreaLight" "dx" "=" vec3 "dy" "=" vec3 "color" "=" vec3
	shared_ptr<Primitive> primitive();  //primitive->sphere|plane|mesh
	shared_ptr<Sphere>   sphere();
	Material             material();
	shared_ptr<Plane>    plane();
	void mesh();//TODO
};