#include "../includes/minishell.h"

void ft_reset_norm(t_norm *n)
{
	n->i = 0;
	n->j = 0;
	n->k = 0;
	n->flg = 0;
	n->type = 's';
}

void copyUntilMatchingChar(char *line, char *str, t_norm *n)
{
	char c;

	c = line[n->i++];
	if (line[n->i] != c)
	{
		while (line[n->i] && line[n->i] != c)
		{
			if (c == '\'')
				n->type = 39;
			else if (c == '"')
				n->type = '"';
			str[n->j++] = line[n->i++];
		}
	}
	n->i++;
}

void processTokens(char *line, char *str, t_norm *n)
{
	while (line[n->i])
	{
		if (line[n->i] != 34 && line[n->i] != 39
			&& line[n->i] != ' ' && line[n->i] != '\t')
			str[n->j++] = line[n->i++];
		else if ((line[n->i] == 34 || line[n->i] == 39)
			&& ft_strchr(&line[n->i + 1], line[n->i]))
			copyUntilMatchingChar(line, str, n);
		else if ((line[n->i] == 34 || line[n->i] == 39)
			&& ft_strchr(&line[n->i + 1], line[n->i]) == NULL)
		{
			printf("Quote aperta!\n");
			exit(0);
		}
		if (line[n->i] == ' ' || line[n->i] == '\t')
		{
			n->i++;
			break ;
		}
	}
}

char *processInput(char *line, t_norm *n)
{
	char *str;
	char *ret;

	if (line[n->i] == '\0')
		return (NULL);
	str = ft_calloc(sizeof(char), (ft_strlen(line) + 1));
	n->j = 0;
	n->type = 's';
	processTokens(line, str, n);
	ret = ft_strdup(str);
	free(str);
	return (ret);
}

