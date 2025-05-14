#include "../includes/mini.h"

t_command_data **big_malloc(t_shell *shell, int i)
{
	t_command_data **cmds;

	shell->analyzing_data.cmds_count = count_max_commands(shell);
	printf("shell->analyzing_data.cmds_count = %d\n", shell->analyzing_data.cmds_count);

}
