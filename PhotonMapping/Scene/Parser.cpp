#include "Parser.h"



regex Parser::fileRegex=regex(".+\\.\\w+");   //¾²Ì¬³ÉÔ±³õÊ¼»¯
/*  .Æ¥Åä×Ö·û£¬\\.Æ¥Åä. \\wÆ¥Åä×ÖÄ¸Êı×ÖÏÂ»®Ïß*/

Token Parser::GetNextToken()
{
	while (toParse[index] == '\n' || toParse[index] == '\t' || toParse[index] == ' ')
		++index;
	if (index == toParse.size())
	{
		return Token(-1, "END");
	}
	Token ret;
	if (isalpha(toParse[index]))
	{
		while (index < toParse.size() && isalpha(toParse[index]))
		{
			ret.value += toParse[index];
			++index;
		}
		return ret;
	}
	if (toParse[index] == '-')
	{
		ret.value = "-";
		++index;
	}
	if (isdigit(toParse[index]))
	{
		while (index < toParse.size() && isdigit(toParse[index]))
		{
			ret.value += toParse[index];
			++index;
		}
		if (index < toParse.size() && toParse[index] == '.')
		{
			++index;
			ret.value += '.';
			bool legal = false;
			while (index < toParse.size() && isdigit(toParse[index]))
			{
				legal = true;
				ret.value += toParse[index];
				++index;
			}
			if (!legal)
			{
				ret.tag = -1;
				return ret;
			}
		}
		return ret;
	}
	if (toParse[index] == '=')
	{
		ret.value = "=";
		++index;
		return ret;
	}
	return ret;
}
void Parser::Move()
{
	currentToken = GetNextToken();
}
bool Parser::Match(int _tag)
{
	if (currentToken.tag == _tag)
	{
		Move();
		return true;
	}
	throw exception("syntax error!");
	return false;
}
bool Parser::Match(const string& pattern)
{
	if (currentToken.value == pattern)
	{
		Move();
		return true;
	}
	return false;
}


Vector3 Parser::vec3()
{
	Vector3 ret;
	ret.x = stof(currentToken.value);
	Move();
	ret.y = stof(currentToken.value);
	Move();
	ret.z = stof(currentToken.value);
	Move();
	return ret;
}

shared_ptr<Scene> Parser::scene()
{
	shared_ptr<Scene> mainScene(new Scene());
	Move();
	mainScene->SetCamera(camera());
	while (!Finished())
	{
		if (currentToken.value == "AreaLight" || currentToken.value == "PointLight")
			mainScene->AddLight(light());
		else if (currentToken.value == "Sphere" || currentToken.value == "Plane" || currentToken.value == "Mesh")
			mainScene->AddObject(primitive());
	}
	return mainScene;
}

shared_ptr<Camera> Parser::camera()
{
	Match("camera");
	shared_ptr<Camera> ret(new Camera());
	Match("EyePosition");
	Match("=");
	ret->SetEyePosition(vec3());
	Match("LookAt");
	Match("=");
	ret->SetLookAt(vec3());
	

	
	Match("LensWidth");
	Match("=");
	ret->SetLensW(stof(currentToken.value));
	Move();

	Match("LensHeight");
	Match("=");
	ret->SetLensH(stof(currentToken.value));
	Move();
	
	if (currentToken.value=="OutFileName")
	{
		Move();
		Match("=");
		bool isFile= regex_match(currentToken.value, Parser::fileRegex);
		if (isFile)
			ret->SetOutFile(currentToken.value);
		else
			ret->SetOutFile("result.bmp");
		Move();
	}
	
	return shared_ptr<Camera>(new Camera());
}
shared_ptr<Light> Parser::light()
{
	if (currentToken.value == "AreaLight")
	{
		return arealgiht();
	}
	else if (currentToken.value == "PointLight")
		return nullptr;
	return nullptr;
}

shared_ptr<AreaLight> Parser::arealgiht()
{
	shared_ptr<AreaLight> ret(new AreaLight());
	Match("AreaLight");
	Match("center");
	Match("=");
	ret->SetCenter(vec3());
	Match("dx");
	Match("=");
	ret->SetDx(vec3());
	Match("dy");
	Match("=");
	ret->SetDy(vec3());
	
	Match("color");
	Match("=");
	ret->SetColor(vec3());
	return ret;
}

shared_ptr<Primitive> Parser::primitive()
{
	if (currentToken.value == "Sphere")
		return sphere();
	else if (currentToken.value == "Plane")
		return plane();
	else if (currentToken.value == "Mesh")
	{
		//TODO;
	}
	return nullptr;
}

Material  Parser::material()
{
	Material ret;
	Match("color");
	Match("=");
	ret.color = vec3();

	Match("diff");
	Match("=");
	ret.diff = stof(currentToken.value);
	Move();

	Match("refl");
	Match("=");
	ret.refl = stof(currentToken.value);
	Move();
	Match("refr");
	Match("=");
	ret.refr = stof(currentToken.value);
	Move();

	if (ret.refr > EPS)
	{
		Match("rindex");
		Match("=");
		ret.rindex = stof(currentToken.value);
		Move();
	}
	/*if (currentToken.value == "texture")
	{
		Move();
		Match("=");
		ret.texture=make_shared<Bmp>(new Bmp());
		ret.texture->Input(currentToken.value);
	}*/
	return ret;
}

shared_ptr<Sphere> Parser::sphere()
{
	shared_ptr<Sphere> ret(new Sphere());
	Match("Sphere");
	Match("center");
	Match("=");
	ret->SetCenter(vec3());
	Match("R");
	Match("=");
	ret->SetRadius(stof(currentToken.value));
	Move();
	ret->SetMaterial(material());
	return ret;
}


shared_ptr<Plane> Parser::plane()
{
	shared_ptr<Plane> ret(new Plane());
	Match("Plane");
	Match("center");
	Match("=");
	ret->center = vec3();
	Match("normal");
	Match("=");
	ret->normal = vec3();
	Match("HalfLength");
	Match("=");
	ret->SetHL(stof(currentToken.value));
	Move();
	Match("HalfWidth");
	Match("=");
	ret->SetHW(stof(currentToken.value));
	Move();
	ret->SetMaterial(material());
	return ret;
}
