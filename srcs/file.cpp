/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 17:42:05 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/24 17:42:06 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

class file
{
	public: 
	bool overwrite_in_file(void);
	string get_file_content(void);
	bool add_in_file(void);
	string file_name;
	string data_to_write;
};

bool	file::overwrite_in_file()
{
	ofstream file_flux(this->file_name);
	if (file_flux)
	{
		file_flux << this->data_to_write;
		return (true);
	}
	else
		return (false);
	file_flux.close();
}

string	file::get_file_content()
{
	ifstream file_flux(this->file_name);
	string buff;
	string file_content;

	if (file_flux)
		while (getline(file_flux, buff))
		{
			file_content += buff;
			file_content += "\n";
		}
	file_flux.close();
	return (file_content);
}

bool	file::add_in_file() : file_name("LOL")
{
	string current_data;

	current_data = this->get_file_content();
	if (!current_data.empty())
	{
		current_data += this->data_to_write;
		this->data_to_write = current_data;
		this->overwrite_in_file();
		return (true);
	}
	else
		return (false);
}

int		main(int argc, char **argv)
{
	file *handle_file;

	if (!argv[1] || !argv[2])
	{
		cout << "error: arguments missing !\n";
		return (-1);
	}
	handle_file = new file;
	handle_file->file_name = argv[1];
	handle_file->data_to_write = argv[2];
	if (handle_file->add_in_file())
		cout << handle_file->get_file_content();
	else if (handle_file->overwrite_in_file())
		cout << handle_file->get_file_content();
	else
		cout << "can't write on the file\n";
	file *copy = handle_file;
	delete handle_file;
	cout << handle_file->file_name;
	return (0);
}
