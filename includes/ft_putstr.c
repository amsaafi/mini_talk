#include "../mini_talk.h"

void	ft_putstr(char c, int fd)
{
	write(fd, &c, 1);
}
