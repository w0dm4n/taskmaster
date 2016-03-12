/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_program.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 23:39:20 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/10 23:39:21 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

vector<program> stop_program(vector<string> args, vector<program> program_list)
{
	if (!args.size())
	{
		print("*** Arguments are missing (see help <topic>)");
		return (program_list);
	}
	int		i = 0;
	bool	found = false;
	int		res = 0;
	if (args[0] == "all")
	{
		while (i != program_list.size())
		{
			if (program_list[i].pid != 0)
			{
				if (!program_list[i].exit_signal_to_set.length()
					|| program_list[i].exit_signal_to_set == "SIGTERM")
					res = kill(program_list[i].pid, SIGTERM);
				else if (program_list[i].exit_signal_to_set == "SIGKILL")
					res = kill(program_list[i].pid, SIGKILL);
				else if (program_list[i].exit_signal_to_set == "SIGSTOP")
					res = kill(program_list[i].pid, SIGSTOP);
				else if (program_list[i].exit_signal_to_set == "SIGINT")
					res = kill(program_list[i].pid, SIGINT);
				else if (program_list[i].exit_signal_to_set == "SIGQUIT")
					res = kill(program_list[i].pid, SIGQUIT);
				else if (program_list[i].exit_signal_to_set == "SIGABRT")
					res = kill(program_list[i].pid, SIGABRT);
				else if (program_list[i].exit_signal_to_set == "SIGTSTP")
					res = kill(program_list[i].pid, SIGTSTP);
				else if (program_list[i].exit_signal_to_set == "SIGTTIN")
					res = kill(program_list[i].pid, SIGTTIN);
				else if (program_list[i].exit_signal_to_set == "SIGTTOU")
					res = kill(program_list[i].pid, SIGTTOU);
				else if (program_list[i].exit_signal_to_set == "SIGUSR1")
					res = kill(program_list[i].pid, SIGUSR1);
				else if (program_list[i].exit_signal_to_set == "SIGUSR2")
					res = kill(program_list[i].pid, SIGUSR2);
				if (res != -1)
				{
					print("*** Program " + program_list[i].program_name + " (");
					print_nbr(program_list[i].pid);
					print(") stopped.\n");
					program_list[i].pid = 0;
					found = true;
					add_in_logs(TaskMasterValue::Current().LogFilePath, "The program " + program_list[i].program_name + " was stopped.");
				}
			}
			i++;
		}
		if (!found)
			print("*** There is no started process.\n");
	}
	else
	{
		int		p_i = 0;
		bool	found = 0;
		int		res = 0;
		while (i != args.size())
		{
			while (p_i != program_list.size())
			{
				if (program_list[p_i].program_name == args[i])
				{
					if (program_list[i].pid != 0)
					{
						if (!program_list[i].exit_signal_to_set.length()
							|| program_list[i].exit_signal_to_set == "SIGTERM")
							res = kill(program_list[i].pid, SIGTERM);
						else if (program_list[i].exit_signal_to_set == "SIGKILL")
							res = kill(program_list[i].pid, SIGKILL);
						else if (program_list[i].exit_signal_to_set == "SIGSTOP")
							res = kill(program_list[i].pid, SIGSTOP);
						else if (program_list[i].exit_signal_to_set == "SIGINT")
							res = kill(program_list[i].pid, SIGINT);
						else if (program_list[i].exit_signal_to_set == "SIGQUIT")
							res = kill(program_list[i].pid, SIGQUIT);
						else if (program_list[i].exit_signal_to_set == "SIGABRT")
							res = kill(program_list[i].pid, SIGABRT);
						else if (program_list[i].exit_signal_to_set == "SIGTSTP")
							res = kill(program_list[i].pid, SIGTSTP);
						else if (program_list[i].exit_signal_to_set == "SIGTTIN")
							res = kill(program_list[i].pid, SIGTTIN);
						else if (program_list[i].exit_signal_to_set == "SIGTTOU")
							res = kill(program_list[i].pid, SIGTTOU);
						else if (program_list[i].exit_signal_to_set == "SIGUSR1")
							res = kill(program_list[i].pid, SIGUSR1);
						else if (program_list[i].exit_signal_to_set == "SIGUSR2")
							res = kill(program_list[i].pid, SIGUSR2);
						if (res != -1)
						{
							print("*** Program " + program_list[p_i].program_name + " (");
							print_nbr(program_list[p_i].pid);
							print(") stopped.\n");
							found = true;
							program_list[p_i].pid = 0;
							add_in_logs(TaskMasterValue::Current().LogFilePath, "The program " + program_list[p_i].program_name + " was stopped.");
						}
					}
					else
					{
						print("*** Program " + program_list[p_i].program_name + " doesn't seems to be started.");
						program_list[p_i].pid = 0;
					}
					found = true;
				}
				p_i++;
			}
			if (!found)
				print("*** Process " + args[i] + " not found.");
			found = false;
			p_i = 0;
			i++;
		}			
	}
	return (program_list);
}