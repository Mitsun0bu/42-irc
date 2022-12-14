/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:15:50 by llethuil          #+#    #+#             */
/*   Updated: 2022/12/07 11:15:11 by llethuil         ###   ########lyon.fr   */
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

void	Server::partCmd(User &user, std::vector<std::string> &cmdTokens)
{
	std::vector<std::string>					channelsToLeave;
	std::string									reason = "";
	std::map<std::string, Channel>::iterator	it;

	if (cmdTokens.size() < 2)
		return(this->numericReply(user, _num.ERR_NEEDMOREPARAMS, cmdTokens[0], _num.MSG_ERR_NEEDMOREPARAMS));

	tokenizer(cmdTokens[1], ",", channelsToLeave);
	if(cmdTokens.size() == 3)
		reason = cmdTokens[2];

	for (size_t i = 0; i < channelsToLeave.size(); i++)
	{
		// IF CHANNEL TO LEAVE DOES NOT EXIST
		if (_channels.find(channelsToLeave[i]) == _channels.end())
		{
			numericReply(user, _num.ERR_NOSUCHCHANNEL, channelsToLeave[i], _num.MSG_ERR_NOSUCHCHANNEL);
			continue;
		}

		// IF CHANNEL TO LEAVE EXISTS
		for(it = _channels.begin(); it != _channels.end(); ++it)
		{
			// WHEN CHANNEL IS FIND IN SERVER CHANNELS
			if (it->first == channelsToLeave[i])
				if (leaveChannel(user, it->second, channelsToLeave[i], reason) == STOP)
					return ;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ UTILS ~~~                                */
/*                                                                            */
/* ************************************************************************** */

int	Server::leaveChannel(User &user, Channel& channel, std::string channelName, std::string reason)
{
	// IF USER IS NOT IN CHANNEL TO LEAVE
	if (user.getLocations().find(channelName) == user.getLocations().end())
	{
		std::string	notInChannelMsg = " " + user.getNickname() + " " + channelName;
		numericReply(user, _num.ERR_NOTONCHANNEL, notInChannelMsg, _num.MSG_ERR_NOTONCHANNEL);
		return (CONTINUE);
	}

	// REMOVE USER FROM CHANNEL MEMBERS
	channel.getMembers().erase(user.getSocket());

	// REMOVE CHANNEL FROM USER LOCATIONS
	user.getLocations().erase(channelName);

	// IF CHANNEL HAS INVITE MODE, REMOVE USER FROM ALLOWED MEMBERS
	if (channel.getModeInvite() == "+i"
	&&  channel.getAllowedMembers().find(user.getSocket()) != channel.getAllowedMembers().end())
		channel.getAllowedMembers().erase(user.getSocket());

	// REPLY
	cmdReply(user, "PART", channelName + " " + reason);
	sendCmdToChannel(user, "PART", channel.getMembers(), channelName, " " + reason);

	// IF THE USER WAS AN OPERATOR, REMOVE IT FROM OPERATOR SET
	if (channel.getOperators().find(user.getSocket()) != channel.getOperators().end())
		channel.removeOperator(user.getSocket());

	// IF THERE IS NO MEMBERS OR OPERATOR IN CHANNEL ANYMORE, DELETE THE CHANNEL
	if (channel.getMembers().size() == 0 || channel.getOperators().size() == 0) // SEE WITH ALEX
	{
		for (std::set<int>::iterator it = channel.getMembers().begin(); it != channel.getMembers().end(); it ++)
		{
			cmdReply(user, "KICK", channel.getName() + " " + getUserNickname(*it));
			sendCmdToChannel(user, "KICK", channel.getMembers(),  channel.getName(), getUserNickname(*it));
			removeUserFromChannel(_users[*it], channel);
			if (channel.getMembers().size() == 0)
				break;
		}
		deleteChannel(channelName);
		if (_channels.size() == 0)
			return(STOP);
	}
	return (SUCCESS);
}