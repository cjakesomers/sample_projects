-This project simulates a subset of the MIPS ISA using input .x files found in "inputs" 

-The .s files contain the human readable MIPS commands which have been translated to the 4 byte instructions to be 
interpreted by the simulation

-The simulation uses the SYSCALL funtion to terminate code execution when the value of register 2 ($v0) is equal to 10

-Compiled using the Makefile found in src

-

-shell.c and shell.h were provided for this project leaving the process_instruction function incomplete

-process_instruction parses the current word pointed to by the program counter for the opcode, then uses the 
corresponding function to process the rest of the given instruction.

The simulation uses the following commands:
--go: processes instructions until given a stop condition

--run n: runs the next n instructions

--mdump low high: dumps the memory from the low address to the high address to the screen and a file named dumpsim

--rdump: dumps the values of the 32 registers, PC and current instruction count similarly to mdump 

--input regNum regVal: sets regNum to regVal

--high val: set HI register to val

--low val: set LO register to val

--?: prints a list of shell commands

--q: exits the program

The simulation implements the following MIPS functions as described in the MIPSISA pdf provided:

-J		-JAL	-BEQ	-BNE	-BLEZ	-BGTZ
-ADDI	-ADDIU	-SLTI	-SLTIU	-ANDI	-ORI
-XORI	-LUI	-LB		-LH		-LW		-LBU
-LHU	-SB		-SH		-SW		-BLTZ	-BGEZ
-BLTZAL	-BGEZAL	-SLL	-SRL	-SRA	-SLLV
-SRLV	-SRAV	-JR		-JALR	-ADD	-ADDU
-SUB	-SUBU 	-AND	-OR		-XOR	-NOR
-SLT	-SLTU	-MULT	-MFHI	-MFLO	-MTHI
-MTLO	-MULTU	-DIV	-DIVU	-SYSCALL