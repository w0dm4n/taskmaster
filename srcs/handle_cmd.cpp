/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 04:24:43 by frmarinh          #+#    #+#             */
/*   Updated: 2016/03/08 04:24:45 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		handle_cmd(string cmd, vector<program> progam_list)
{
	size_t test = cmd.find(" ");
	for (unsigned i=0; i<cmd.length(); ++i)
 	 {
   	 	print_nbr(cmd.at(i));
 	 }
}