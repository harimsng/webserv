#ifndef ATOKENIZER_HPP
#define ATOKENIZER_HPP

#include <string>
#include <vector>

class	ATokenizer
{
	ATokenizer(ATokenizer const& tokenizer);
	ATokenizer	&operator=(ATokenizer const& tokenizer);

public:
// constructors & destructor
	ATokenizer();
	~ATokenizer();

// member functions
	virtual std::string const&	peek() = 0;
	virtual std::string const&	get() = 0;
	virtual void				eat(const std::string& target);
	virtual bool				empty() const = 0;

private:
	char				m_buffer[1024];
	unsigned int		m_size;
};

#endif