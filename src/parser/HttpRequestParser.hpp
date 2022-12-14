#ifndef HTTPREQUESTPARSER_HPP
#define HTTPREQUESTPARSER_HPP

#include <vector>
#include <map>

#include "parser/AParser.hpp"
#include "tokenizer/HttpStreamTokenizer.hpp"

class	Request;
class	Server;

class	StatusLine;

typedef std::map<std::string, std::vector<std::string> > HeaderFieldsMap;

class	HttpRequestParser
:	public AParser<HttpStreamTokenizer, Request>
{
// deleted
	HttpRequestParser(const HttpRequestParser& parser);
	HttpRequestParser&	operator=(const HttpRequestParser& parser);

// types
public:
	enum	e_readStatus
	{
		REQUEST_LINE = 0,
		HEADER_FIELDS,
		MESSAGE_BODY,
		FINISHED
	};

// constructors & destructor
	HttpRequestParser(std::string& buffer);
	~HttpRequestParser();

// member functions
	virtual void			parse(Request& request);
	std::string::size_type	updateBuffer();

	void	parseStatusLine(Request& request);
	void	parseHeaderFields(HeaderFieldsMap& headerFieldsMap);
	void	parseMessageBody();

	e_readStatus	checkStatusLine(Request& request);

	e_readStatus	getReadStatus() const;

// member variables
private:
	e_readStatus		m_readStatus;
};

#endif
