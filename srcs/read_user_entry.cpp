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

void	delete_x_characters(int to_del)
{
	tputs(tgoto((char*)tgetstr((char*)"DC", NULL), 0, to_del), 1, cursor_do);
}

void	delete_current_and_print_history(string to_set, string tmp)
{
	int i = 0;

	if (!UserEntry::Current().cmd.length() && !tmp.length())
	{
		UserEntry::Current().cursor = 0;
		while (i != to_set.length())
		{
			write(1, &to_set[i], 1);
			i++;
			UserEntry::Current().cursor++;
		}
		UserEntry::Current().cmd.clear();
		UserEntry::Current().cmd = to_set;
	}
	else
	{
		while (i != UserEntry::Current().cmd.length())
		{
			tputs(tgetstr((char*)"le", NULL), 0, cursor_do);
			i++;
		}
		tputs(tgetstr((char*)"cd", NULL), 0, cursor_do);
		UserEntry::Current().cursor = 0;
		i = 0;
		while (i != to_set.length())
		{
			write(1, &to_set[i], 1);
			i++;
			UserEntry::Current().cursor++;
		}
		UserEntry::Current().cmd.clear();
		UserEntry::Current().cmd = to_set;
	}
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
	else if (ascii_value == ARROW_LEFT && UserEntry::Current().cursor)
	{
		tputs(tgetstr((char*)"le", NULL), 0, cursor_do);
		UserEntry::Current().cursor--;
	}
	else if (ascii_value == ARROW_RIGHT && (UserEntry::Current().cmd[(UserEntry::Current().cursor + 1)]
		|| UserEntry::Current().cursor == (UserEntry::Current().cmd.length() - 1)))
	{
		tputs(tgetstr((char*)"nd", NULL), 0, cursor_do);
		UserEntry::Current().cursor++;
	}
	else if (ascii_value == BACKSPACE && (UserEntry::Current().cmd[(UserEntry::Current().cursor - 1)])
		&& UserEntry::Current().cursor >= 1)
	{
		UserEntry::Current().cmd.erase((UserEntry::Current().cursor - 1), 1);
		int tmp = UserEntry::Current().cursor;
		tputs(tgetstr((char*)"sc", NULL), 0, cursor_do);
		while (UserEntry::Current().cursor >= 1)
		{
			tputs(tgetstr((char*)"le", NULL), 0, cursor_do);
			UserEntry::Current().cursor--;
		}
		if (!UserEntry::Current().cmd.length())
			delete_x_characters(1);
		else
			delete_x_characters(UserEntry::Current().cmd.length());
		print(UserEntry::Current().cmd);
		UserEntry::Current().cursor = tmp;
		tputs(tgetstr((char*)"rc", NULL), 0, cursor_do);
		tputs(tgetstr((char*)"le", NULL), 0, cursor_do);
		UserEntry::Current().cursor--;
		if (!UserEntry::Current().cmd.length())
			UserEntry::Current().cursor = 0;
	}
	else if (ascii_value == CLEAR_SCREEN)
	{
		print(TO_PRINT_FOR_CLEAR);
		tputs(tgoto((char*)tgetstr((char*)"cm", NULL), 0, 0), 1, cursor_do);
		print("taskmaster> ");
		print(UserEntry::Current().cmd);
	}
	else if (ascii_value == ARROW_UP)
	{
		if (!UserEntry::Current().cmd_history.size() || !UserEntry::Current().history_pos)
			return ;
		if (UserEntry::Current().cmd_history[(UserEntry::Current().history_pos - 1)].length()
			&& UserEntry::Current().history_pos <= UserEntry::Current().cmd_history.size())
		{
			UserEntry::Current().history_pos--;
			delete_current_and_print_history(UserEntry::Current().cmd_history[UserEntry::Current().history_pos], tmp_line);
		}
	}
	else if (ascii_value == ARROW_DOWN)
	{
		if (!UserEntry::Current().cmd_history.size())
			return ;
		if ((UserEntry::Current().history_pos + 1) > (UserEntry::Current().cmd_history.size() - 1))
			return ;
		if (UserEntry::Current().cmd_history[(UserEntry::Current().history_pos + 1)].length() 
			&& UserEntry::Current().history_pos <= UserEntry::Current().cmd_history.size())
		{
			UserEntry::Current().history_pos++;
			delete_current_and_print_history(UserEntry::Current().cmd_history[UserEntry::Current().history_pos], tmp_line);
		}
	}
	else if (ft_isprint(ascii_value))
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

void	handle_history()
{
	if (UserEntry::Current().cmd.length())
	{
		UserEntry::Current().cmd_history.push_back(UserEntry::Current().cmd);
		UserEntry::Current().history_pos = UserEntry::Current().cmd_history.size();
	}
}

void	reset_value()
{
	int i = 0;
	UserEntry::Current().end_cmd = false;
	UserEntry::Current().cursor = 0;
	while (UserEntry::Current().cmd[i])
	{
		UserEntry::Current().cmd[i] = '\0';
		i++;
	}
	UserEntry::Current().cmd.clear();
}

string trim(const string &s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;

    string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return (string(it, rit.base()));
}

void	read_user_entry(vector<program> program_list)
{
	string tmp_line;

	read_entry(tmp_line);
	if (UserEntry::Current().end_cmd)
	{
		UserEntry::Current().cmd = trim(UserEntry::Current().cmd);
		if (UserEntry::Current().cmd.length())
			handle_cmd(UserEntry::Current().cmd, program_list);
		print("\ntaskmaster> ");		
		handle_history();
		reset_value();
	}
	read_user_entry(program_list);
}