#include "shell.h"

/**
 * customExit - exits the shell
 * @info: Structure containing potential arguments.
 * 
 * Returns: Exits with a given exit status
 *          (0) if info->argv[0] != "exit"
 */
int customExit(info_t *info)
{
    int exitStatus;

    if (info->argv[1])  
    {
        exitStatus = customAtoi(info->argv[1]);
        if (exitStatus == -1)
        {
            info->status = 2;
            printError(info, "Illegal number: ");
            eputs(info->argv[1]);
            eputchar('\n');
            return 1;
        }
        info->err_num = exitStatus;
        return -2;
    }
    info->err_num = -1;
    return -2;
}

/**
 * customCd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * 
 * Returns: Always 0
 */
int customCd(info_t *info)
{
    char *currentDir, *newDir, buffer[1024];
    int chdirResult;

    currentDir = getcwd(buffer, 1024);
    if (!currentDir)
        puts("TODO: >>getcwd failure emsg here<<\n");
    
    if (!info->argv[1])
    {
        newDir = getenv(info, "HOME=");
        if (!newDir)
            chdirResult = chdir((newDir = getenv(info, "PWD=")) ? newDir : "/");
        else
            chdirResult = chdir(newDir);
    }
    else if (customStrcmp(info->argv[1], "-") == 0)
    {
        if (!getenv(info, "OLDPWD="))
        {
            puts(currentDir);
            putchar('\n');
            return 1;
        }
        puts(getenv(info, "OLDPWD="));
        chdirResult = chdir((newDir = getenv(info, "OLDPWD=")) ? newDir : "/");
    }
    else
        chdirResult = chdir(info->argv[1]);
    
    if (chdirResult == -1)
    {
        printError(info, "can't cd to ");
        eputs(info->argv[1]);
        eputchar('\n');
    }
    else
    {
        setenv(info, "OLDPWD", getenv(info, "PWD="));
        setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return 0;
}

/**
 * customHelp - prints help information
 * @info: Structure containing potential arguments.
 * 
 * Returns: Always 0
 */
int customHelp(info_t *info)
{
    char **argArray;

    argArray = info->argv;
    puts("Help is available but not yet implemented.\n");
    
    if (0)
        puts(*argArray); /* temp att_unused workaround */
    
    return 0;
}
