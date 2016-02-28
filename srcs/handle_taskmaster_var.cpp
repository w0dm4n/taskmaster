/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_taskmaster_var.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 04:06:36 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/26 04:06:37 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static vector<string> get_args(string line, vector<string> args)
{
	char	**args_tmp;
	int		i;

	i = 0;
	line = line.substr(1, line.length());
	args_tmp = ft_strsplit(line.c_str(), ';');
	while (args_tmp[i])
	{
		args.push_back(args_tmp[i]);
		i++;
	}
	args.push_back("\0");
	return (args);
}

static	string get_correct_path(string path)
{
	int i;
	bool found = false;

	i = 0;
	while (path[i])
	{
		if (path[i] == '~')
		{
			found = true;
			break ;
		}
		i++;
	}
	if (found)
	{
		path.erase(i, (i + 1));
		path.insert(i, getenv("HOME"));
	}
	return (path);
}

void	handle_taskmaster_var(string line, int position)
{
	vector<string>	args;
	int				i = 0;

	position += 2;
	args = get_args(line, args);
	if (args.size())
	{
		if (args[0] == "taskmaster_log_file")
		{
			if (args[1].length())
			{

			}
			else
				print_error(position, "path of the log file is missing !");
		}
		else
			print_error(position, "Unknown variable " + args[0]);
	}
	else
		print_error(position, "missing or invalid variable name");
}