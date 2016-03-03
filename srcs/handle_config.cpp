/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_config.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 03:03:15 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/26 03:03:16 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	handle_config(string config_name)
{
	config_infos config;
	vector<program> program_list;

	config.config_file_name = config_name;
	if (config.check_if_config_exist())
		program_list = config.read_config(program_list);
	if (check_all_program(program_list))
	{
		print("taskmaster> ");
		read_user_entry();
	}
	/*int i = 0;
	int env = 0;
	while (i != program_list.size())
	{
		if (program_list[i].program_name.length())
			cout << "PROGAM TO START NAME : " << program_list[i].program_name << endl;
		if (program_list[i].executable_path.length())
			cout << "EXECUTABLE_PATH : " << program_list[i].executable_path << endl;
		if (program_list[i].executable_argument.length())
			cout << "EXECUTABLE_ARGUMENT : " << program_list[i].executable_argument << endl;
		if (program_list[i].auto_start && program_list[i].env_to_set.size())
		{
			cout << "ENVIRONMENT VARIABLES TO SET : " << endl;
			while (env != program_list[i].env_to_set.size())
			{
				cout << program_list[i].env_to_set[env] << endl;
				env++;
			}
		}
		cout << endl << endl;
		i++;
		env = 0;
	}*/
}