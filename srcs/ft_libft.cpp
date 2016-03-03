/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 06:16:15 by frmarinh          #+#    #+#             */
/*   Updated: 2016/02/22 14:03:45 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "all.h"

int				ft_strlen(const char *str)
{
	int i;

	i = 0;
	 while (str[i])
	 	i++;
	 return (i);
}

static char		*ft_strnew(size_t size)
{
	void	*tmp;
	int		i;
	char	*omg;

	i = 0;
	if (!(tmp = malloc(sizeof(char) * size + 1)))
		return (NULL);
	omg = (char*)tmp;
	while (i != size)
	{
		omg[i] = '\0';
		i++; 
	}
	return (omg);
}


static int		where(char const *s, int pos, char c)
{
	int i;

	i = 0;
	while (s[pos])
	{
		if (pos == 0)
			if (s[pos] != c)
				return (pos);
		if (s[pos] == c)
		{
			i++;
			break ;
		}
		pos++;
	}
	return ((pos + i));
}

static int		char_nbr(char const *s, char c)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (s[i])
	{
		if (s[i] == c || s[i + 1] == '\0')
			nbr++;
		i++;
	}
	return (nbr);
}

static int		next(char const *s, int pos, char c)
{
	int i;

	i = 0;
	while (s[pos])
	{
		if (s[pos] != c)
			pos++;
		else
			break ;
		i++;
	}
	return (pos);
}

static char		*get_from(char const *s, int start, int end)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(tmp = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (start < end)
	{
		tmp[i] = s[start];
		i++;
		start++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char			**ft_strsplit(char const *s, char c)
{
	int		pos;
	int		nbr;
	char	*res;
	char	**tmp;
	void	*array;
	int		occurence;

	pos = 0;
	occurence = 0;
	if (!(res = ft_strnew(ft_strlen(s))) || !s)
		return (NULL);
	nbr = char_nbr(s, c) + 1;
	if (!(array = malloc(sizeof(char*) * 8192)))
		return (NULL);
	tmp = (char**)array;
	while (nbr-- > 0)
	{
		pos = where(s, pos, c);
		res = get_from(s, pos, next(s, pos, c));
		if (res[0])
			tmp[occurence++] = res;
		if (pos == 0)
			pos++;
	}
	tmp[occurence] = NULL;
	return (tmp);
}

void			print(string str)
{
	const char *string = str.c_str();
	int	 i = 0;

	while (string[i])
	{
		write(1, &string[i], 1);
		i++;
	}
}

int				ft_isprint(int c)
{
 	if (c >= 32 && c <= 126)
 		return (1);
 	return (0);
 }

void			ft_putchar(char c)
{
	write(1, &c, 1);
}

void			print_nbr(int nbr)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		print_nbr(nbr / 10);
		print_nbr(nbr % 10);
	}
	else
		ft_putchar(nbr + 48);
}
