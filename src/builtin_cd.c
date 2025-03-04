#include "../includes/mini.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


#include <stdlib.h> 
#include <string.h> 

char *get_env(const char *name)
{
    extern char **environ; // Declare the global environ array
    size_t name_len = strlen(name);
    int i = 0;

    // Iterate through the environment variables
    while (environ[i] != NULL)
    {
        // Check if the current variable matches the name followed by '='
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            // Return the value (the part after '=')
            return (environ[i] + name_len + 1);
        }
        i++;
    }
    return NULL; // Return NULL if the variable is not found
}
#include <stdlib.h> // For setenv

int set_env(const char *name, const char *value)
{
    // Set or update the environment variable using setenv
    if (setenv(name, value, 1) != 0)
    {
        perror("setenv"); // Print error message if setenv fails
        return 1; // Return error status
    }
    return 0; // Return success status
}

int ft_cd(char **argv)
{
    char *target_dir;    // Directory to change to
    char *old_pwd;       // Previous working directory
    char *new_pwd;       // New working directory
    int print_flag = 0;  // Flag to print new directory (for cd -)

    // Get the current working directory as OLDPWD
    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
    {
        perror("cd: getcwd failed");
        return 1;  // Error exit status
    }

    // Determine the target directory
    if (argv[1] == NULL)
    {
        // No argument: Use HOME
        target_dir = get_env("HOME");
        if (!target_dir)
        {
            fprintf(stderr, "cd: HOME not set\n");
            free(old_pwd);
            return 1;
        }
    }
    else if (argv[2] != NULL)
    {
        // Too many arguments
        fprintf(stderr, "cd: too many arguments\n");
        free(old_pwd);
        return 1;
    }
    else if (strcmp(argv[1], "-") == 0)
    {
        // cd -: Use OLDPWD
        target_dir = get_env("OLDPWD");
        if (!target_dir)
        {
            fprintf(stderr, "cd: OLDPWD not set\n");
            free(old_pwd);
            return 1;
        }
        print_flag = 1;  // Set flag to print new directory
    }
    else
    {
        // Use the provided argument as target directory
        target_dir = argv[1];
    }

    // Attempt to change to the target directory
    if (chdir(target_dir) != 0)
    {
        fprintf(stderr, "cd: %s: %s\n", target_dir, strerror(errno));
        free(old_pwd);
        return 1;
    }

    // Get the new current working directory
    new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
    {
        perror("cd: getcwd failed");
        // Directory changed successfully, but PWD update will be skipped
    }

    // Print new directory if cd - was used
    if (print_flag && new_pwd)
    {
        printf("%s\n", new_pwd);
    }

    // Update environment variables
    set_env("OLDPWD", old_pwd);
    free(old_pwd);  // Clean up memory
    if (new_pwd)
    {
        set_env("PWD", new_pwd);
        free(new_pwd);  // Clean up memory
    }

    return 0;  // Success
}


// int main(int argc, char *argv[])
// {
//     // Test 1: No argument should take us to HOME
//     printf("Testing cd with no argument (should go to HOME):\n");
//     char *no_args[] = { "cd", NULL };
//     ft_cd(no_args);

//     // Test 2: cd to a valid directory
//     printf("\nTesting cd with a valid directory (/tmp):\n");
//     char *valid_dir[] = { "cd", "/tmp", NULL };
//     ft_cd(valid_dir);

//     // Test 3: cd to OLDPWD (using -)
//     printf("\nTesting cd with - (should go to OLDPWD):\n");
//     char *cd_dash[] = { "cd", "-", NULL };
//     ft_cd(cd_dash);

//     // Test 4: cd with a non-existent directory (should print error)
//     printf("\nTesting cd with a non-existent directory (/nonexistentdir):\n");
//     char *invalid_dir[] = { "cd", "/nonexistentdir", NULL };
//     ft_cd(invalid_dir);

//     return 0;
// }

