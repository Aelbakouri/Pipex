// #include <stdio.h>
// #include <stdlib.h>

// char	*str_ndup(char *str, unsigned int n)
// {
// 	char				*s;
// 	unsigned int		i;

// 	i = 0;
// 	s = malloc(sizeof(char) * (n + 1));
// 	while (i < n)
// 		s[i++] = *str++;
// 	s[n] = 0;
// 	return (s);
// }

// char	**ft_split(char *str, char sep)
// {
// 	char	**tab;
// 	int		count;
// 	int		i;
// 	int		j;

// 	count = 0;
// 	j = -1;
// 	while (str[++j])
// 		if ((str[j] != sep && str[j + 1] == sep)
// 			|| (str[j] != sep && str[j + 1] == '\0'))
// 			count++;
// 	tab = malloc(sizeof(char *) * (count + 1));
// 	i = 0;
// 	while (i < count)
// 	{
// 		j = 0;
// 		while (*str && *str == sep)
// 			str++;
// 		while (str[j] && str[j] != sep)
// 			j++;
// 		tab[i++] = str_ndup(str, j);
// 		str = str + j;
// 	}
// 	tab[i] = NULL;
// 	return (tab);
// }
// int	str_ichr(char *str, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && str[i] != c)
// 		i++;
// 	if (str[i] == c)
// 		return (i);
// 	return (-1);
// }

// int main(int ac, char **av)
// {
// 	// int i = str_ichr(av[1], '/');
// 	// // if(!av[1][0])
// 	// // 	printf(":yes:\n");
// 	int i = 0;
// 	char **str = ft_split(av[1], ' ');

// 		printf("%s\n", str[i]);

// }
