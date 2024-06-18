#ifndef TYPES_H
#define TYPES_H
enum class Opcode {
    ADD = 0b0110011,
    SUB = 0b0110111,
    LW = 0b0000011,
    SW = 0b0100011,
    BEQ = 0b1100011,
    JAL = 0b1101111,
    HALT = 0b0000000, // Custom opcode for halting the processor
    NOP = 0b0000001
};
typedef uint64_t Addr;
struct Instruction {
    Opcode opcode;
    int rd;
    int rs1;
    int rs2;
    int imm;
    bool dest_needed;
    bool src1_needed;
    bool src2_needed;
    int src1_tag;
    int src2_tag;
    bool src1_ready;
    bool src2_ready;
    int destTag;
    int inst_num;
    int exe_wait_cycles;
    Instruction():opcode(Opcode::HALT), rd(-1), rs1(-1), rs2(-1), imm(0),
          dest_needed(false), src1_needed(false), src2_needed(false),
          src1_tag(-1), src2_tag(-1), src1_ready(false), src2_ready(false),
          destTag(-1), inst_num(-1), exe_wait_cycles(0) {}
    Instruction(Opcode op, int rd, int rs1, int rs2, int imm,
                bool dest_needed, bool src1_needed, bool src2_needed,
                int src1_tag, int src2_tag, bool src1_ready, bool src2_ready,
                int destTag, int inst_num, int exe_wait_cycles)
        : opcode(op), rd(rd), rs1(rs1), rs2(rs2), imm(imm),
          dest_needed(dest_needed), src1_needed(src1_needed), src2_needed(src2_needed),
          src1_tag(src1_tag), src2_tag(src2_tag), src1_ready(src1_ready), src2_ready(src2_ready),
          destTag(destTag), inst_num(inst_num), exe_wait_cycles(exe_wait_cycles) {}

};



#endif
