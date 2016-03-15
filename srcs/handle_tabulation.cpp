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

void		get_program_name()
{
	print("SLT");
}