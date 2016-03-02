/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/28 22:46:39 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/28 22:46:41 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	print_error(int position, string message)
{
	if (position != -1)
		cerr << "taskmaster configuration: error at the line " << position << ": "<< endl;
	cerr << message << endl;
	exit(0);
}