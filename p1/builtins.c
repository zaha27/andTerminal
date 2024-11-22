#include "header.h"

char *builtin_str[] = {
        "cd",
        "help",
        "exit",
        "pwd",
        "clear",
        "echo",
        "ls"
        //posibil de implementat in viitor: touch, rm, cat
};
int (*builtin_func[]) (char **) = {
        &andt_cd,
        &andt_help,
        &andt_exit,
        &andt_pwd,
        &andt_clear,
        &andt_echo,
        &andt_ls
};

int andt_num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}

int andt_cd(char **args) {
	if (args[1] == NULL) {
    		fprintf(stderr, "andt: trebuie să specifici un director\n");
	} else {
    		if (chdir(args[1]) != 0) {
        		perror("andt");
		}
	}
	return 1;
}
int andt_help(char **args) {
	printf("comenzi pe care le poti utiliza: \n");
	for(int i = 0; i < andt_num_builtins(); ++i) {
		printf("	%s\n", builtin_str[i]);
	}
	return 1;
}
int andt_exit(char **args) {
	return 0;
}
int andt_pwd(char **args) {
	char cwd[1024];
	if(getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("%s\n", cwd);
	} else {
	perror("andt");
	}
	return 1;
}
int andt_clear(char **args) {
	printf("\033[H\033[J");
	return 1;
}
int andt_echo(char **args) {
	for (int i = 1; args[i] != NULL; ++i) {
		printf("%s ", args[i]);
	}
	printf("\n");
	return 1;
}
int andt_ls(char **args) {
	struct dirent *entry;
	DIR *dp;

	char *path = args[1] ? args[1] : ".";
	dp = opendir(path);
    	if (dp == NULL) {
		perror("andt");
		return 1;
	}
	while ((entry = readdir(dp))) {
		printf("%s\n", entry->d_name);
	}
	
	closedir(dp);
	return 1;
}
int andt_execute(char **args) {
	if(args[0] == NULL) {
		return 1;
	}
	for(int i = 0; i < andt_num_builtins(); ++i) {
		if(strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}
}
