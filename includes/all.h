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
# define VAR_SYNTHAX '%'
using namespace std;
class program
{
	public:
	string	program_name;
	string	executable_path;
	string	executable_argument;
	string	env_to_set;
	int		auto_start;
	string	exit_signal_to_set;
	string	stderror;
	string  stdout;
	string  working_dir;
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

/*
				vector<program> program_list;
				program new_prog;
				new_prog.program_name = "test";
				program_list.push_back(new_prog);
				cout << program_list[0].program_name;
*/
#endif
