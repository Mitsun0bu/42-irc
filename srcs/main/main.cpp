/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:32:28 by llethuil          #+#    #+#             */
/*   Updated: 2022/11/11 18:45:14 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "../../incs/main.hpp"

/*
	LISTE DES COMMANDES A CODER :

	CONNECTION
		CAP message
		AUTHENTICATE message
		PASS message
		NICK message
		USER message
		PONG message
		QUIT message

	CHANNEL OPERATIONS
		JOIN message
		PART message
		TOPIC message
		NAMES message
		LIST message
		INVITE message
		KICK message

	SERVER QUERIES AND COMMANDS
		MODE message (gerer l'operateur)

	SENDING MESSAGES
		PRIVMSG message
		NOTICE message
*/

int	main(int ac, char** av)
{
	// HANDLE PROGRAM ARGUMENTS
	std::pair<int, std::string>	param				= parseArguments(ac, av);
	int							port				= param.first;
	std::string					passwd				= param.second;

	// CREATE SERVER
	Server	server(
					port,
					AF_INET,
					SOCK_STREAM,
					F_SETFL,
					O_NONBLOCK,
					0,
					"127.0.0.1"
			 	  );

	// SET SERVER
	if (server.setSocket() == FAILED)
		exit(1);
	server.clientFdListInit();

	// DEBUG
	std::cout << std::endl << "~~~ Waiting for new connection ~~~" << std::endl;

	// HANDLE CLIENT CONNECTION
	launchServer(server);

	return (0);
}