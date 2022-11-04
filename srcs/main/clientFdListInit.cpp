/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientFdListInit.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:28:18 by llethuil          #+#    #+#             */
/*   Updated: 2022/11/04 11:28:21 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "../../incs/main.hpp"

void	clientFdListInit(t_clientFdList *clientFdList, int serverSocket)
{
	clientFdList->max 		= serverSocket;
	clientFdList->t.tv_sec	= 0;
	clientFdList->t.tv_usec	= 10;
	FD_ZERO(&clientFdList->master);
	FD_ZERO(&clientFdList->read);
	FD_SET(serverSocket, &clientFdList->master);
}