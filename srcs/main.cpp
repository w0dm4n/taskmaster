/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 00:10:54 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/26 00:10:55 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

int		main(int argc, char **argv, char **env)
{
	int i;
	bool	args;
	bool	other;
	string flags;
	string current_flag;
	string config_file;

	i = 1;
	args = 0;
	args = false;
	other = false;
	if (argc != 1)
	{
		while (argv[i])
		{
			if (argv[i][0] == '-')
			{
				if (!other)
				{
					current_flag = argv[i];
					current_flag = current_flag.substr(1, current_flag.length());
					flags += current_flag;
					args = true;
				}
				else
				{
					cerr << "taskmaster: bad syntax (argument - config file)" << endl;
					return (-1);
				}
			}
			else
			{
				if (!args)
				{
					cerr << "taskmaster: bad syntax (argument - config file)" << endl;
					return (-1);
				}
				else
				{
					config_file = argv[i];
					other = true;
				}
			}
			i++;
		}
		if (strchr(flags.c_str(), 'c') && other)
		{
			TaskMasterValue::Current().DefaultEnvironment = get_environment_vector(env);
			handle_config(config_file);
		}
		else
			cerr << "taskmaster: missing configuration file" << endl;
	}
	else
		cerr << "taskmaster: no argument given" << endl;
	return (0);
}
