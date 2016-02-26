/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_taskmaster_var.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 04:06:36 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/26 04:06:37 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	handle_taskmaster_var(string line, int position)
{
	vector<string> args;
	string	args_delimiter = ";";
	string	tmp;
	string	token;
	int		i = 0;
	position += 2;

	line = line.substr(1, line.length());
	tmp = line;
	while (token != tmp)
	{
		token = tmp.substr(0, tmp.find_first_of(args_delimiter));
		tmp = tmp.substr(tmp.find_first_of(args_delimiter) + 1);
		args.push_back(token);
	}
	if (args.size())
	{
		if (args[0] == "taskmaster_log_file")
		{

		}
		else
		{
			cerr << "taskmaster configuration: error on the line " << position << ": "<< endl;
			cerr << "Unknown variable " << args[0] << endl;
		}
	}
	else
	{
		cerr << "taskmaster configuration: error on the line " << position << ": "<< endl;
		cerr << "missing or invalid variable name" << endl;
	}
}