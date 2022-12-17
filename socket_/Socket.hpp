#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <unistd.h>

#include "SocketTypes.hpp"

template <typename SocketType>
class	Socket
{
// types
	typedef typename SocketType::socketAddr	socketAddr;

// deleted
	Socket	&operator=(Socket const& socket) {(void)socket; return *this;}

public:
// constructors & destructor
	Socket() throw();
	~Socket() throw();
	Socket(Socket const& socket) throw();
	Socket(int fd) throw();

// member functions
	int	listen(int backlog = 16) throw();
	int	bind(socketAddr* raddr) throw();
	int	accept(socketAddr* addr) throw();
	int	connect(socketAddr* addr) throw();

// member variables
	const int	m_fd;
};

template <typename SocketType>
Socket<SocketType>::Socket() throw()
:	m_fd(socket(SocketType::domain, SocketType::type, SocketType::protocol))
{
}

template <typename SocketType>
Socket<SocketType>::~Socket() throw()
{
	close(m_fd);
}

template <typename SocketType>
Socket<SocketType>::Socket(Socket const& socket) throw()
:	m_fd(dup(socket.m_fd))
{
}

template <typename SocketType>
Socket<SocketType>::Socket(int fd) throw()
:	m_fd(fd)
{
}

template <typename SocketType>
int
Socket<SocketType>::bind(socketAddr* addr) throw()
{
	return bind(m_fd, addr, SocketType::socketAddrLen);
}

template <typename SocketType>
int
Socket<SocketType>::listen(int backlog) throw()
{
	return listen(m_fd, backlog);
}

template <typename SocketType>
int
Socket<SocketType>::accept(socketAddr* raddr) throw()
{
	return accept(m_fd, raddr, SocketType::socketAddrLen);
}

template <typename SocketType>
int
Socket<SocketType>::connect(socketAddr* addr) throw()
{
	return connect(m_fd, addr, SocketType::socketAddrLen);
}

// operators

#endif