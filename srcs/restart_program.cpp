/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart_program.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 10:14:21 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/12 10:14:22 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

vector<program>		restart_program(vector<string> args, vector<program> program_list)
{
	if (!args.size())
		return (program_list);
	if (!args[0].length())
	{
		print_error(-1, "*** Arguments are missing (see help <topic>");
		return (program_list);
	}
	else
	{
		program_list = stop_program(args, program_list);
		print("\n");
		program_list = start_program(args, program_list);
		return (program_list);
	}
}