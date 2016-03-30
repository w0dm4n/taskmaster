/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process_status.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 01:05:26 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/09 01:05:27 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		print_program_informations(vector<program> program_list, int p_i)
{
	int f = -1;
	int env = 0;
	string first_line = "Information for the program ";
	first_line += program_list[p_i].program_name;
	print("/");
	while (f++ != first_line.length())
		print("*");
	print("\\\n");
	print("  " + first_line + " ");
	print("\n");
	print("\\");
	f = -1;
	while (f++ != first_line.length())
		print("*");
	print("/\n");
	print("Path of the executable file : " + program_list[p_i].executable_path + "\n");
	if (program_list[p_i].working_dir.length())
		print("Executable working directory : " + program_list[p_i].working_dir + "\n");
	if (program_list[p_i].executable_argument.length())
		print("Executable argument(s) : " + program_list[p_i].executable_argument + "\n");
	if (program_list[p_i].env_to_set.size())
	{
		print("Environment variable(s) to set : \n");
		while (env != program_list[p_i].env_to_set.size())
		{
			if ((env + 1) != program_list[p_i].env_to_set.size())
				print(program_list[p_i].env_to_set[env] + " ");
			else
				print(program_list[p_i].env_to_set[env]);
			env++;
		}
		print("\n");
		env = 0;
	}
	print("Automatic start mode : ");
	(program_list[p_i].auto_start) ? print("TRUE") : print("FALSE");
	print ("\n");
	if (program_list[p_i].set_umask.length())
	{
		print("Umask to set : ");
		print(program_list[p_i].set_umask);
		print("\n");
	}
	print ("Process actually launched : ");
	if (program_list[p_i].pid)
	{
		print("TRUE (");
		print_nbr(program_list[p_i].pid);
		print(")");
	}
	else
		print("FALSE");
	print("\n");
	if (program_list[p_i].stdout_to_file.length())
		print ("Redirect STDOUT from the executable to : " + program_list[p_i].stdout_to_file + "\n");
	if (program_list[p_i].stderror_to_file.length())
		print ("Redirect STDERR from the executable to : " + program_list[p_i].stderror_to_file + "\n");
	if (program_list[p_i].exit_signal_to_set.length())
		print("EXIT SIGNAL : " + program_list[p_i].exit_signal_to_set + "\n");
	print("Print executable to taskmaster : ");
	(program_list[p_i].print_on_taskmaster) ? print("TRUE\n") : print("FALSE\n");
	print("Process exit return : ");
	print_nbr(program_list[p_i].exit_code);
	print("\n");
	print("Time before closing the process : ");
	print_nbr(program_list[p_i].stop_time);
	print("s\n");
}

void		get_process_status(vector<string> args, vector<program> program_list)
{
	int i = 0;
	int	p_i = 0;
	bool found = false;
	if (!args.size())
	{
		while (i < program_list.size())
		{
			print_program_informations(program_list, i);
			if ((i + 1) < program_list.size())
				print("\n\n");
			i++;
		}
	}
	else
	{
		while (i < args.size())
		{
			while (p_i < program_list.size())
			{
				if (program_list[p_i].program_name == args[i])
				{
					print_program_informations(program_list, p_i);
					found = true;
				}
				p_i++;
			}
			if (!found)
			{
				if ((i + 1) < args.size())
					print_fd("*** No such process " + args[i] + "\n", 2);
				else
					print_fd("*** No such process " + args[i], 2);
			}
			found = false;
			p_i = 0;
			i++;
		}
	}
}