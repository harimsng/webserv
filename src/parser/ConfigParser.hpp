#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <string>
#include <vector>

#include "Webserv.hpp"
#include "parser/AParser.hpp"
#include "tokenizer/FileTokenizer.hpp"
#include "Server.hpp"

class	ConfigParser: public AParser<FileTokenizer, void>
{
// deleted
	ConfigParser(ConfigParser const& configParser);
	ConfigParser	&operator=(ConfigParser const& configParser);

public:
	class	ConfigParserException;

// constructors & destructor
	ConfigParser();
	virtual ~ConfigParser();

// member functions
	void			init(std::string configPath, VirtualServerTable& serverTable);
	bool			checkFileStat(const char* path);

	virtual void	parse();
	void			parseServer() throw(std::string);

private:
	void	checkDuplicateServerName(const Server& server) const;
	void	addNameToTable(Server& server);

	VirtualServerTable*	m_serverTable;
};

#endif
