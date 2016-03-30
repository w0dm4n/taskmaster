/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 02:11:41 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/26 02:11:42 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	config_infos::check_if_config_exist(void)
{
	struct stat *config;

	if (!(config = (struct stat*)malloc(sizeof(struct stat))))
		return (-1);
	if (lstat(this->config_file_name.c_str(), config) < 0)
	{
		print(this->config_file_name.c_str());
		print_error(-1, "taskmaster: invalid config file");
		return (0);
	}
	if (S_ISDIR(config->st_mode))
	{
		print_error(-1, "taskmaster: config file set is a directory...");
		return (0);
	}
	else if (S_ISLNK(config->st_mode))
	{
		print_error(-1, "taskmaster: config file set is a symoblic link...");
		return (0);
	}
	if (config->st_mode & S_IRUSR)
		return (1);
	else
	{
		print_error(-1, "taskmaster: permission denied on the config file");
		return (0);
	}
}

string delete_space(string &str)
{
    int first = str.find_first_not_of(' ');
    if (first == -1)
    	return (str);
    int last = str.find_last_not_of(' ');
   	if (last == -1)
   		return (str);
    return (str.substr(first, (last - first + 1)));
}

string delete_tab(string &str)
{
    int first = str.find_first_not_of('\t');
    if (first == -1)
    	return (str);
    int last = str.find_last_not_of('\t');
    if (last == -1)
    	return (str);
    return (str.substr(first, (last - first + 1)));
}

vector<program> config_infos::get_config_value(vector<program> program_list, vector<string> data)
{
	int		i = 0;
	bool	taskmaster_var = true;

	while (i != data.size())
	{
		if (data[i][0] == VAR_SYNTHAX && taskmaster_var)
			handle_taskmaster_var(data[i], i);
		else if (data[i][0] == NEW_PROGRAM_SYNTHAX)
		{
			program_list.push_back(get_new_program(data, i));
			taskmaster_var = false;
		}
		i++;
	}
	return (program_list);
}

vector<program> config_infos::read_config(vector<program> program_list)
{
	int			i;
	ifstream	flux(this->config_file_name);
	string		buff;
	vector<string> config_content;
	vector<string> clear_content;

	i = 0;
	if (flux)
	{
		while (getline(flux, buff))
			config_content.push_back(buff);
		if (!config_content.size())
		{
			print_error(-1, "taskmaster: empty configuration file");
			return (program_list);
		}
		if (config_content[0] != "[taskmaster]" ||
		 config_content[(config_content.size() - 1)] != "[end_taskmaster]")
		{
			print_error(-1, "taskmaster: header not present in the configuration ([taskmaster] ... [end_taskmaster])");
			return (program_list);
		}
		else
		{
			i++;
			while (i != (config_content.size() - 1))
			{
					config_content[i] = delete_space(config_content[i]);
					config_content[i] = delete_tab(config_content[i]);
					if (config_content[i][0] != '\0' && config_content[i][0] != '\t')
						clear_content.push_back(config_content[i]);
				i++;
			}
			return (this->get_config_value(program_list, clear_content));
		}
		flux.close();
	}
	else
		print_error(-1, "taskmaster: invalid configuration file");
	return (program_list);
}