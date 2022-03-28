`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/26 10:50:30
// Design Name: 
// Module Name: Top
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Top(
    input RESET,
    input CLK
    );
    
    wire REG_DST,
    JUMP,
    BRANCH,
    MEM_READ,
    MEM_TO_REG,
    MEM_WRITE;
    wire [1:0] ALU_OP;
    wire ALU_SRC,
    REG_WRITE;
    wire [31:0] INST;
    wire [31:0] INST_ADDRESS;
    wire [31:0] IN_ADDRESS;
    wire [4:0] WRITE_REG;
    wire [31:0] WRITE_DATA;
    wire [31:0] REG_READ_DATA1;
    wire [31:0] REG_READ_DATA2;
    wire [31:0] SIGNEXT_OUT;
    wire [31:0] ALU_INPUT;
    wire ZERO;
    wire [31:0] DATA_MEM_ADDRESS;
    wire [3:0] ALUCTR_OUT;
    wire [31:0] dataMem_READ_DATA;
    wire [31:0] PC4;
    wire [31:0] addALU_OUT;
    wire [31:0] muxToMux_OUT;
    
    
    Ctr mainCtr(
        .opCode(INST[31:26]),
        .regDst(REG_DST),
        .aluSrc(ALU_SRC),
        .memToReg(MEM_TO_REG),
        .regWrite(REG_WRITE),
        .memRead(MEM_READ),
        .memWrite(MEM_WRITE),
        .branch(BRANCH),
        .aluOp(ALU_OP),
        .jump(JUMP)
    );
    
    InstMemory instMemory(
        .instAddress(INST_ADDRESS[31:0]),
        .inst(INST[31:0])
    );
    
    PC Pc(
        .RESET(RESET),
        .Clk(CLK),
        .inAddress(IN_ADDRESS[31:0]),
        .outAddress(INST_ADDRESS[31:0])
    );
    
    Mux5 muxWriteReg(
        .ctrSignal(REG_DST),
        .input1(INST[15:11]),
        .input2(INST[20:16]),
        .result(WRITE_REG[4:0])
    );
    
    Registers register (
        .Reset(RESET),
        .Clk(CLK),
        .readReg1(INST[25:21]),
        .readReg2(INST[20:16]),
        .writeReg(WRITE_REG),
        .writeData(WRITE_DATA),
        .regWrite(REG_WRITE),
        .readData1(REG_READ_DATA1),
        .readData2(REG_READ_DATA2)
    );
    
    signext SignExt(
        .inst(INST[15:0]),
        .data(SIGNEXT_OUT)
    );
    
    Mux muxAluInput (
        .ctrSignal(ALU_SRC),
        .input1(SIGNEXT_OUT),
        .input2(REG_READ_DATA2),
        .result(ALU_INPUT)
    );
    
    ALU Alu(
        .input1(REG_READ_DATA1),
        .input2(ALU_INPUT),
        .aluCtr(ALUCTR_OUT[3:0]),
        .zero(ZERO),
        .aluRes(DATA_MEM_ADDRESS[31:0])
    );
    
    ALUCtr ALUCTR(
        .aluOp(ALU_OP),
        .funct(INST[5:0]),
        .aluCtrOut(ALUCTR_OUT[3:0])
    );
    
    dataMemory dataMem(
        .Clk(CLK),
        .address(DATA_MEM_ADDRESS[31:0]),
        .writeData(REG_READ_DATA2),
        .memWrite(MEM_WRITE),
        .memRead(MEM_READ),
        .readData(dataMem_READ_DATA)
    );
    
    Mux muxWriteData(
        .ctrSignal(MEM_TO_REG),
        .input1(dataMem_READ_DATA),
        .input2(DATA_MEM_ADDRESS[31:0]),
        .result(WRITE_DATA)
    );
   
    ALU PCadder(
        .input1(INST_ADDRESS),
        .input2(4),
        .aluCtr(4'b0010),
        //.zero(0),
        .aluRes(PC4)
    );
    
    /*
    always @ (posedge CLK)
        PC4 <= INST_ADDRESS + 4;
    */
    
    ALU addALU(
        .input1(PC4),
        .input2(SIGNEXT_OUT << 2),
        .aluCtr(4'b0010),
        //.zero(0),
        .aluRes(addALU_OUT)
    );
    
    Mux muxToMux(
        .ctrSignal(BRANCH & ZERO),
        .input1(addALU_OUT),
        .input2(PC4),
        .result(muxToMux_OUT)
    );
    
    Mux muxToPC(
        .ctrSignal(JUMP),
        .input1((INST[25:0] << 2) + (PC4 & 32'hF0000000)),
        .input2(muxToMux_OUT),
        .result(IN_ADDRESS[31:0])
    );
    
endmodule
