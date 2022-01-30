// Christopher Somers

// sim.c


#include <stdio.h>
#include "shell.h"

// if reg 2 == 10, sets run bit to 0
void MIPS_syscall() {
    printf("syscall\n");
    //if "$v0" == 10, run bit = 0
    if(CURRENT_STATE.REGS[2] == 10) {
        RUN_BIT = 0;
    }
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Divide Unsigned
void MIPS_divu() {
    printf("divu\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt = rt>>16;
    rs = CURRENT_STATE.REGS[rs];
    rt = CURRENT_STATE.REGS[rt];
    // obtain remainder
    int32_t remainder = rs % rt;
    //subtract the remainder and obtain the quotient
    rs = rs - remainder;
    int32_t quotient = rs / rt;
    //store the quotient in LO and the remainder in HI
    NEXT_STATE.LO = quotient;
    NEXT_STATE.HI = remainder;
    //increment PC
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Divide
void MIPS_div() {
    printf("div\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt = rt>>16;
    rs = CURRENT_STATE.REGS[rs];
    rt = CURRENT_STATE.REGS[rt];
    // obtain remainder
    int32_t remainder = rs % rt;
    //subtract the remainder and obtain the quotient
    rs = rs - remainder;
    int32_t quotient = rs / rt;
    //store the quotient in LO and the remainder in HI
    NEXT_STATE.LO = quotient;
    NEXT_STATE.HI = remainder;
    //increment PC
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Multiply Unsigned
void MIPS_multu() {
    printf("multu\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt = rt>>16;
    rs = CURRENT_STATE.REGS[rs];
    rt = CURRENT_STATE.REGS[rt];
    // multiply rs and rt and split the results into HI and LO
    int64_t product = rs * rt;
    int32_t HI, LO;
    int64_t temp = product;
    temp = temp&65535;
    LO = temp;
    temp = product;
    temp = temp&4294901760;
    temp = temp>>16;
    HI = temp;
    NEXT_STATE.HI = HI;
    NEXT_STATE.LO = LO;
    //increment PC
    NEXT_STATE.PC = CURRENT_STATE.PC +4;
}
// Multiply
void MIPS_mult() {
    printf("mult\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt = rt>>16;
    rs = CURRENT_STATE.REGS[rs];
    rt = CURRENT_STATE.REGS[rt];
    // multiply rs and rt and split the results into HI and LO
    int64_t product = rs * rt;
    int32_t HI, LO;
    int64_t temp = product;
    temp = temp&65535;
    LO = temp;
    temp = product;
    temp = temp&4294901760;
    temp = temp>>16;
    HI = temp;
    NEXT_STATE.HI = HI;
    NEXT_STATE.LO = LO;
    //increment PC
    NEXT_STATE.PC = CURRENT_STATE.PC +4;
}
// Store Word
void MIPS_sw() {
    printf("sw\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    uint32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get base
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t base = PC&65011712;
    base = base>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    // compute virtual address and store lower byte at the effective address
    uint32_t address = CURRENT_STATE.REGS[base] + offset;
    //obtain the lower byte of GPR[rt] (& with 11111111 11111111 11111111 11111111)
    rt = CURRENT_STATE.REGS[rt];
    uint32_t word = rt&4294967295;
    // write the byte to address rt
    mem_write_32(address, word);
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Store Halfword
void MIPS_sh() {
    printf("sh\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    uint32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get base
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t base = PC&65011712;
    base = base>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    // compute virtual address and store lower byte at the effective address
    uint32_t address = CURRENT_STATE.REGS[base] + offset;
    //obtain the lower byte of GPR[rt] (& with 11111111 11111111)
    rt = CURRENT_STATE.REGS[rt];
    uint32_t halfword = rt&65535;
    // write the byte to address rt
    mem_write_32(address, halfword);
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Store Byte
void MIPS_sb() {
    printf("sb\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    uint32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get base
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t base = PC&65011712;
    base = base>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    // compute virtual address and store lower byte at the effective address
    uint32_t address = CURRENT_STATE.REGS[base] + offset;
    //obtain the lower byte of GPR[rt] (& with 11111111)
    rt = CURRENT_STATE.REGS[rt];
    uint32_t byte = rt&255;
    // write the byte to address rt
    mem_write_32(address, byte);
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Move To LO
void MIPS_mtlo() {
    printf("mtlo\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //move the contents of register rs into special register HI
    NEXT_STATE.LO = CURRENT_STATE.REGS[rs];
    //increment PC
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Move To HI
void MIPS_mthi() {
    printf("mthi\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //move the contents of register rs into special register HI
    NEXT_STATE.HI = CURRENT_STATE.REGS[rs];
    //increment PC
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Move From LO
void MIPS_mflo() {
    printf("mflo\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    int32_t rd = PC&63488;
    rd = rd>>11;
    // move the contents of the special register LO to register rd
    NEXT_STATE.REGS[rd] = CURRENT_STATE.LO;
    // increment PC
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Move From HI
void MIPS_mfhi() {
    printf("mfhi\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    int32_t rd = PC&63488;
    rd = rd>>11;
    // move the contents of the special register HI to register rd
    NEXT_STATE.REGS[rd] = CURRENT_STATE.HI;
    // increment PC
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Branch On Greater Than Or Equal To Zero And Link
void MIPS_bgezal() {
    printf("bltzal\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    int32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    // compare rs to zero to determine direction
    rs = CURRENT_STATE.REGS[rs];
    //$31 stores current PC + 4 unconditionally
    NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
    if(rs >= 0) {
        // target address is theh sum of the offset and next instruction address
        int32_t delayAddress = CURRENT_STATE.PC + 4;
        //offset is shifted two bits left
        offset = offset<<2;
        int32_t targetAddress = delayAddress + offset;
        NEXT_STATE.PC = targetAddress;
    }
    else {
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
    }
}
// Branch On Less Than Zero And Link
void MIPS_bltzal() {
    printf("bltzal\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    int32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    // compare rs to zero to determine direction
    rs = CURRENT_STATE.REGS[rs];
    //$31 stores current PC + 4 unconditionally
    NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
    if(rs < 0) {
        // target address is theh sum of the offset and next instruction address
        int32_t delayAddress = CURRENT_STATE.PC + 4;
        //offset is shifted two bits left
        offset = offset<<2;
        int32_t targetAddress = delayAddress + offset;
        NEXT_STATE.PC = targetAddress;
    }
    else {
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
    }
}
// Branch On Greater Than Or Equal To Zero
void MIPS_bgez() {
    printf("bgez\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    int32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    // compare rs to zero to determine direction
    rs = CURRENT_STATE.REGS[rs];
    if(rs >= 0) {
        // target address is theh sum of the offset and next instruction address
        int32_t delayAddress = CURRENT_STATE.PC + 4;
        //offset is shifted two bits left
        offset = offset<<2;
        int32_t targetAddress = delayAddress + offset;
        NEXT_STATE.PC = targetAddress;
    }
    else {
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
    }
}
// Branch On Less Than Zero
void MIPS_bltz() {
    printf("bltz\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    int32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    // compare rs to zero to determine direction
    rs = CURRENT_STATE.REGS[rs];
    if(rs < 0) {
        // target address is theh sum of the offset and next instruction address
        int32_t delayAddress = CURRENT_STATE.PC + 4;
        //offset is shifted two bits left
        offset = offset<<2;
        int32_t targetAddress = delayAddress + offset;
        NEXT_STATE.PC = targetAddress;
    }
    else {
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
    }
}
// Branch On Greater Than Zero
void MIPS_bgtz() {
    printf("bgtz\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    int32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    // compare rs to zero to determine direction
    rs = CURRENT_STATE.REGS[rs];
    if(rs > 0) {
        // target address is theh sum of the offset and next instruction address
        int32_t delayAddress = CURRENT_STATE.PC + 4;
        //offset is shifted two bits left
        offset = offset<<2;
        int32_t targetAddress = delayAddress + offset;
        NEXT_STATE.PC = targetAddress;
    }
    else {
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
    }
}
// Branch On Less Than Or Equal To Zero
void MIPS_blez() {
    printf("blez\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    int32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    // compare rs to zero to determine direction
    rs = CURRENT_STATE.REGS[rs];
    if(rs <= 0) {
        // target address is theh sum of the offset and next instruction address
        int32_t delayAddress = CURRENT_STATE.PC + 4;
        //offset is shifted two bits left
        offset = offset<<2;
        int32_t targetAddress = delayAddress + offset;
        NEXT_STATE.PC = targetAddress;
    }
    else {
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
    }
}
// Branch On Not Equal
void MIPS_bne() {
    printf("bne\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    int32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    // compare register values to determine direction
    rs = CURRENT_STATE.REGS[rs];
    rt = CURRENT_STATE.REGS[rt];
    if(rs != rt) {
        // target address is theh sum of the offset and next instruction address
        int32_t delayAddress = CURRENT_STATE.PC + 4;
        //offset is shifted two bits left
        offset = offset<<2;
        int32_t targetAddress = delayAddress + offset;
        NEXT_STATE.PC = targetAddress;
    }
    else {
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
    }
}
// Branch On Equal
void MIPS_beq() {
    printf("beq\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    int32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    // compare register values to determine direction
    rs = CURRENT_STATE.REGS[rs];
    rt = CURRENT_STATE.REGS[rt];
    if(rs == rt) {
        // target address is theh sum of the offset and next instruction address
        int32_t delayAddress = CURRENT_STATE.PC + 4;
        //offset is shifted two bits left
        offset = offset<<2;
        int32_t targetAddress = delayAddress + offset;
        NEXT_STATE.PC = targetAddress;
    }
    else {
        NEXT_STATE.PC = CURRENT_STATE.PC + 4;
    }
}
// Jump And Link Register
void MIPS_jalr() {
    printf("jal\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11111111 11111111 11111111 and shift left by two to get temp
    uint32_t rs = PC&67108863;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rd = PC&63488;
    rd = rd>>11;
    // contents of rs are stored in temp, PC + 4 is stored in rd and PC becomes temp
    //update next PC and $31
    int32_t temp = CURRENT_STATE.REGS[rs];
    NEXT_STATE.REGS[rd] = CURRENT_STATE.PC + 4;
    NEXT_STATE.PC = temp;
}
// Jump Register
void MIPS_jr() {
    printf("jr");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //the contents of register rs become the new PC
    NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
}
// jump and link
void MIPS_jal() {
    printf("jal\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11111111 11111111 11111111 and shift left by two to get temp
    uint32_t temp = PC&67108863;
    temp = temp<<2;
    // bitwise and PC with 11110000 00000000 00000000 00000000 and add to temp to get new PC
    PC = PC&4026531840;
    PC = PC + temp;
    //update next PC and $31
    NEXT_STATE.PC = PC;
    NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
}
// jump
void MIPS_j() {
    printf("j\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11111111 11111111 11111111 and shift left by two to get temp
    uint32_t temp = PC&67108863;
    temp = temp<<2;
    // bitwise and PC with 11110000 00000000 00000000 00000000 and add to temp to get new PC
    PC = PC&4026531840;
    PC = PC + temp;
    NEXT_STATE.PC = PC;
}
// Load Halfword Unsigned
void MIPS_lhu() {
    printf("lhu\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    uint32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get base
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t base = PC&65011712;
    base = base>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    // compute virtual address and store result in rt
    uint32_t address = CURRENT_STATE.REGS[base] + offset;
    uint32_t result = mem_read_32(address);
    // bitwise and with 00000000 00000000 11111111 11111111 to get the lower 8 bits
    result = result&65535;
    //assign the result to rt
    NEXT_STATE.REGS[rt] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Load Byte Unsigned
void MIPS_lbu() {
    printf("lbu\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    uint32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get base
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t base = PC&65011712;
    base = base>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    // compute virtual address and store result in rt
    uint32_t address = CURRENT_STATE.REGS[base] + offset;
    uint32_t result = mem_read_32(address);
    // bitwise and with 00000000 00000000 00000000 11111111 to get the lower 8 bits
    result = result&255;
    //assign the result to rt
    NEXT_STATE.REGS[rt] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Load Word
void MIPS_lw() {
    printf("lw\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    uint32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get base
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t base = PC&65011712;
    base = base>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    // compute virtual address and store result in rt
    uint32_t address = CURRENT_STATE.REGS[base] + offset;
    int32_t result = mem_read_32(address);
    // bitwise and with 11111111 11111111 11111111 11111111 to get the lower 8 bits
    result = result&4294967295;
    //assign the result to rt
    NEXT_STATE.REGS[rt] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Load Halfword
void MIPS_lh() {
    printf("lh\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    uint32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get base
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t base = PC&65011712;
    base = base>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    // compute virtual address and store result in rt
    uint32_t address = CURRENT_STATE.REGS[base] + offset;
    int32_t result = mem_read_32(address);
    // bitwise and with 00000000 00000000 11111111 11111111 to get the lower 8 bits
    result = result&65535;
    //assign the result to rt
    NEXT_STATE.REGS[rt] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Load Byte
void MIPS_lb() {
    printf("lb\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get offset
    uint32_t offset = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get base
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t base = PC&65011712;
    base = base>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    // compute virtual address and store result in rt
    uint32_t address = CURRENT_STATE.REGS[base] + offset;
    int32_t result = mem_read_32(address);
    // bitwise and with 00000000 00000000 00000000 11111111 to get the lower 8 bits
    result = result&255;
    //assign the result to rt
    NEXT_STATE.REGS[rt] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// r-type Set On Less Than Unsigned
void MIPS_sltu() {
    printf("sltu\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    rs = CURRENT_STATE.REGS[rs];
    rt = CURRENT_STATE.REGS[rt];
    uint32_t sub = rs - rt;
    //make comparison
    uint32_t result;
    if(sub < 0) {
        result = 1;
    }
    else {
        result = 0;
    }
    //assign the result to rt
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// r-type Set On Less Than
void MIPS_slt() {
    printf("slt\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    rs = CURRENT_STATE.REGS[rs];
    rt = CURRENT_STATE.REGS[rt];
    int32_t sub = rs - rt;
    //make comparison
    uint32_t result = 0;
    if(sub < 0) {
        result = 1;
    }
    //assign the result to rt
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// r-type nor
void MIPS_nor() {
    printf("nor\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    uint32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt = rt>>16;
    // perform bitwise and on rs and rt and store the result in rd
    rs = CURRENT_STATE.REGS[rs];
    rt = CURRENT_STATE.REGS[rt];
    uint32_t result = ~(rs|rt);
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// r-type xor
void MIPS_xor() {
    printf("xor\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    uint32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt = rt>>16;
    // perform bitwise and on rs and rt and store the result in rd
    rs = CURRENT_STATE.REGS[rs];
    rt = CURRENT_STATE.REGS[rt];
    uint32_t result = rs^rt;
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// r-type Or
void MIPS_or() {
    printf("or\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    uint32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt = rt>>16;
    // perform bitwise and on rs and rt and store the result in rd
    rs = CURRENT_STATE.REGS[rs];
    rt = CURRENT_STATE.REGS[rt];
    uint32_t result = rs|rt;
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// r-type And
void MIPS_and() {
    printf("and\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    uint32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rd = PC&63488;
    rd = rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    // perform bitwise and on rs and rt and store the result in rd
    rs = CURRENT_STATE.REGS[rs];
    rt = CURRENT_STATE.REGS[rt];
    uint32_t result = rs&rt;
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// r-type Subtraction Unsigned
void MIPS_subu() {
    printf("subu\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    uint32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    // add rs and rt and store in rd
    uint32_t result = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// r-type Subtraction
void MIPS_sub() {
    printf("sub\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    uint32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    // add rs and rt and store in rd
    int32_t result = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// r-type Add Unsigned
void MIPS_addu() {
    printf("addu\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    uint32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    // add rs and rt and store in rd
    uint32_t result = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// r-type Add
void MIPS_add() {
    printf("add\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    // add rs and rt and store in rd
    int32_t result = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}

// Shift Right Arithmetic Variable
void MIPS_srav() {
    printf("srav\n");
    mem_read_32(CURRENT_STATE.PC);
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    rt = CURRENT_STATE.REGS[rt];
    rs = CURRENT_STATE.REGS[rs];
    //obtain the low order 5 bits of rs by anding with 00000000 00000000 00000000 00011111
    int32_t offset = rs&31;
    // shift rt by the offset and store in rd
    NEXT_STATE.REGS[rd] = rt>>offset;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}

// Shift Right Logical Variable
void MIPS_srlv() {
    printf("srlv\n");
    mem_read_32(CURRENT_STATE.PC);
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    rt = CURRENT_STATE.REGS[rt];
    rs = CURRENT_STATE.REGS[rs];
    //obtain the low order 5 bits of rs by anding with 00000000 00000000 00000000 00011111
    int32_t offset = rs&31;
    //shift rt's contents offset bits right and store in rd
    uint32_t result = rt>>offset;
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Shift Left Logical Variable
void MIPS_sllv() {
    printf("sllv\n");
    mem_read_32(CURRENT_STATE.PC);
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    int32_t rs = PC&65011712;
    rs = rs>>21;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    rt = CURRENT_STATE.REGS[rt];
    rs = CURRENT_STATE.REGS[rs];
    //obtain the low order 5 bits of rs by anding with 00000000 00000000 00000000 00011111
    int32_t offset = rs&31;
    //shift rt's contents offset bits left and store in rd
    uint32_t result = rt<<offset;
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Shift Right Arithmetic
void MIPS_sra() {
    printf("sra\n");
    mem_read_32(CURRENT_STATE.PC);
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 00000111 11000000 to get sa
    int32_t sa = PC&1984;
    sa = sa>>6;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    // shift rt right sa bits and store in rd
    rt = CURRENT_STATE.REGS[rt];
    uint32_t result = rt>>sa;
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// shirft right logical
void MIPS_srl() {
    printf("srl\n");
    mem_read_32(CURRENT_STATE.PC);
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 00000111 11000000 to get sa
    int32_t sa = PC&1984;
    sa = sa>>6;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    // shift rt right sa bits and store in rd
    rt = CURRENT_STATE.REGS[rt];
    int32_t result = rt>>sa;
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// Shift Left Logical
void MIPS_sll() {
    printf("sll\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 00000111 11000000 to get sa
    int32_t sa = PC&1984;
    sa = sa>>6;
    // & PC with 00000000 00000000 11111000 00000000 to get rd
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rd = PC&63488;
    rd = rd>>11;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    // shift rt left sa bits and store in rd
    rt = CURRENT_STATE.REGS[rt];
    int32_t result = rt<<sa;
    //assign the result to rd
    NEXT_STATE.REGS[rd] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// I-type Load Upper Immediate
void MIPS_lui() {
    printf("lui\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get immediate
    int32_t immediate = PC&65535;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    // shift the immediate 16 bits to the left and store in rt
    int32_t result = immediate<<16;
    //assign the result to rt
    NEXT_STATE.REGS[rt] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// I-type Exclusive Or Immediate
void MIPS_xori() {
    printf("xori\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get immediate
    int32_t immediate = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    // perform bitwise xor and store in result
    rs = CURRENT_STATE.REGS[rs];
    int32_t result = rs^immediate;
    //assign the result to rt
    NEXT_STATE.REGS[rt] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// I-type Or Immediate
void MIPS_ori() {
    printf("ori\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get immediate
    int32_t immediate = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    // perform bitwise or and store in result
    rs = CURRENT_STATE.REGS[rs];
    int32_t result = rs|immediate;
    //assign the result to rt
    NEXT_STATE.REGS[rt] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// I-type And Immediate
void MIPS_andi() {
    printf("andi\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get immediate
    int32_t immediate = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    // perform bitwise and and store in result
    rs = CURRENT_STATE.REGS[rs];
    int32_t result = rs&immediate;
    //assign the result to rt
    NEXT_STATE.REGS[rt] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// I-type Set On Less Than Immediate Unsigned
void MIPS_sltiu() {
    printf("sltiu\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get immediate
    uint32_t immediate = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    //make comparison
    rs = CURRENT_STATE.REGS[rs];
    uint32_t sub = rs - immediate;
    uint32_t result;
    if(CURRENT_STATE.REGS[rs] < immediate) {
        result = 1;
    }
    else {
        result = 0;
    }
    //assign the result to rt
    NEXT_STATE.REGS[rt] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// I-type Set On Less Than Immediate
void MIPS_slti() {
    printf("slti\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get immediate
    int32_t immediate = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    //make comparison
    rs = CURRENT_STATE.REGS[rs];
    int32_t sub = rs - immediate;
    int32_t result;
    if(sub < 0) {
        result = 1;
    }
    else {
        result = 0;
    }
    //assign the result to rt
    NEXT_STATE.REGS[rt] = result;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// I-type add immediate
void MIPS_addi() {
    printf("addi\n");
    int32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get immediate
    int32_t immediate = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    int32_t rt = PC&2031616;
    rt = rt>>16;
    //perform addition
    NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + immediate;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
// I-type add immediate unsigned
void MIPS_addiu() {
    printf("addiu\n");
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // & PC with 00000000 00000000 11111111 11111111 to get immediate
    uint32_t immediate = PC&65535;
    // & PC with 00000011 11100000 00000000 00000000 and shift to get rs
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rs = PC&65011712;
    rs = rs>>21;
    //& PC with 00000000 00011111 00000000 00000000 and shift to get rt
    PC = mem_read_32(CURRENT_STATE.PC);
    uint32_t rt = PC&2031616;
    rt = rt>>16;
    //perform addition
    NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + immediate;
    //increment PC 
    NEXT_STATE.PC = CURRENT_STATE.PC + 4;
}
void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */
    // Obtain instruction in integer representation
    uint32_t PC = mem_read_32(CURRENT_STATE.PC);
    // examine the opcode and enter the appropriate function
    // & with this to obtain opcode and compare with other decimal representations to determine which function it is
    uint32_t temp = 4227858432; // 11111100 00000000 00000000 00000000 in decimal form
    uint32_t op = PC&temp;
    //if SPECIAL instruction
    PC = mem_read_32(CURRENT_STATE.PC);
    temp = 63; // 00000000 00000000 00000000 00111111 to get the opcode in the first 6 bits
    uint32_t opCode = PC&temp;
    //if REGIMM instruction, opcode is stored in bits 16 to 20
    PC = mem_read_32(CURRENT_STATE.PC);
    temp = 2031616; // 00000000 00011111 00000000 00000000 to get the opcode in the first 6 bits
    uint32_t type = PC&temp;
    switch(op) {
    
    //if addiu
    case 603979776:

        MIPS_addiu();
        break;
    
    
    //if addi
    case 536870912:
        MIPS_addi();
        break;

    //if slti
    case 671088640:
        MIPS_slti();
        break;

    //if sltiu
    case 738197504:
        MIPS_sltiu();
        break;

    //if andi
    case 805306368:
        MIPS_andi();
        break;

    //if ori
    case 872415232:
        MIPS_ori();
        break;

    //if xori
    case 939524096:
        MIPS_xori();
        break;

    //if lui
    case 1006632960:
        MIPS_lui();
        break;

    //if lb
    case 2147483648:
        MIPS_lb();
        break;

    //if lh
    case 2214592512:
        MIPS_lh();
        break;

    //if lw
    case 2348810240:
        MIPS_lw();
        break;

    //if lbu
    case 2415919104:
        MIPS_lbu();
        break;

    //if lhu
    case 2483027968:
        MIPS_lhu();
        break;

    // if sb
    case 2684354560:
        MIPS_sb();
        break;

    // if sh
    case 2751463424:
        MIPS_sh();
        break;

    // if sw
    case 2885681152:
        MIPS_sw();
        break;


    //if j
    case 134217728:
        MIPS_j();
        break;

    //if jal
    case 201326592:
        MIPS_jal();
        break;

    //if beq
    case 268435456:
        MIPS_beq();
        break;

    //if bne
    case 335544320:
        MIPS_bne();
        break;

    //if blez
    case 402653184:
        MIPS_blez();
        break;

    //if bgtz
    case 469762048:
        MIPS_bgtz();
        break;

    //if opcode is labeled special
    case 0:
        switch(opCode) {
            //if syscall
            case 12:
                MIPS_syscall();
                break;
        
            //if sll
            case 0:
                MIPS_sll();
                break;

            // if srl
            case 2:
                MIPS_srl();
                break;

            // if sra
            case 3:
                MIPS_sra();
                break;

            // if sllv
            case 4:
                MIPS_sllv();
                break;

            // if srlv
            case 6:
                MIPS_srlv();
                break;
            
            // if srav
            case 7:
                MIPS_srav();
                break;
            
            //if add
            case 32:
                MIPS_add();
                break;

            //if addu
            case 33:
                MIPS_addu();
                break;

            //if and
            case 36:
                MIPS_and();
                break;

            //if or
            case 37:
                MIPS_or();
                break;

            //if sub
            case 34:
                MIPS_sub();
                break;

            //if subu
            case 35:
                MIPS_subu();
                break;

            //if xor
            case 38:
                MIPS_xor();
                break;

            //if nor
            case 39:
                MIPS_nor();
                break;

            //if slt
            case 42:
                MIPS_slt();
                break;
        
            //if jr
            case 8:
                MIPS_jr();
                break;

            //if jalr
            case 9:
                MIPS_jalr();
                break;

            // if mfhi
            case 16:
                MIPS_mfhi();
                break;

            //if mflo
            case 18:
                MIPS_mflo();
                break;

            // if mthi
            case 17:
                MIPS_mthi();
                break;

            // if mtlo
            case 19:
                MIPS_mtlo();
                break;

            // if mult
            case 24:
                MIPS_mult();
                break;

            // if multu
            case 25:
                MIPS_multu();
                break;

            // if div
            case 26:
                MIPS_div();
                break;

            // if divu
            case 27:
                MIPS_divu();
                break;

        }
        break;
    // if opcode is REGIMM
    case 67108864:
    /*
        //if REGIMM instruction, opcode is stored in bits 16 to 20
        PC = mem_read_32(CURRENT_STATE.PC);
        temp = 2031616; // 00000000 00011111 00000000 00000000 to get the opcode in the first 6 bits
        uint32_t type = PC&temp;
        */
        switch(type) {
            //if bltz
            case 0:
                MIPS_bltz();
                break;

            //if bgez
            case 65536:
                MIPS_bgez();
                break;

            //if bltzal
            case 1048576:
                MIPS_bltzal();
                break;

            //if bgezal
            case 1114112:
                MIPS_bgezal();
                break;
        }
    }

}
