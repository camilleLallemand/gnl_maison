/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/12/15 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(char *s)
{
	size_t	i;
	char	*cp;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	cp = malloc(sizeof(char) * (i + 1));
	if (!cp)
		return (NULL);
	i = 0;
	while (s[i])
	{
		cp[i] = s[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}

int	find_nl(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (s[i] == '\n');
}

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*new_res(char *buffer, char *res)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = ft_strlen(res);
	j = ft_strlen(buffer);
	tmp = malloc(sizeof(char) * (i + j + 1));
	if (!tmp)
		return (free(res), NULL);
	i = 0;
	while (res[i])
	{
		tmp[i] = res[i];
		i++;
	}
	j = 0;
	while (buffer[j])
	{
		tmp[i + j] = buffer[j];
		j++;
	}
	tmp[i + j] = '\0';
	free(res);
	return (tmp);
}
