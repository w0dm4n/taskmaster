/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_program.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 01:00:10 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/29 01:00:56 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

string		get_function_name(string data)
{
	string	tmp;
	int 	i;

	i = 0;
	data = data.substr(1, data.length());
	while (data[i] && data[i] != '{')
	{
		tmp += data[i];
		i++;
	}
	return (tmp);
}

string		get_name(string data)
{
	string	tmp;
	int		i;

	i = 0;
	data = data.substr(1, data.length());
	while (data[i] && data[i] != '{')
		i++;
	while (data[i])
	{
		tmp += data[i];
		i++;
	}
	return (tmp);
}

int			get_function_end(vector<string> data, int i)
{
	while (i != data.size())
	{
		if (data[i] == ")")
			return (i);
		i++;
	}
	return (-1);
}

program		get_new_program(vector<string> data, int i)
{
	program 	new_program;
	string		function_name;
	string		name;
	int			function_end;

	function_name = get_function_name(data[i]);
	if (!function_name.length())
		print_error((i + 2), "missing function name");
	if (function_name == "new_program")
	{
		name = get_name(data[i]);
		function_end = get_function_end(data, i);
		if (name[0] == '{' && name[(name.length() - 1)] == '}')
		{
			if (data[i + 1] != "(")
				print_error((i + 3), "missing ( for the function opening");
			if (function_end == -1)
			{
				TaskMasterValue::Current().ExitProgramOnError = true;
				print_error((i + 2), "missing ) for the function end");
			}
			new_program = get_program_args((i + 2), data, function_end, name);
		}
		else
			print_error((i + 2), "bad syntax near " + name);
	}
	else
		print_error((i + 2), "unknown function " + function_name);
	return (new_program);
}