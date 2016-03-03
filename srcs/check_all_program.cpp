/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_program.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 01:59:04 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/03 01:59:06 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

bool check_all_program(vector<program> program_list)
{
	int i;

	i = 0;
	while (i != program_list.size())
	{
		if (!program_list[i].program_name.length())
			print_error(-1, "taskmaster: missing program name on a function");
		if (!program_list[i].executable_path.length())
			print_error(-1, "taskmaster: missing executable_path on the program " + program_list[i].program_name);
		i++;
	}
	return (true);
}