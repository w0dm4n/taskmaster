/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 02:18:17 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/29 02:18:19 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

program		get_program_args(int start, vector<string> data, int end, string name)
{
	program tmp;

	name = name.substr(1, name.length());
	name = name.substr(0, (name.length() - 1));
	if (!name.length())
		print_error(start, "program name missing !");
	tmp.program_name = name;
	while (start != end)
	{
		cout << data[start] << endl;
		start++;
	}
	return (tmp);
}