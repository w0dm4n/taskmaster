/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 00:10:54 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/26 00:10:55 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <all.h>

int		main(int argc, char **argv)
{
	int i;
	int	args;

	i = 0;
	args = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			args++;
			cout << "args\n";
		}
		else
		{
			if (args)
			{
				stderr << "taskmaster : bad syntax\n";
				return (-1);
			}
			else
			{
				cout << "configuration file\n"
			}
		}
	}
	return (0);
}
