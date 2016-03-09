/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_program.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 02:05:33 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/09 02:05:35 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		start_program(vector<string> args, vector<program> program_list)
{
	if (!args.size())
	{
		print_fd("*** Arguments are missing (see help <topic>)", 2);
	}
	else
	{
		if (args[0] == "all")
		{
			int i = 0;
			if (!program_list.size())
			{
				print_error(-1, "There is no process to launch");
				add_in_logs(TaskMasterValue::Current().LogFilePath, "Trying to launch all process but there is no process found");
			}
			while (i < program_list.size())
			{
				handle_program(program_list[i]);
				i++;
			}
		}
		else
		{
			int i = 0;
			int	p_i = 0;
			bool found = false;
			while (i < args.size())
			{
				while (p_i < program_list.size())
				{
					if (program_list[p_i].program_name == args[i])
					{
						handle_program(program_list[p_i]);
						found = true;
					}
					p_i++;
				}
				if (!found)
				{
					if ((i + 1) < args.size())
						print_fd("*** Process " + args[i] + " not found\n", 2);
					else
						print_fd("*** Process " + args[i] + " not found", 2);
					add_in_logs(TaskMasterValue::Current().LogFilePath, "Trying to launch a process not found (" + args[i] + ")");
				}
				p_i = 0;
				found = false;
				i++;
			}
		}
	}
}