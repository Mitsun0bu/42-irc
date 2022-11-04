/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:24:17 by llethuil          #+#    #+#             */
/*   Updated: 2022/11/04 11:55:18 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ INCLUDES ~~~                             */
/*                                                                            */
/* ************************************************************************** */

# include "../../incs/User.hpp"

/* ************************************************************************** */
/*                                                                            */
/*                      ~~~ CONSTRUCTORS ~~~                                  */
/*                                                                            */
/* ************************************************************************** */

User::User(void)
{
	std::cout	<< BLUE
				<< "[CONSTRUCTOR] : "
				<< END
				<< "A new user has been created !"
				<< std::endl;

	this->_socketAddrSize	= sizeof(this->_socketAddr);

	return ;
}

User::User(User const & src)
{
	std::cout	<< ORANGE
				<< "[COPY CONSTRUCTOR] : "
				<< END
				<< "A user has been duplicated !"
				<< std::endl;

	*this = src;

	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                         ~~~ OPERATOR OVERLOAD ~~~                          */
/*                                                                            */
/* ************************************************************************** */

User&	User::operator=(User const & src)
{
	this->_socket			= src._socket;
	this->_socketAddr		= src._socketAddr;
	this->_socketAddrSize	= src._socketAddrSize;
	strcpy(this->_remoteIP, src._remoteIP);

	return (*this);
}

/* ************************************************************************** */
/*                                                                            */
/*                         ~~~ MEMBER FUNCTIONS ~~~                           */
/*                                                                            */
/* ************************************************************************** */



const void*	User::getInAddr(void)
{
	struct sockaddr*	address = (struct sockaddr*)&this->_socketAddr;

	if (address->sa_family == AF_INET)
		this->_inAddr = &(((struct sockaddr_in*)address)->sin_addr);
	else
		this->_inAddr = &(((struct sockaddr_in6*)address)->sin6_addr);

	return (this->_inAddr);
}

const char*	User::getIp(void)
{
		this->_ip	= inet_ntop(
									this->_socketAddr.ss_family,
									this->getInAddr(),
									this->_remoteIP,
									INET6_ADDRSTRLEN
							   );

		return (this->_ip);
}

/* ************************************************************************** */
/*                                                                            */
/*                           ~~~ DESTRUCTOR ~~~                               */
/*                                                                            */
/* ************************************************************************** */

User::~User(void)
{
	std::cout	<< PURPLE
				<< "[DESTRUCTOR] : "
				<< END
				<< "User "
				<< this->_socket
				<< " has been destroyed."
				<< std::endl;
	return ;
}