/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdReply.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:32:44 by llethuil          #+#    #+#             */
/*   Updated: 2022/12/02 14:02:09 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ INCLUDES ~~~                             */
/*                                                                            */
/* ************************************************************************** */

# include "../../../incs/Server.hpp"
# include "../../../incs/main.hpp"

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ FUNCTION ~~~                             */
/*                                                                            */
/* ************************************************************************** */

void	Server::cmdReply(User &user, std::string cmd, std::string param)
{
	std::string finalMsg = ":" + user.getNickname() + " " + cmd + " " + param + "\r\n";

	std::cout << BLUE << "[SERVER] : " << END << finalMsg << std::endl;

	if (FD_ISSET(user.getSocket(), &this->_clientFdList.write))
		if (send(user.getSocket(), finalMsg.c_str(), finalMsg.size(), 0) == FAILED)
			perror("send()");
}