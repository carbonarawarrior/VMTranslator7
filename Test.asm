// push constant 20
@20
D=A
@SP
A=M
M=D
@SP
M=M+1
// push local 2
@2
D=A
@LCL
A=M
M=M+D
D=M
@SP
A=M
M=D
@SP
M=M+1
// add (null) (null)
