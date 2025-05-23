#include "../includes/mini.h"

int	close_wth_free(size_t risgo_vsnot ,t_command_data **cmds, int fd)
{
	if (risgo_vsnot)
	{
		close(fd);
		free_big_malloc_cmds(0, cmds, -1);
		return (0);
	}
}