/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 02:18:17 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/29 02:18:19 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int			get_variable_state(string var)
{
	if (var == "executable_path")
		return (EXECUTABLE_PATH);
	else if (var == "executable_argument")
		return (EXECUTABLE_ARGUMENT);
	else if (var == "set_env")
		return (SET_ENV);
	else if (var == "working_dir")
		return (WORKING_DIR);
	else if (var == "auto_start")
		return (AUTO_START);
	return (UNKNOWN_VARIABLE);
}

static program		check_variable_and_set(string line, program tmp, int position)
{
	vector<string>	args;
	int				i;

	i = 0;
	args = get_args(line, args, ';');
		switch (get_variable_state(args[0]))
		{
			case EXECUTABLE_PATH:
				i++;
				while (i != (args.size() - 1))
				{
					cout << args[i] << endl;
					i++;
				}
			break;

			case EXECUTABLE_ARGUMENT:
				i++;
				while (i != (args.size() - 1))
				{
					cout << args[i] << endl;
					i++;
				}
			break;

			case SET_ENV:
				i++;
				while (i != (args.size() - 1))
				{
					cout << args[i] << endl;
					i++;
				}
			break;

			case WORKING_DIR:
				i++;
				while (i != (args.size() - 1))
				{
					cout << args[i] << endl;
					i++;
				}
			break;

			case AUTO_START:
				i++;
				while (i != (args.size() - 1))
				{
					cout << args[i] << endl;
					i++;
				}
			break;

			default:
				if (args[0][0] != '/')
					print_error(position, "unknown variable " + args[0]);
			break;
		}
	return (tmp);
}

program		get_program_args(int start, vector<string> data, int end, string name)
{
	program tmp;

	name = name.substr(1, name.length());
	name = name.substr(0, (name.length() - 1));
	if (!name.length())
		print_error(start, "program name missing !");
	tmp.program_name = name;
	while (start != end)
	{
		tmp = check_variable_and_set(data[start], tmp, (start + 2));
		start++;
	}
	return (tmp);
}