/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:23:07 by llethuil          #+#    #+#             */
/*   Updated: 2022/11/11 11:43:18 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# ifndef CHANNEL_HPP
# define CHANNEL_HPP

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ INCLUDES ~~~                             */
/*                                                                            */
/* ************************************************************************** */

# include "main.hpp"

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ CLASS ~~~                                */
/*                                                                            */
/* ************************************************************************** */

class User;

class Channel
{
	public :
		/* constructors													*/
							Channel(void);
							Channel(std::string name);
		/* public attributes											*/
		std::string			_name;
		std::string			_key;
		bool				_requiresKey;
		std::string			_topic;
		bool				_topicIsSet;
		std::set<int>		_members;
		std::set<int>		_operators;
		std::string			_mode;

		/* operator overload											*/
		Channel				&operator=(const Channel& src);

		/* member functions												*/
		void				addMember(User &user);
		void				setKey(std::string key);
		// void				addMember(int userSocket);
		// void				deleteMember(User &user);
		// void				deleteMember(int userSocket);
		// void				addOperator(User &user);
		// void				addOperator(int userSocket);
		// void				deleteOperator(User &user);
		// void				deleteOperator(int userSocket);
		// void	sendMsgToMembers(const std::string &content, int socketException) const;

		/* exceptions													*/

		/* destructor													*/
							~Channel(void);

	private :

		/* copy constructor												*/
							Channel(const Channel& src);


		/* private attributes											*/

};

# endif