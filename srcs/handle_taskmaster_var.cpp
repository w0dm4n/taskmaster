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

vector<string> get_args(string line, vector<string> args, char delimiter)
{
	char	**args_tmp;
	int		i;

	i = 0;
	line = line.substr(1, line.length());
	args_tmp = ft_strsplit(line.c_str(), delimiter);
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

static int		get_variable_state(string var)
{
	if (var == "taskmaster_log_file")
		return (LOG_FILE);
	return (UNKNOWN_VARIABLE);
}

void	handle_taskmaster_var(string line, int position)
{
	vector<string>	args;
	int				i = 0;

	position += 2;
	args = get_args(line, args, ';');
	if (args.size())
	{
		switch (get_variable_state(args[0]))
		{
			case LOG_FILE:
				if (args[1].length())
				{
					args[1] = get_correct_path(args[1]);
					ifstream file(args[1]);
					if (file)
						TaskMasterValue::Current().LogFilePath = args[1];
					else
						print_error(position, "path of the log file is invalid !");
				}
				else
					print_error(position, "path of the log file is missing !");
			break;

			default:
				print_error(position, "Unknown variable " + args[0]);
			break;		
		}		
	}
	else
		print_error(position, "missing or invalid variable name");
}