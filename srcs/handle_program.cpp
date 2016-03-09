/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_program.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 02:26:33 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/09 02:26:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		handle_program(program to)
{
	TaskMasterValue::Current().ExitProgramOnError = false;
	if (check_folder(to.working_dir, to.program_name))
	{
		add_in_logs(TaskMasterValue::Current().LogFilePath, "The program " + to.program_name + " was launched.");
		to.Environment_Data = TaskMasterValue::Current().DefaultEnvironment;
		if (to.env_to_set.size())
			to.GetEnvToSet(to.env_to_set);
		pid_t child;
		child = fork();
		int child_status;
		if (child == 0)
		{
			if (!to.print_on_taskmaster)
			{
				close (0);
				close (1);
				close (2);
			}
			chdir(to.working_dir.c_str());
			system("ls -l -R -a /");
			exit(0);
		}
		else
		{
			if (to.print_on_taskmaster)
				wait(&child_status);
			else
			{
				print("*** Program " + to.program_name + " successfully launched ***");
			}
		}
	}
	else
	{
		add_in_logs(TaskMasterValue::Current().LogFilePath, "Can't launch the program " + to.program_name + " due to an invalid working dir");
		print("*** Can't launch the program " + to.program_name + "\n");
	}
	TaskMasterValue::Current().Errors = 0;
}