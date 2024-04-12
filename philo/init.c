/*HEADER*/

#include "philo.h"

static size_t	ft_atot(const char *nptr)
{
	size_t	n;

	n = 0;
	while (*nptr == '+')
		nptr++;
	while (*nptr)
	{
		n *= 10;
		n += (*nptr++ -48) %10;
	}
	return (n);
}

static size_t	last_digit(size_t n, int flag)
{
	size_t	i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	if (flag)
		return (i);
	return (n);
}

static char	*ft_ttoa(size_t n)
{
	char	*n_a;
	size_t	len;

	len = last_digit(n, 1);
	n_a = malloc(len + 1);
	if (!n_a)
		return (NULL);
	n_a[len] = 0;
	while (len)
	{
		n_a[len - 1] = (n % 10) + 48;
		len--;
		n /= 10;
	}
	return (n_a);
}

static int	compare_nrs(const char *s1, const char *s2)
{
	while (*s1 == '+')
		s1++;
	return (ft_strncmp(s1, s2, ft_strlen(s1)));
}

int	check_overflow(size_t *args, char **argv, int argc, int i)
{
	int	j;
	char	*n_a;

	j = 0;
	if (argc == 5)
		args[4] = 0;
	while (i < argc)
		args[j++] = ft_atot(argv[i++]);
	if (!args[0])
		return (1);
	i = 1;
	j = 0;
	while (i < argc)
	{
		if (j != 4 && !args[j])
			return (printf("Error: invalid input\n"), 1);
		n_a = ft_ttoa(args[j++]);
		if (!n_a)
			return (1);
		if (compare_nrs(argv[i++], n_a))
			return (printf("Error: invalid input\n"), free(n_a), 1);
		free(n_a);
	}
	return (0);
}
