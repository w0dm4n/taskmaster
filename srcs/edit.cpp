/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 01:18:30 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/15 01:18:31 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

vector<program>		edit(vector<string> args, vector<program> program_list)
{
	if (args.size() != 2)
	{
		print_fd("*** Arguments are missing (see help <topic>)", 2);
		return (program_list);
	}
	else
	{
		int i = 0;
		int found = false;
		string save_first_char;
		TaskMasterValue::Current().ExitProgramOnError = false;
		while (i != program_list.size())
		{
			if (program_list[i].program_name == args[0])
			{
				save_first_char += args[1][0];
				args[1].insert(0, save_first_char);
				program_list[i] = check_variable_and_set(args[1], program_list[i], -1);
				found = true;
			}
			save_first_char.clear();
			i++;
		}
		if (!found)
			print_fd("*** Program " + args[0] + " was not found.", 2);
	}
	TaskMasterValue::Current().ExitProgramOnError = true;
	return (program_list);
}