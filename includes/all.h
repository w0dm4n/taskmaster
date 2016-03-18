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
#include <signal.h>
#include <errno.h>
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
# define PRINT_ON_TASKMASTER 20
# define EXIT_SIGNAL 21
# define AUTO_RESTART 22
# define START_TIME 23
# define STOP_TIME 24
# define EXIT_CODE 25
# define WHITE_COLOR "\e[1;37m"
# define ENTRY 10
# define BACKSPACE 127
# define ARROW_UP 183
# define ARROW_DOWN 184
# define ARROW_RIGHT 185
# define ARROW_LEFT 186
# define CLEAR_SCREEN 12
# define TABULATION 9
# define TO_PRINT_FOR_CLEAR "\033[2J"
# define DEFAULT_ARGS_SIZE 1024
# define DEFAULT_ENV_SIZE 1024
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
	bool			print_on_taskmaster;
	bool			close_stdout;
	bool			close_stderror;
	bool			auto_restart;
	int				start_time;
	int				stop_time;
	vector<string>	Environment_Data;
	int				pid;
	int				exit_code;
	int				time_for_restart;
	void		   GetEnvToSet(vector<string> env_to_set);
	void		   FindAndSet(char *variable, char *value);
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
    string ConfigFileName;
    bool ExitProgramOnError;
    int Errors;
    vector<string> DefaultEnvironment;
};

class UserEntry
{
	public:
	static UserEntry &Current()
	{
		static UserEntry Singleton;
		return Singleton;
	}
	bool end_cmd;
	string cmd;
	int cursor;
	vector<string> cmd_history;
	int history_pos;
	int auto_completion_get;
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
bool		check_all_program(vector<program> program_list);
void		read_user_entry(vector<program> program_list);
void		print(string str);
void		print_fd(string str, int fd);
int			ft_isprint(int c);
void		print_nbr(int nbr);
vector<program>		handle_cmd(string cmd, vector<program> program_list);
vector<program>		check_cmd(string cmd, vector<string> cmd_args, vector<program> program_list);
void		get_help_cmd(vector<string> args);
int			ft_is_all_print(char *str);
void		get_process_status(vector<string> args, vector<program> program_list);
vector<program>		reload(vector<string> args, vector<program> program_list);
vector<program>		start_program(vector<string> args, vector<program> program_list);
vector<program>		handle_program(program to, int pos, vector<program> program_list);
void				add_in_logs(string file_path, string content);
int					check_folder(string folder, string program_name);
vector<string> 		get_environment_vector(char **env);
vector<program> 	stop_program(vector<string> args, vector<program> program_list);
void				print_nbr_fd(int nbr, int fd);
vector<program>		restart_program(vector<string> args, vector<program> program_list);
int					ft_isdigit(int c);
vector<program>		edit(vector<string> args, vector<program> program_list);
program				check_variable_and_set(string line, program tmp, int position);
void				get_command();
int					cursor_do(int to_print);
void				refresh_stdout();
void				get_program_name(vector<program> program_list);
#endif
