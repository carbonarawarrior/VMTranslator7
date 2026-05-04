//module 7 methods
void writePush(char *arg1, char *arg2, FILE *f, char *fname);
void writePop(char *arg1, char *arg2, FILE *f, char *fname);
void writeAdd(FILE *f);
void writeSub(FILE *f);
void writeNeg(FILE *f);
void writeEq(int label, FILE *f);
void writeGt(int label, FILE *f);
void writeLt(int label, FILE *f);
void writeAnd(FILE *f);
void writeOr(FILE *f);
void writeNot(FILE *f);
void writeLabel(char *arg1, FILE *f);
void writeGoto(char *arg1, FILE *f);
void writeIfGoto(char *arg1, FILE *f);

//module 8 methods
void writeInit(FILE *f);
void writeFunction(char *arg1, char *arg2, FILE *f); 
void writeCall(int callid, char *arg1, char *arg2, FILE *f); 
void writeReturn(FILE *f); 
