/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 01:22:26 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/09 01:22:30 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

vector<program> 	reload(vector<string> args, vector<program> program_list)
{
	if (!args.size())
	{
		print_fd("*** Arguments are missing (see help <topic>)", 2);
	}
	else
	{
		if (args[0] == "config")
		{
			vector<program> new_list;
			config_infos config;
			TaskMasterValue::Current().ExitProgramOnError = false;
			config.config_file_name = TaskMasterValue::Current().ConfigFileName;
			if (config.check_if_config_exist())
				new_list = config.read_config(new_list);
			check_all_program(new_list);
			if (TaskMasterValue::Current().Errors == 0)
			{
				print("*** Config file has been reloaded");
				return (new_list);
			}
			else
			{
				print("\n*** Can't reload the config file due to ");
				print_nbr(TaskMasterValue::Current().Errors);
				print (" errors");
				TaskMasterValue::Current().Errors = 0;
				return (program_list);
			}
		}
		else
			print_fd("*** Arguments are invalid (see help <topic>", 2);
	}
	return (program_list);
}