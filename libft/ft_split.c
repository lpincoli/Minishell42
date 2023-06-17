/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocastell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:37:01 by ocastell          #+#    #+#             */
/*   Updated: 2022/10/11 10:37:07 by ocastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static	char	*ft_strlength(char const *str, char c, int i)
{
	int		j;
	char	*string;

	j = 0;
	string = (char *)malloc((ft_strlen(str) + 1) * sizeof(*string));
	if (!string)
		return (NULL);
	while (str[i] == c)
		i++;
	while (str[i])
	{
		*string = str[i];
		if (str[i + 1] == c || str[i + 1] == '\0')
		{
			string++;
			j++;
			*string = '\0';
			return (string - j);
		}
		string++;
		j++;
		i++;
	}
	return (0);
}

static	int	str_count(char const *str, char c)
{
	int	i;
	int	count;
	int	def;

	i = 0;
	count = 0;
	def = 1;
	while (str[i])
	{
		if (str[i] == c && def == 0)
		{
			def = 1;
		}
		if (str[i] != c && def == 1)
		{
			count++;
			def = 0;
		}
		i++;
	}
	return (count);
}

static	char	**creat_splits(char const *s, char **split, char c)
{
	int		i;
	int		len;
	int		str_num;
	char	*string;
	int		count;

	i = 0;
	count = 0;
	str_num = str_count(s, c);
	while (i < str_num)
	{
		while (s[count] == c && s[count])
			count++;
		string = ft_strlength(s, c, count);
		len = ft_strlen(string);
		split[i] = (char *)malloc(len + 1);
		if (!split[i])
			return (NULL);
		ft_strcpy(split[i], string);
		count += len;
		i++;
		free(string);
		string = NULL;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	char	**flip;
	int		str_num;

	str_num = str_count(s, c);
	split = (char **)malloc((str_num + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[str_num] = NULL;
	split = creat_splits(s, split, c);
	if (creat_splits(s, split, c) == NULL)
	{
		flip = split;
		while (*flip)
		{
			free (*flip);
			flip++;
		}
		free (split);
		split = NULL;
	}
	return (split);
}
