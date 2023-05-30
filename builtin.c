#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

void	ft_echo(int fd, char **args, int count, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putstr_fd(args[i], fd);
		i++;
	}
	if (!n)
		write(fd, "\n", 1);
}