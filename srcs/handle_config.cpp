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
	/*int i = 0;
	int env = 0;
	while (i != program_list.size())
	{
		if (program_list[i].auto_start && program_list[i].env_to_set.size())
		{
			while (env != program_list[i].env_to_set.size())
			{
				cout << program_list[i].env_to_set[env] << endl;
				env++;
			}
		}
		i++;
	}*/
}