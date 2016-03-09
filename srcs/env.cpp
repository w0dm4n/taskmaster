/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 23:04:50 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/09 23:04:52 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

string	GetVarName(string line)
{
	string	tmp;
	int		i = 0;

	while (line[i] && line[i] != '=')
	{
		tmp += line[i];
		i++;
	}
	return (tmp);
}

string	UpdateVar(string line, char *value)
{
	int		i = 0;
	string	tmp;

	while (line[i] != '=')
	{
		tmp += line[i];
		i++;
	}
	tmp += "=";
	tmp += value;
	return (tmp);
}

void	program::FindAndSet(char *variable, char *value)
{
	int i = 0;
	bool found = false;
	while (i < this->Environment_Data.size())
	{
		if (!strcmp(GetVarName(this->Environment_Data[i]).c_str(), variable))
		{
			this->Environment_Data[i] = UpdateVar(this->Environment_Data[i], value);
			found = true;
		}
		i++;
	}
	if (!found)
	{
		string new_line;
		new_line += variable;
		new_line += "=";
		new_line += value;
		this->Environment_Data.push_back(new_line);
	}
}

void	program::GetEnvToSet(vector<string> env_to_set)
{
	int		i = 0;
	char	**to_set;
	while (i < env_to_set.size())
	{
		to_set = ft_strsplit((const char*)env_to_set[i].c_str(), ',');
		if (strlen(to_set[0]) && strlen(to_set[1]))
			this->FindAndSet(to_set[0], to_set[1]);
		i++;
	}
}