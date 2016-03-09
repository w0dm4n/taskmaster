/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_program.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 02:26:33 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/09 02:26:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		handle_program(program to)
{
	add_in_logs(TaskMasterValue::Current().LogFilePath, "The program " + to.program_name + " was launched.");
	print("START : " + to.program_name + "\n");
}