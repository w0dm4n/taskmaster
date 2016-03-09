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

void		get_process_status(vector<string> args, vector<program> program_list)
{
	if (!args.size())
	{
		print("get all process status !");
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
					print("process found");
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