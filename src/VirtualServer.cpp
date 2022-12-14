#include "VirtualServer.hpp"

VirtualServer::VirtualServer()
{
	setToDefault();
}

VirtualServer::~VirtualServer()
{
}

VirtualServer::VirtualServer(VirtualServer const& server)
{
	*this = server;
}

VirtualServer&
VirtualServer::operator=(const VirtualServer& server)
{
	m_index = server.m_index;
	m_serverNames = server.m_serverNames;
	m_errorCode = server.m_errorCode;
	m_root = server.m_root;
	m_errorPages = server.m_errorPages;
	m_listen = server.m_listen;
	m_clientMaxBodySize = server.m_clientMaxBodySize;
	m_uriBufferSize = server.m_uriBufferSize;
	m_locationList = server.m_locationList;
	return *this;
}

#define DEFAULT_NAME ("") // coule be hostname
#define DEFAULT_ADDR (INADDR_ANY)
#define DEFAULT_PORT (8000)
// TODO: fill up default variable list

void
VirtualServer::setToDefault()
{
//	m_index;
	m_serverNames = vector<string>(1, DEFAULT_NAME);
//	m_errorCode;
//	m_root;
//	m_errorPages;
	m_listen = GET_SOCKADDR_IN(DEFAULT_ADDR, DEFAULT_PORT);
	m_clientMaxBodySize = 1 << 13; // 8kb
//	m_uriBufferSize;
//
	m_addrKey = (DEFAULT_ADDR << 16) + DEFAULT_PORT;
}

std::ostream&
operator<<(std::ostream& os, const VirtualServer& server)
{
	uint32_t	addr = ntohl(server.m_listen.sin_addr.s_addr);

	os << "server\n{\n";
	os << "\tserver_name    ";
	for (size_t i = 0; i < server.m_serverNames.size(); ++i)
		os << server.m_serverNames[i] << ' ';
	os << '\n';
	os << "\tlisten " << ((addr & 0xff000000) >> 24) << '.'
	   << ((addr & 0xff0000) >> 16) << '.'
	   << ((addr & 0xff00) >> 8) << '.'
	   << (addr & 0xff) << ':'
	   << ntohs(server.m_listen.sin_port) << '\n';
	os << "\tindex " << server.m_index << '\n';
	os << "\tclient_max_body_size " << server.m_clientMaxBodySize << '\n';
	for (uint32_t i = 0; i < server.m_locationList.size(); ++i)
		os << server.m_locationList[i];
	os << "}\n";
	return os;
}
