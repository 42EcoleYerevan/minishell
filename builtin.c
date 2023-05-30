#include <unistd.h>
#include <limits.h>

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

void    ft_pwd()
{
    char    path[PATH_MAX];

    if (getcwd(path, PATH_MAX))
    {
        ft_putstr_fd(path, 1);
        write(1, "\n", 1);
    }
}

void	ft_echo(int fd, char **args, int count, int n)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_putstr_fd(args[i], fd);
		i++;
	}
	if (!n)
		write(fd, "\n", 1);
}