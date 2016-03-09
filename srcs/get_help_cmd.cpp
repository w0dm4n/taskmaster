/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_help_cmd.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 23:04:11 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/08 23:04:13 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	get_help_cmd(vector<string> args)
{
	string	topic;
	int		i = 0;
	if (!args.size())
	{
		print("\n");
		print("default commands (type help <topic>):\n");
		print("=====================================\n");
		print("status	start	stop	reload");
		print("\n");
	}
	else
	{
		while (i < args.size())
		{
			if (args[i].length())
				topic += args[i];
			if ((i + 1) < args.size())
				topic += " ";
			i++;
		}
		if (topic == "status")
		{
			print ("status			Get all process status infos\n"); 
			print ("status <name>           Get status on multiple or single process");
		}
		else if (topic == "start")
		{
			print ("start <name>		Start on multiple or single a process by name\n");
			print ("start all               Start all process");
		}
		else if (topic == "reload")
		{
			print ("reload config		Reload the config file");
		}
		else if (topic == "stop")
		{
			print ("stop <name>			Stop multiple or single process by name\n");
			print ("stop all			Stop all process");
		}
		else
			print_fd("*** No help on " + topic, 2);
	}
	topic.clear();
}