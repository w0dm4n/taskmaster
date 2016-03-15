/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tabulation.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 02:30:15 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/15 02:30:16 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include <termios.h>
#include <term.h>

static		void update_stdout()
{
	int i = 0;
	refresh_stdout();
	UserEntry::Current().cursor++;
	while (UserEntry::Current().cursor)
	{
		UserEntry::Current().cursor--;
		tputs(tgetstr((char*)"le", NULL), 0, cursor_do);
	}
	while (i != UserEntry::Current().cmd.length())
	{
		UserEntry::Current().cursor++;
		tputs(tgetstr((char*)"nd", NULL), 0, cursor_do);
		i++;
	}
}

static		void delete_name(vector<program> program_list)
{
	int i = UserEntry::Current().cmd.length();
	while (UserEntry::Current().cmd[i] != ' ')
	{
		tputs(tgetstr((char*)"dc", NULL), 0, cursor_do);
		tputs(tgetstr((char*)"le", NULL), 0, cursor_do);
		UserEntry::Current().cmd[i] = '\0';
		UserEntry::Current().cmd.erase(i, 1);
		i--;
	}
	i++;
	UserEntry::Current().cmd[i] = '\0';
	UserEntry::Current().cmd.erase(i, 1);
	UserEntry::Current().cmd.insert(i, program_list[UserEntry::Current().auto_completion_get].program_name + "\0");
	i = 0;
	print(" ");
	while (program_list[UserEntry::Current().auto_completion_get].program_name[i])
	{
		write(1, &program_list[UserEntry::Current().auto_completion_get].program_name[i], 1);
		i++;
	}
	UserEntry::Current().cursor = 0;
	i = 0;
	while (i != UserEntry::Current().cmd.length())
	{
		UserEntry::Current().cursor++;
		i++;
	}
}

void		get_command()
{
		if (UserEntry::Current().cmd == "edit")
		{
			UserEntry::Current().cmd = "exit";
			update_stdout();
		}
		else if (UserEntry::Current().cmd == "status")
		{
			UserEntry::Current().cmd = "start";
			update_stdout();
		}
		else if (UserEntry::Current().cmd == "reload")
		{
			UserEntry::Current().cmd = "restart";
			update_stdout();
		}
		else if (UserEntry::Current().cmd == "restart")
		{
			UserEntry::Current().cmd = "reload";
			update_stdout();
		}
		else if (UserEntry::Current().cmd == "exit")
		{
			UserEntry::Current().cmd = "edit";
			update_stdout();
		}
		else if (UserEntry::Current().cmd == "start")
		{
			UserEntry::Current().cmd = "stop";
			update_stdout();
		}
		else if (UserEntry::Current().cmd == "stop")
		{
			UserEntry::Current().cmd = "status";
			update_stdout();
		}
		else if (UserEntry::Current().cmd[0] == 'h' && UserEntry::Current().cmd.length() < 4)
		{
			UserEntry::Current().cmd = "help";
			update_stdout();
		}
		else if (UserEntry::Current().cmd[0] == 's' && UserEntry::Current().cmd.length() < 4)
		{
			UserEntry::Current().cmd = "status";
			update_stdout();
		}
		else if (UserEntry::Current().cmd[0] == 'e' && UserEntry::Current().cmd.length() < 4)
		{
			UserEntry::Current().cmd = "edit";
			update_stdout();
		}
		else if (UserEntry::Current().cmd[0] == 'r' && UserEntry::Current().cmd.length() < 6)
		{
			UserEntry::Current().cmd = "restart";
			update_stdout();
		}
}

void		get_program_name(vector<program> program_list)
{
	if (UserEntry::Current().auto_completion_get != program_list.size())
	{
		if (UserEntry::Current().cmd.find(' ') != -1)
			delete_name(program_list);
		UserEntry::Current().auto_completion_get++;
	}
	else
		UserEntry::Current().auto_completion_get = 0;
}