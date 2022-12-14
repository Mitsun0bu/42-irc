/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isOperator.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:01:33 by llethuil          #+#    #+#             */
/*   Updated: 2022/11/29 10:06:30 by llethuil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ INCLUDES ~~~                             */
/*                                                                            */
/* ************************************************************************** */

# include "../../../incs/User.hpp"

/* ************************************************************************** */
/*                                                                            */
/*                               ~~~ FUNCTION ~~~                             */
/*                                                                            */
/* ************************************************************************** */

bool	User::isOperator(std::set<int>	operatorSet)
{
	if (operatorSet.find(_socket) != operatorSet.end())
		return (true);
	return (false);
}