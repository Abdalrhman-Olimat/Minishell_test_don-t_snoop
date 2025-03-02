#include"../includes/mini.h"

int ft_pwd(void)
{
    char path[PATH_MAX];

    if (getcwd(path, sizeof(path)) == NULL)
    {
        perror("getcwd failed");
        return 1;
    }
    printf("%s\n", path);
    return 0;
}
