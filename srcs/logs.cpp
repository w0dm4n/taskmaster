/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 04:39:53 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/09 04:39:54 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include <fcntl.h>

void		add_in_logs(string file_path, string content)
{
	string logs_content;
	char buffer[1024];
	int fd = 0;
	int res = 0;

	fd = open(file_path.c_str(), O_RDWR);
	if (fd == -1)
	{
		close (fd);
		if ((fd = open(file_path.c_str(), O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
			print_error(-1, "Can't open the log file !");
		else
		{
			close(fd);
			fd = open(file_path.c_str(), O_RDWR);
		}
	}
	content += "\n"; // ADD [DAYS-HOUR] IN FRONT OF THE MSG
	while ((res = read(fd, buffer, 1024)) > 0)
	{
		buffer[res] = '\0';
		logs_content += buffer;
	}
	logs_content += content;
	write(fd, content.c_str(), strlen(content.c_str()));
	close(fd);
}