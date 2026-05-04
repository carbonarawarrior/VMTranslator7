#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "write.h"
#define VMMAX 10000
#define HACKMAX 40000

typedef struct {
    char *cmd;
    char *arg1;
    char *arg2;
} Command;

Command *parser_read_file(FILE *vm, int *count) {
    char line[75];
    Command *parsed = malloc(sizeof(Command) * VMMAX);
    int i = 0;
    
    while (fgets(line, sizeof(line), vm)) {
	char *comment = strstr(line, "//");
	if (comment != NULL) {
	    *comment = '\0';
	}
	char *command = strtok(line, " \n\r\t");
	if (command == NULL) {
	    continue;
	}

	char *arg1 = strtok(NULL, " \n\r\t");
	char *arg2 = strtok(NULL, " \n\r\t");

	parsed[i].cmd = strdup(command);
	if (arg1 == NULL) {
	    parsed[i].arg1 = NULL;
	} else {
	    parsed[i].arg1 = strdup(arg1);
	}

	if (arg2 == NULL) {
	    parsed[i].arg2 = NULL;
	} else {
	    parsed[i].arg2 = strdup(arg2);
	}

	i++;
    }

    *count = i;

    return parsed;
}

void codewriter_write(Command *vmcommands, int *commandSize, FILE *f, char *fname) {

    int label = 0;
    int i = 0;
    static int callid = 0;
    while (i < *commandSize) {
	if (strcmp(vmcommands[i].cmd, "push") == 0) {
	    writePush(vmcommands[i].arg1, vmcommands[i].arg2, f, fname);
	} else if (strcmp(vmcommands[i].cmd, "pop") == 0) {
	    writePop(vmcommands[i].arg1, vmcommands[i].arg2, f, fname);
    	} else if (strcmp(vmcommands[i].cmd, "add") == 0) {
	    writeAdd(f);
	} else if (strcmp(vmcommands[i].cmd, "sub") == 0) {
	    writeSub(f);
	} else if (strcmp(vmcommands[i].cmd, "neg") == 0) {
	    writeNeg(f);
	} else if (strcmp(vmcommands[i].cmd, "eq") == 0) {
	    writeEq(label, f);
	    label++;
	} else if (strcmp(vmcommands[i].cmd, "gt") == 0) {
	    writeGt(label, f);
	    label++;
	} else if (strcmp(vmcommands[i].cmd, "lt") == 0) {
	    writeLt(label, f);
	    label++;
	} else if (strcmp(vmcommands[i].cmd, "and") == 0) {
	    writeAnd(f);
	} else if (strcmp(vmcommands[i].cmd, "or") == 0) {
	    writeOr(f);
	} else if (strcmp(vmcommands[i].cmd, "not") == 0) {
	    writeNot(f);
	} else if (strcmp(vmcommands[i].cmd, "label") == 0) {
	    writeLabel(vmcommands[i].arg1, f);
	} else if (strcmp(vmcommands[i].cmd, "goto") == 0) {
	    writeGoto(vmcommands[i].arg1, f);
	} else if (strcmp(vmcommands[i].cmd, "if-goto") == 0) {
	    writeIfGoto(vmcommands[i].arg1, f);
	    //now we have to implement functions which look like the hardest part
	    //:((
	} else if  (strcmp(vmcommands[i].cmd, "function") == 0) {
	    writeFunction(vmcommands[i].arg1, vmcommands[i].arg2, f);
	} else if  (strcmp(vmcommands[i].cmd, "call") == 0) {
	    writeCall(callid, vmcommands[i].arg1, vmcommands[i].arg2, f);
	    callid++;
	} else if  (strcmp(vmcommands[i].cmd, "return") == 0) {
	    writeReturn(f);
	}

	i++;
    }
}

int main(int argc, char **argv) {
    
    if (argc < 2) {
	printf("VM files or directory must be provided\n");
	return 1;
    }

    char *cpy= strdup(argv[1]);
    char *baseName = strtok(cpy, ".");
    char *ext = strtok(NULL, ".");
    char *asmName = malloc(strlen(baseName) + 5);

    strcpy(asmName, baseName);
    strcat(asmName, ".asm");

    if (ext == NULL) {
	DIR *vmdir = opendir(baseName);
	struct dirent *entry;


	if (vmdir == NULL) {
	    printf("failed to open directory!\n");
	    return 1;
	}

	FILE *asmfile = fopen(asmName, "w");
	if (asmfile == NULL) {
	    printf("Error opening file\n");
	    return 1;
	}

	writeInit(asmfile);
	while ((entry = readdir(vmdir)) != NULL) {
	    char path[4096];
	    snprintf(path, sizeof(path), "%s/%s", baseName, entry->d_name);
	    struct stat st;
	    if (stat(path, &st) == -1) {
		printf("stat error\n");
		continue;
	    }


	    if (!S_ISREG(st.st_mode)) {
		continue;
	    }

	    char *dot = strrchr(entry->d_name, '.');
	    //checks if the file we are looking at is a ".vm" file
	    if (!dot || strcmp(dot, ".vm") != 0) {
		continue;
	    }

	    FILE *vmfile = fopen(path, "r");
	    if (!vmfile) {
		continue;
	    }

	    char *vmfilename = strdup(entry->d_name);
	    char *ext = strrchr(vmfilename, '.');
	    if (ext) {
		*ext = '\0';
	    }

	    int *numcommands = malloc(sizeof(int));
	    Command *cmdlist = parser_read_file(vmfile, numcommands);

	    codewriter_write(cmdlist, numcommands, asmfile, vmfilename);

	    free(vmfilename);

	    for (int j = 0; j < *numcommands; j++) {
		free(cmdlist[j].cmd);
		free(cmdlist[j].arg1);
		free(cmdlist[j].arg2);
	    }
	    free(cmdlist);
	    free(numcommands);
	    fclose(vmfile);
	}


    } else if (strcmp(ext, "vm") == 0) {
	FILE *vmfile = fopen(argv[1], "r");

	if (vmfile == NULL) {
	    printf("Error opening file\n");
	    return 1;
	}

	int* numcommands = malloc(sizeof(int));
	Command *commandlist = parser_read_file(vmfile, numcommands);
	fclose(vmfile);

	FILE *asmfile = fopen(asmName, "w");
	if (asmfile == NULL) {
	    printf("Error opening file\n");
	    return 1;
	}

	writeInit(asmfile);
	codewriter_write(commandlist, numcommands, asmfile, baseName);
	fclose(asmfile);

	for (int i = 0; i < *numcommands; i++) {
	    free(commandlist[i].cmd);
	    free(commandlist[i].arg1);
	    free(commandlist[i].arg2);
	}
	free(commandlist);
	free(numcommands);

    } else {
	printf("Must provide directory of vm files or single vm file\n");
	return 1;
    }

    free(asmName);
    free(cpy);
    return 0;
}
