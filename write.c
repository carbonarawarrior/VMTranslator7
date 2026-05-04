#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//module 7 methods
void writePush(char *arg1, char *arg2, FILE *f, char *fname) {
    if (strcmp(arg1, "constant") == 0) {
	fprintf(f, "// %s %s %s\n", "push", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@SP\n");
	fprintf(f, "A=M\n");
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "M=M+1\n");
    } else if (strcmp(arg1, "local") == 0) {
	fprintf(f, "// %s %s %s\n", "push", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@LCL\n");
	fprintf(f, "A=D+M\n");
	fprintf(f, "D=M\n");
	fprintf(f, "@SP\n");
	fprintf(f, "A=M\n");
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "M=M+1\n");
    } else if (strcmp(arg1, "static") == 0) {
	fprintf(f, "// %s %s %s\n", "push", arg1, arg2);
	fprintf(f, "@%s.%s\n", fname, arg2);
	fprintf(f, "D=M\n");
	fprintf(f, "@SP\n");
	fprintf(f, "A=M\n");
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "M=M+1\n");
    } else if (strcmp(arg1, "this") == 0) {
	fprintf(f, "// %s %s %s\n", "push", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@THIS\n");
	fprintf(f, "A=D+M\n");
	fprintf(f, "D=M\n");
	fprintf(f, "@SP\n");
	fprintf(f, "A=M\n");
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "M=M+1\n");
    } else if (strcmp(arg1, "that") == 0) { 
	fprintf(f, "// %s %s %s\n", "push", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@THAT\n");
	fprintf(f, "A=D+M\n");
	fprintf(f, "D=M\n");
	fprintf(f, "@SP\n");
	fprintf(f, "A=M\n");
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "M=M+1\n");
    } else if (strcmp(arg1, "pointer") == 0) { 
	fprintf(f, "// %s %s %s\n", "push", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@3\n");
	fprintf(f, "A=D+A\n");
	fprintf(f, "D=M\n");
	fprintf(f, "@SP\n");
	fprintf(f, "A=M\n");
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "M=M+1\n");
    } else if (strcmp(arg1, "temp") == 0) {
	fprintf(f, "// %s %s %s\n", "push", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@5\n");
	fprintf(f, "A=D+A\n");
	fprintf(f, "D=M\n");
	fprintf(f, "@SP\n");
	fprintf(f, "A=M\n");
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "M=M+1\n");
    } else if (strcmp(arg1, "argument") == 0) {
	fprintf(f, "// %s %s %s\n", "push", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@ARG\n");
	fprintf(f, "A=D+M\n");
	fprintf(f, "D=M\n");
	fprintf(f, "@SP\n");
	fprintf(f, "A=M\n");
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "M=M+1\n");
    }
}
void writePop(char *arg1, char *arg2, FILE *f, char *fname) {

    if (strcmp(arg1, "local") == 0) {
	fprintf(f, "// %s %s %s\n", "pop", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@LCL\n");
	fprintf(f, "D=D+M\n");
	fprintf(f, "@R14\n"); //essentially we use R14 as a pseudo D register
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
	fprintf(f, "D=M\n");
	fprintf(f, "@R14\n");
	fprintf(f, "A=M\n"); //earlier we stored the address of the local register in R14
	fprintf(f, "M=D\n"); //set that address (in local) to the value we got off the stack
    } else if (strcmp(arg1, "static") == 0) {
	fprintf(f, "// %s %s %s\n", "pop", arg1, arg2);
	fprintf(f, "@SP\n");
	fprintf(f, "AM=M-1\n");
	fprintf(f, "D=M\n");
	fprintf(f, "@%s.%s\n", fname, arg2);
	fprintf(f, "M=D\n");
    } else if (strcmp(arg1, "this") == 0) {
	fprintf(f, "// %s %s %s\n", "pop", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@THIS\n");
	fprintf(f, "D=D+M\n");
	fprintf(f, "@R14\n"); //essentially we use R14 as a pseudo D register
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
	fprintf(f, "D=M\n");
	fprintf(f, "@R14\n");
	fprintf(f, "A=M\n"); //earlier we stored the address of the local register in R14
	fprintf(f, "M=D\n"); //set that address (in local) to the value we got off the stack
    } else if (strcmp(arg1, "that") == 0) { 
	fprintf(f, "// %s %s %s\n", "pop", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@THAT\n");
	fprintf(f, "D=D+M\n");
	fprintf(f, "@R14\n"); //essentially we use R14 as a pseudo D register
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
	fprintf(f, "D=M\n");
	fprintf(f, "@R14\n");
	fprintf(f, "A=M\n"); //earlier we stored the address of the local register in R14
	fprintf(f, "M=D\n"); //set that address (in local) to the value we got off the stack
    } else if (strcmp(arg1, "pointer") == 0) {
	fprintf(f, "// %s %s %s\n", "pop", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@3\n");
	fprintf(f, "D=D+A\n");
	fprintf(f, "@R14\n"); //essentially we use R14 as a pseudo D register
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
	fprintf(f, "D=M\n");
	fprintf(f, "@R14\n");
	fprintf(f, "A=M\n"); //earlier we stored the address of the local register in R14
	fprintf(f, "M=D\n"); //set that address (in local) to the value we got off the stack
    } else if (strcmp(arg1, "temp") == 0) {
	fprintf(f, "// %s %s %s\n", "pop", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@5\n");
	fprintf(f, "D=D+A\n");
	fprintf(f, "@R14\n"); //essentially we use R14 as a pseudo D register
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
	fprintf(f, "D=M\n");
	fprintf(f, "@R14\n");
	fprintf(f, "A=M\n"); //earlier we stored the address of the local register in R14
	fprintf(f, "M=D\n"); //set that address (in local) to the value we got off the stack
    } else if (strcmp(arg1, "argument") == 0) {
	fprintf(f, "// %s %s %s\n", "pop", arg1, arg2);
	fprintf(f, "@%s\n", arg2);
	fprintf(f, "D=A\n");
	fprintf(f, "@ARG\n");
	fprintf(f, "D=D+M\n");
	fprintf(f, "@R14\n"); //essentially we use R14 as a pseudo D register
	fprintf(f, "M=D\n");
	fprintf(f, "@SP\n");
	fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
	fprintf(f, "D=M\n");
	fprintf(f, "@R14\n");
	fprintf(f, "A=M\n"); //earlier we stored the address of the local register in R14
	fprintf(f, "M=D\n"); //set that address (in local) to the value we got off the stack
    }
}

void writeAdd(FILE *f) {
    fprintf(f, "// add\n");
    fprintf(f, "@SP\n");
    fprintf(f, "AM=M-1\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M-1\n");
    fprintf(f, "M=D+M\n");
}
void writeSub(FILE *f) {
    fprintf(f, "// sub\n");
    fprintf(f, "@SP\n");
    fprintf(f, "AM=M-1\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M-1\n");
    fprintf(f, "M=M-D\n");
}
void writeNeg(FILE *f) {
    fprintf(f, "// neg\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M-1\n");
    fprintf(f, "M=-M\n");
}
void writeEq(int label, FILE *f) {
    fprintf(f, "// eq\n");
    fprintf(f, "@SP\n");
    fprintf(f, "AM=M-1\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M-1\n");
    fprintf(f, "D=D-M\n");
    fprintf(f, "M=-1\n");
    fprintf(f, "@trueeq%d\n", label);
    fprintf(f, "D;JEQ\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M-1\n");
    fprintf(f, "M=0\n");
    fprintf(f, "(trueeq%d)\n", label);
}
void writeGt(int label, FILE *f) {
    fprintf(f, "// gt\n");
    fprintf(f, "@SP\n");
    fprintf(f, "AM=M-1\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M-1\n");
    fprintf(f, "D=M-D\n");
    fprintf(f, "M=-1\n");
    fprintf(f, "@truegt%d\n", label);
    fprintf(f, "D;JGT\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M-1\n");
    fprintf(f, "M=0\n");
    fprintf(f, "(truegt%d)\n", label);
}
void writeLt(int label, FILE *f) {
    fprintf(f, "// lt\n");
    fprintf(f, "@SP\n");
    fprintf(f, "AM=M-1\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M-1\n");
    fprintf(f, "D=M-D\n");
    fprintf(f, "M=-1\n");
    fprintf(f, "@truelt%d\n", label);
    fprintf(f, "D;JLT\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M-1\n");
    fprintf(f, "M=0\n");
    fprintf(f, "(truelt%d)\n", label);
}
void writeAnd(FILE *f) {
    fprintf(f, "// and\n");
    fprintf(f, "@SP\n");
    fprintf(f, "AM=M-1\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M-1\n");
    fprintf(f, "M=D&M\n");
}
void writeOr(FILE *f) {
    fprintf(f, "// or\n");
    fprintf(f, "@SP\n");
    fprintf(f, "AM=M-1\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M-1\n");
    fprintf(f, "M=D|M\n");
}
void writeNot(FILE *f) {
    fprintf(f, "// not\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M-1\n");
    fprintf(f, "M=!M\n");
}
void writeLabel(char *arg1, FILE *f) {
    fprintf(f, "// label %s\n", arg1);
    fprintf(f, "(%s)\n", arg1);
}
void writeGoto(char *arg1, FILE *f) {
    fprintf(f, "// goto %s\n", arg1);
    fprintf(f, "@%s\n", arg1);
    fprintf(f, "0;JMP\n");
}
void writeIfGoto(char *arg1, FILE *f) {
    fprintf(f, "// if-goto %s\n", arg1);
    fprintf(f, "@SP\n");
    fprintf(f, "AM=M-1\n"); //move the stack pointer down 1 and put the value there into D
    fprintf(f, "D=M\n");//we have the value we need to compare in D
    fprintf(f, "@%s\n", arg1);
    fprintf(f, "D;JNE\n");
}

//module 8 methods
void writeInit(FILE *f) {
    fprintf(f, "// init\n");
    fprintf(f, "@256\n");
    fprintf(f, "D=A\n");
    fprintf(f, "@SP\n");
    fprintf(f, "M=D\n");
    
    //"calls" Sys.init
    //push return address
    fprintf(f, "@%s$%s\n", "Sys", "init");
    fprintf(f, "D=A\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M\n");
    fprintf(f, "M=D\n");
    fprintf(f, "@SP\n");
    fprintf(f, "M=M+1\n");
    //push (previous) LCL address
    fprintf(f, "@LCL\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M\n");
    fprintf(f, "M=D\n");
    fprintf(f, "@SP\n");
    fprintf(f, "M=M+1\n");
    //push (previous) arg address
    fprintf(f, "@ARG\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M\n");
    fprintf(f, "M=D\n");
    fprintf(f, "@SP\n");
    fprintf(f, "M=M+1\n");
    //new THIS base address
    fprintf(f, "@THIS\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M\n");
    fprintf(f, "M=D\n");
    fprintf(f, "@SP\n");
    fprintf(f, "M=M+1\n");
    //new THAT address
    fprintf(f, "@THAT\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M\n");
    fprintf(f, "M=D\n");
    fprintf(f, "@SP\n");
    fprintf(f, "M=M+1\n");
    //new arg
    fprintf(f, "@SP\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@%d\n", 5);
    fprintf(f, "D=D-A\n");
    fprintf(f, "@ARG\n");
    fprintf(f, "M=D\n");
    //new LCL base address
    fprintf(f, "@SP\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@LCL\n");
    fprintf(f, "M=D\n");
    //go to func
    fprintf(f, "@Sys.init\n");
    fprintf(f, "0;JMP\n");
    fprintf(f, "(%s$%s)\n", "Sys", "init");
}


void writeFunction(char *arg1, char *arg2, FILE *f) {
    fprintf(f, "// function %s %s\n", arg1, arg2);
    //create a label marking where we store the funcs definition
    fprintf(f, "(%s)\n", arg1);

    //init each local var to 0
    int num = atoi(arg2);
    for (int j = 0; j < num; j++) {
	fprintf(f, "@SP\n");
	fprintf(f, "A=M\n");
	fprintf(f, "M=0\n");
	fprintf(f, "@SP\n");
	fprintf(f, "M=M+1\n");
    }
}

void writeCall(int callid, char *arg1, char *arg2, FILE *f) {
    fprintf(f, "// call %s %s\n", arg1, arg2);
    //push return address

    fprintf(f, "@%s$%d\n", arg1, callid);
    fprintf(f, "D=A\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M\n");
    fprintf(f, "M=D\n");
    fprintf(f, "@SP\n");
    fprintf(f, "M=M+1\n");
    //push (previous) LCL address
    fprintf(f, "@LCL\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M\n");
    fprintf(f, "M=D\n");
    fprintf(f, "@SP\n");
    fprintf(f, "M=M+1\n");
    //push (previous) arg address
    fprintf(f, "@ARG\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M\n");
    fprintf(f, "M=D\n");
    fprintf(f, "@SP\n");
    fprintf(f, "M=M+1\n");
    //new THIS base address
    fprintf(f, "@THIS\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M\n");
    fprintf(f, "M=D\n");
    fprintf(f, "@SP\n");
    fprintf(f, "M=M+1\n");
    //new THAT address
    fprintf(f, "@THAT\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@SP\n");
    fprintf(f, "A=M\n");
    fprintf(f, "M=D\n");
    fprintf(f, "@SP\n");
    fprintf(f, "M=M+1\n");
    //new arg
    fprintf(f, "@SP\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@%d\n", (atoi(arg2)+5));
    fprintf(f, "D=D-A\n");
    fprintf(f, "@ARG\n");
    fprintf(f, "M=D\n");
    //new LCL base address
    fprintf(f, "@SP\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@LCL\n");
    fprintf(f, "M=D\n");
    //go to func
    fprintf(f, "@%s\n", arg1);
    fprintf(f, "0;JMP\n");
    fprintf(f, "(%s$%d)\n",  arg1, callid);
}

void writeReturn(FILE *f) {
    fprintf(f, "// return\n");
    fprintf(f, "@LCL\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@R13\n");
    fprintf(f, "M=D\n");
    fprintf(f, "@5\n");
    fprintf(f, "A=D-A\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@R14\n");
    fprintf(f, "M=D\n");

    fprintf(f, "@SP\n");
    fprintf(f, "AM=M-1\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@ARG\n");
    fprintf(f, "A=M\n");
    fprintf(f, "M=D\n");

    fprintf(f, "@ARG\n");
    fprintf(f, "D=M+1\n");
    fprintf(f, "@SP\n");
    fprintf(f, "M=D\n");

    fprintf(f, "@R13\n");
    fprintf(f, "AM=M-1\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@THAT\n");
    fprintf(f, "M=D\n");

    fprintf(f, "@R13\n");
    fprintf(f, "AM=M-1\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@THIS\n");
    fprintf(f, "M=D\n");

    fprintf(f, "@R13\n");
    fprintf(f, "AM=M-1\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@ARG\n");
    fprintf(f, "M=D\n");

    fprintf(f, "@R13\n");
    fprintf(f, "AM=M-1\n");
    fprintf(f, "D=M\n");
    fprintf(f, "@LCL\n");
    fprintf(f, "M=D\n");

    fprintf(f, "@R14\n");
    fprintf(f, "A=M\n");
    fprintf(f, "0;JMP\n");
}
