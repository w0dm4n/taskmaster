/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_program.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 02:26:33 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/09 02:26:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

vector<string> split(char *str, const char *delim)
{
    char *saveptr;
    char *token = strtok_r(str, delim, &saveptr);
    vector<string> result;

    while(token != NULL)
    {
        result.push_back(token);
        token = strtok_r(NULL, delim, &saveptr);
    }
    return (result);
}

char		**get_program_args(string executable_path, string args)
{
	char	**args_new;
	int		i = 0;
	int		i_2 = 0;
	char	**args_executable;

	if (!(args_new = (char**)malloc(sizeof(char*) * DEFAULT_ARGS_SIZE)))
		return (NULL);
	while (args_new[i])
	{
		args_new[i] = NULL;
		i++;
	}
	args_new[0] = strdup(executable_path.c_str());
	vector<string> hihi = split((char*)args.c_str(), " ");
	i_2 = 0;
	i = 1;
	while (i_2 != hihi.size())
	{
		args_new[i] = strdup(hihi[i_2].c_str()); 
		i++;
		i_2++;
	}
	return (args_new);
}

char		**get_program_env(vector<string> data)
{
	char	**env_new;
	int		i = 0;

	if (!(env_new = (char**)malloc(sizeof(char*) * 100000)))
		return (NULL);
	while (env_new[i])
	{
		env_new[i] = NULL;
		i++;
	}
	i = 0;
	while (i != data.size())
	{
		env_new[i] = strdup(data[i].c_str());
		i++;
	}
	env_new[i] = NULL;
	return (env_new);
}

vector<program>		handle_program(program to, int pos, vector<program> program_list)
{
	if (program_list[pos].pid != 0)
	{
		print("*** Program " + program_list[pos].program_name + " already started (type help restart).\n");
		return (program_list);
	}
	TaskMasterValue::Current().ExitProgramOnError = false;
	if (check_folder(to.working_dir, to.program_name))
	{
		add_in_logs(TaskMasterValue::Current().LogFilePath, "The program " + to.program_name + " was launched.");
		to.Environment_Data = TaskMasterValue::Current().DefaultEnvironment;
		if (to.env_to_set.size())
			to.GetEnvToSet(to.env_to_set);
		pid_t child;
		int child_status;
		int fd[2];
		pipe(fd);
		child = fork();
		if (child == 0)
		{
			pid_t process = getpid();
			print_nbr_fd(process, fd[1]);
			close(fd[1]);
			if (to.set_umask.length())
				umask((unsigned short)atoi(to.set_umask.c_str()));
			char	**env = get_program_env(to.Environment_Data);
			int i = 0;
			if (!to.print_on_taskmaster)
			{
				close (0);
				close (1);
				close (2);
			}
			chdir(to.working_dir.c_str());
			execve(to.executable_path.c_str(), get_program_args(to.executable_path, to.executable_argument), env);
			exit(0);
		}
		else
		{
			if (to.print_on_taskmaster)
				wait(&child_status);
			else
			{
				char program_pid[1024];
				int res = read(fd[0], program_pid, 1024);
				program_pid[res] = '\0';
				program_list[pos].pid = atoi(program_pid);
				print("*** Program " + to.program_name + " successfully launched (" + program_pid + ") ***\n");
				return (program_list);
			}
		}
	}
	else
	{
		add_in_logs(TaskMasterValue::Current().LogFilePath, "Can't launch the program " + to.program_name + " due to an invalid working dir");
		print("*** Can't launch the program " + to.program_name + "\n");
	}
	TaskMasterValue::Current().Errors = 0;
	return (program_list);
}