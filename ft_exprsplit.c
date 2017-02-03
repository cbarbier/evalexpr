/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exprsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 12:31:51 by cbarbier          #+#    #+#             */
/*   Updated: 2016/07/12 14:18:23 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_beta/libft.h"

static int 		nb_words(char **aptr, char c, int nbwords)
{
	char		*ptr;

	ptr = *aptr;
	while (*ptr)
	{
		if (*ptr == '(' || *ptr == ')')
		{
			if (!nbwords)
				*aptr = ptr;
			ptr++;
			nbwords++;
		}
		else if (*ptr != c)
		{
			if (!nbwords)
				*aptr = ptr;
			while (*ptr && *ptr != c && *ptr != ')')
				ptr++;
			nbwords++;
		}
		else
			ptr++;
	}
	return (nbwords);
}

static	unsigned int	add_word(char *ptr, char **res, char c)
{
	unsigned int	index;

	index = 0;
	if (ptr[index] == '(' || ptr[index] == ')')
		index++;
	else
	{
		while (ptr[index] != c && ptr[index]
			&& ptr[index] != '(' && ptr[index] != ')')
			index++;
	}
	*res = ft_strsub(ptr, 0, index);
	while (ptr[index] && ptr[index] == c) 
		index++;
	return (index);
}

char			**ft_exprsplit(char const *s, char c)
{
	char	**res;
	char	*ptr;
	unsigned int	i_res;
	unsigned int	nb;

	ptr = (char *)s;
	nb = nb_words(&ptr, c, 0);
	if (!s || !c || !nb)
		return (NULL);
	if (!(res = (char **)malloc((nb + 1) * sizeof(char *))))
		return (NULL);
	i_res = 0;
	while (i_res < nb)
	{
		ptr += add_word(ptr, &res[i_res], c);
		i_res++;
	}
	res[i_res] = NULL;
	return (res);
}
