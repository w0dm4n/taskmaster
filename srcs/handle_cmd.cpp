/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 04:24:43 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/08 04:24:45 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

string				get_cmd(string cmd)
{
	int		i;
	string	tmp;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
	{
		tmp += cmd[i];
		i++;
	}
	return (tmp);
}

vector<string>		get_args(string cmd)
{
	int				i;
	vector<string>	tmp_args;
	string			tmp;
	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	i++;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
		{
			while (cmd[i] && cmd[i] != ' ')
			{
				tmp += cmd[i];
				i++;
			}
			if (ft_is_all_print((char*)tmp.c_str()) || tmp.find(';') != -1)
				tmp_args.push_back(tmp);
			tmp.clear();
		}
		i++;
	}
	return (tmp_args);
}

vector<program>		handle_cmd(string cmd, vector<program> progam_list)
{
	string			cmd_to;
	vector<string>	cmd_args;
	int				i = 0;

	cmd_to = get_cmd(cmd);
	cmd_args = get_args(cmd);
	return (check_cmd(cmd_to, cmd_args, progam_list));
}