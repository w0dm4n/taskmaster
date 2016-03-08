/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:45:12 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/08 22:45:13 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

vector<string>	clear_args(vector<string> cmd_args)
{
	int i = 0;
	while (i < cmd_args.size())
	{
		cmd_args[i] = '\0';
		i++;
	}
	return (cmd_args);
}

void			check_cmd(string cmd, vector<string> cmd_args)
{
	write(1, "\n", 1);
	if (cmd == "help")
		get_help_cmd(cmd_args);
	else
		print_fd("*** Unknown syntax: " + cmd, 2);
	cmd_args = clear_args(cmd_args);
	cmd_args.clear();
}