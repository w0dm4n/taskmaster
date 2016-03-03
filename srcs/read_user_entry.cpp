/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_user_entry.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 02:05:02 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/03 02:05:08 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include <termios.h>
#include <term.h>

int		get_ascii_value(string tmp_line)
{
	int i = 0;
	int value = 0;

	while (tmp_line.c_str()[i])
	{
		value += tmp_line.c_str()[i];
		i++;
	}
	return (value);
}

int		cursor_do(int to_print)
{
	write(1, &to_print, 1);
	return (to_print);
}

void	refresh_stdout()
{
	int tmp = UserEntry::Current().cursor;
	tputs(tgetstr((char*)"sc", NULL), 0, cursor_do);
	while (tmp)
	{
		tputs(tgetstr((char*)"le", NULL), 0, cursor_do);
		tmp--;
	}
	tputs(tgetstr((char*)"cd", NULL), 0, cursor_do);
	print(UserEntry::Current().cmd);
	tputs(tgetstr((char*)"rc", NULL), 0, cursor_do);
	tputs(tgetstr((char*)"nd", NULL), 0, cursor_do);
}

void	read_entry(string tmp_line)
{
	struct termios	*term;
	int				ascii_value;

	tmp_line.clear();
	if (!(term = (struct termios*)malloc(sizeof(struct termios))))
		return ;
	if (!(tgetent(NULL, getenv("TERM"))))
		return ;
	tcgetattr(0, term);
	term->c_lflag &= ~ICANON;
	term->c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, term);
	read(0, (void*)tmp_line.c_str(), 16);
	ascii_value = get_ascii_value(tmp_line);
	if (ascii_value == ENTRY)
		UserEntry::Current().end_cmd = true;
	if (ascii_value == ARROW_LEFT && UserEntry::Current().cursor)
	{
		tputs(tgetstr((char*)"le", NULL), 0, cursor_do);
		UserEntry::Current().cursor--;
	}
	if (ascii_value == ARROW_RIGHT && UserEntry::Current().cmd[(UserEntry::Current().cursor - 1)])
	{
		tputs(tgetstr((char*)"nd", NULL), 0, cursor_do);
		UserEntry::Current().cursor++;
	}
	if (ascii_value == BACKSPACE)
	{
		
	}
	if (ft_isprint(ascii_value))
	{
		if (UserEntry::Current().cmd[(UserEntry::Current().cursor + 1)])
		{
			UserEntry::Current().cmd.insert(UserEntry::Current().cursor, 1, tmp_line[0]);
			refresh_stdout();
			UserEntry::Current().cursor++;
		}
		else
		{
			print(tmp_line);
			UserEntry::Current().cmd += tmp_line[0];
			UserEntry::Current().cursor++;
		}
	}
}

void	reset_value()
{
	UserEntry::Current().end_cmd = false;
	UserEntry::Current().cursor = 0;
	UserEntry::Current().cmd.clear();
}

void	read_user_entry()
{
	string tmp_line;

	read_entry(tmp_line);
	if (UserEntry::Current().end_cmd)
	{
		print("\ntaskmaster> ");		
		reset_value();
	}
	read_user_entry();
}