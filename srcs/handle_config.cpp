/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_config.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 03:03:15 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/26 03:03:16 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

bool	program_to_auto_start(vector<program> program_list)
{
	int i = 0;
	while (i < program_list.size())
	{
		if (program_list[i].auto_start)
			return (true);
		i++;
	}
	return (false);
}

void	auto_restart_program(vector<program> program_list)
{
	pid_t			slt;
	vector<string>	args;

	args.push_back("default");
	if ((slt = fork()) == 0)
	{
		int i = 0;
		while (1)
		{
			i = 0;
			while (i != program_list.size())
			{
				if (program_list[i].auto_restart)
				{
					if (program_list[i].time_for_restart != 0)
						sleep(program_list[i].time_for_restart);
					if (program_list[i].pid == 0)
					{
						args[0] = program_list[i].program_name;
						int fd = dup(1);
						close(1);
						program_list = start_program(args, program_list);
						dup2(fd, 1);
						print("\n*** The program " + program_list[i].program_name + " was automatically launched !\ntaskmaster> ");
					}
				}
				i++;
			}
		}
	}
}

void	handle_config(string config_name)
{
	config_infos config;
	vector<program> program_list;

	config.config_file_name = config_name;
	TaskMasterValue::Current().ExitProgramOnError = true;
	UserEntry::Current().auto_completion_get = 0;
	if (config.check_if_config_exist())
		program_list = config.read_config(program_list);
	if (!TaskMasterValue::Current().LogFilePath.length())
		TaskMasterValue::Current().LogFilePath = "taskmaster.log";
	if (!TaskMasterValue::Current().LogFilePathExist)
		add_in_logs(TaskMasterValue::Current().LogFilePath, "Configuration file generated");
	if (check_all_program(program_list))
	{
		if (program_to_auto_start(program_list))
		{
			print(" *** Auto starting program start ***\n");
			int i = 0;
			while (i < program_list.size())
			{
				if (program_list[i].auto_start)
					program_list = handle_program(program_list[i], i, program_list);
				i++;
			}
			print("*** Auto starting program end ***\n\n");
		}
		auto_restart_program(program_list);
		TaskMasterValue::Current().ConfigFileName = config_name;
		print("taskmaster> ");
		read_user_entry(program_list);
	}
}