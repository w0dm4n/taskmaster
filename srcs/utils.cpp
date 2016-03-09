/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 22:30:17 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/09 22:30:18 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		check_folder(string folder, string program_name)
{
	struct stat *folder_stat;

	if (!(folder_stat = (struct stat*)malloc(sizeof(struct stat))))
		return (-1);
	if (lstat(folder.c_str(), folder_stat) < 0)
	{
		print_error(-1, "--- Invalid working directory for the program " + program_name + "\n");
		return (0);
	}
	else if (S_ISDIR(folder_stat->st_mode))
		if (folder_stat->st_mode & S_IRUSR)
			return (1);
	print_error(-1, "--- Invalid working directory for the program " + program_name + "\n");
	return (0);
}

vector<string> get_environment_vector(char **env)
{
	int				i;
	vector<string> new_env;

	while (env[i])
	{
		new_env.push_back(env[i]);
		i++;
	}
	return (new_env);
}