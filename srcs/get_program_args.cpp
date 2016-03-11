/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 02:18:17 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/29 02:18:19 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int			get_variable_state(string var)
{
	if (var == "executable_path")
		return (EXECUTABLE_PATH);
	else if (var == "executable_argument")
		return (EXECUTABLE_ARGUMENT);
	else if (var == "set_env")
		return (SET_ENV);
	else if (var == "working_dir")
		return (WORKING_DIR);
	else if (var == "auto_start")
		return (AUTO_START);
	else if (var == "set_umask")
		return (SET_UMASK);
	else if (var == "stderror_to_file")
		return (STDERROR_TO);
	else if (var == "stdout_to_file")
		return (STDOUT_TO);
	else if (var == "close_stderror")
		return (STDERROR_CLOSE);
	else if (var == "close_stdout")
		return (STDOUT_CLOSE);
	else if (var == "print_on_taskmaster")
		return (PRINT_ON_TASKMASTER);
	return (UNKNOWN_VARIABLE);
}

static program		check_variable_and_set(string line, program tmp, int position)
{
	vector<string>	args;
	int				i;

	i = 0;
	args = get_args(line, args, ';');
		switch (get_variable_state(args[0]))
		{
			case EXECUTABLE_PATH:
				if (args.size() == 3)
				{
					if (args[1].length())
					{
						args[1] = get_correct_path(args[1]);
						struct stat *executable_path;
						if (!(executable_path = (struct stat*)malloc(sizeof(struct stat))))
							return (tmp);
						if (lstat(args[1].c_str(), executable_path) < 0)
							print_error(position, "taskmaster: executable path invalid");
						if (S_ISDIR(executable_path->st_mode))
							print_error(-1, "taskmaster: executable path file set is a directory...");
						else if (S_ISLNK(executable_path->st_mode))
							print_error(-1, "taskmaster: executable path file set is a symoblic link...");
						if (!(executable_path->st_mode & S_IRUSR))
							print_error(-1, "taskmaster: permission denied on the executable path");
						tmp.executable_path = args[1];
					}
					else
						print_error(position, "taskmaster: executable path argument missing");
				}
				else
					print_error(position, "taskmaster: executable path can take only one argument");
			break;

			case EXECUTABLE_ARGUMENT:
				if (args.size() == 3)
				{
					if (args[1].length())
						tmp.executable_argument = args[1];
					else
						print_error(position, "taskmaster: executable_argument variable set but arguments are missing");
				}
				else
					print_error(position, "taskmaster: executable_argument bad syntax");
			break;

			case SET_ENV:
				if (args.size() == 4)
				{
					if (args[1].length() && args[2].length())
						tmp.env_to_set.push_back(args[1] + "," + args[2]);
					else
						print_error(position, "taskmaster: set_env missing arguments");
				}
				else
					print_error(position, "taskmaster: set_env bad syntax");
			break;

			case WORKING_DIR:
				if (args.size() == 3)
				{
					if (args[1].length())
					{
						struct stat *work_dir;
						if (!(work_dir = (struct stat*)malloc(sizeof(struct stat))))
							return (tmp);
						args[1] = get_correct_path(args[1]);
						if (lstat(args[1].c_str(), work_dir) < 0)
							print_error(position, "taskmaster: working dir path invalid");
						if (S_ISLNK(work_dir->st_mode))
							print_error(-1, "taskmaster: working dir path set is a symoblic link...");
						if (!(work_dir->st_mode & S_IRUSR))
							print_error(-1, "taskmaster: permission denied on the working dir path");
						if (S_ISDIR(work_dir->st_mode))
							tmp.working_dir = args[1];
					}
					else
						print_error(position, "taskmaster: working_dir variable set but argument are missing");
				}
				else
					print_error(position, "taskmaster: working_dir bad syntax");
			break;

			case AUTO_START:
				if (args[1] == "true")
					tmp.auto_start = true;
			break;

			case SET_UMASK:
				if (args.size() == 3)
				{
					if (args[1].length())
					{
						if (atoi(args[1].c_str()) <= 7777)
							tmp.set_umask = args[1];
						else
							print_error(position, "taskmaster: set_umask invalid permissions");
					}
					else
						print_error(position, "taskmaster: set_umask variable set but argument are missing");
				}
				else
					print_error(position, "taskmaster: set_umask bad syntax");
			break;

			case STDERROR_TO:
				if (args.size() == 3)
				{
					if (args[1].length())
						tmp.stderror_to_file = get_correct_path(args[1]);
					else
						print_error(position, "taskmaster: stderror_to_file variable set but argument are missing");
				}
				else
					print_error(position, "taskmaster: stderror_to_file bad syntax");
			break;

			case STDOUT_TO:
				if (args.size() == 3)
				{
					if (args[1].length())
						tmp.stdout_to_file = get_correct_path(args[1]);
					else
						print_error(position, "taskmaster: stdout_to_file variable set but argument are missing");
				}
				else
					print_error(position, "taskmaster: stdout_to_file bad syntax");
			break;

			case STDERROR_CLOSE:
				if (args.size() == 3)
				{
					if (args[1] == "true")
						tmp.close_stderror = true;
					else 
						tmp.close_stderror = false;
				}
				else
					print_error(position, "taskmaster: close_stdout bad syntax");
			break;

			case STDOUT_CLOSE:
				if (args.size() == 3)
				{
					if (args[1] == "true")
						tmp.close_stdout = true;
					else
						tmp.close_stdout = false;
				}
				else
					print_error(position, "taskmaster: close_stderror bad syntax");
			break;

			case PRINT_ON_TASKMASTER:
				if (args.size() == 3)
				{
					if (args[1] == "true")
						tmp.print_on_taskmaster = true;
					else
						tmp.print_on_taskmaster = false;
				}
				else
					print_error(position, "taskmaster: print_stdout bad syntax");
			break;

			default:
				if (args[0][0] != '/')
					print_error(position, "unknown variable " + args[0]);
			break;
		}
	return (tmp);
}

program		get_program_args(int start, vector<string> data, int end, string name)
{
	program tmp;

	name = name.substr(1, name.length());
	name = name.substr(0, (name.length() - 1));
	if (!name.length())
		print_error(start, "program name missing !");
	tmp.program_name = name;
	tmp.auto_start = false;
	tmp.print_on_taskmaster = false;
	tmp.pid = 0;
	while (start != end)
	{
		tmp = check_variable_and_set(data[start], tmp, (start + 2));
		start++;
	}
	return (tmp);
}