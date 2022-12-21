#include <sys/stat.h>

#include <sstream>
#include <iostream>

#include "tokenizer/FileTokenizer.hpp"
#include "exception/ConfigParserException.hpp"
#include "parser/ServerParser.hpp"
#include "parser/LocationParser.hpp"
#include "parser/ConfigParser.hpp"

using namespace std;

// constructors & destructor
ConfigParser::ConfigParser()
{
}

ConfigParser::~ConfigParser()
{
}

void
ConfigParser::init(string configPath)
{
	ServerParser::setServerSetterMap();
	LocationParser::setLocationSetterMap();

	if (checkFileStat(configPath.data()) == false)
		throw ConfigParserException("invalid file type");
			
	if (configPath.rfind(".conf") != configPath.size() - 5)
		throw ConfigParserException("invalid filename");

	m_tokenizer.init(configPath);
}

bool
ConfigParser::checkFileStat(const char* path)
{
	struct stat	buffer;

	if (stat(path, &buffer) == -1)
		throw ConfigParserException("file doesn't exist");
	return (buffer.st_mode & S_IFREG) == S_IFREG;
}

void
ConfigParser::parse(vector<Server>& servers) try
{
	while (m_tokenizer.peek() == "server")
	{
		m_tokenizer.get();
		parseServer(servers);
	}
	if (m_tokenizer.empty() == false)
		m_tokenizer.eat("server");
}
catch (std::exception& e)
{
	cout << m_tokenizer.getErrorLog(e.what());
}

void
ConfigParser::parseServer(vector<Server>& servers)
{
	m_tokenizer.eat("{");
	
	ServerParser	serverParser(m_tokenizer);

	servers.push_back(Server());
	serverParser.parse(servers.back());
	m_tokenizer.eat("}");
}

int
ConfigParser::toInt(const string& str)
{
	stringstream	ss(str);
	int				num = 0;

	ss >> num;
	return num;
}

string
ConfigParser::toString(int num)
{
	string	str;
	int		denom = 1000000000;
	
	while (denom > 0 && num / denom == 0)
		denom /= 10;
	while (denom > 0)
	{
		str.push_back(num / denom + '0');
		num %= denom;
		denom /= 10;
	}
	return str;
}