/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 00:16:18 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/26 00:17:08 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/stat.h> 
# define VAR_SYNTHAX '%'
# define NEW_PROGRAM_SYNTHAX '#'
# define LOG_FILE 0
# define UNKNOWN_VARIABLE 666
# define EXECUTABLE_PATH 10
# define EXECUTABLE_ARGUMENT 11
# define SET_ENV 12
# define WORKING_DIR 13
# define AUTO_START 14
# define SET_UMASK 15
# define STDERROR_TO 16
# define STDOUT_TO 17
# define STDERROR_CLOSE 18
# define STDOUT_CLOSE 19
using namespace std;
class program
{
	public:
	string			program_name;
	string			executable_path;
	string			executable_argument;
	vector<string>	env_to_set;
	bool			auto_start;
	string			exit_signal_to_set;
	string  		working_dir;
	string			set_umask;
	string			stderror_to_file;
	string			stdout_to_file;
	bool			close_stdout;
	bool			close_stderror;
};

class TaskMasterValue
{
	public:
    static TaskMasterValue &Current()
    {
        static TaskMasterValue Singleton;
        return Singleton;
    }
    string LogFilePath;
    bool LogFilePathExist;
};

class config_infos
{
	public:
	int check_if_config_exist();
	vector<program> read_config(vector<program> program_list);
	vector<program> get_config_value(vector<program> program_list, vector<string> data);
	string config_file_name;
};

void	handle_config(string config_name);
void	handle_taskmaster_var(string line, int position);
char	**ft_strsplit(char const *s, char c);
int		ft_strlen(const char *str);
void	print_error(int position, string message);
program		get_new_program(vector<string> data, int i);
vector<string> get_args(string line, vector<string> args, char delimiter);
program		get_program_args(int start, vector<string> data, int end, string name);
string 		get_correct_path(string path);

/*
				vector<program> program_list;
				program new_prog;
				new_prog.program_name = "test";
				program_list.push_back(new_prog);
				cout << program_list[0].program_name;
*/
#endif
