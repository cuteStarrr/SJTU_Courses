`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/02 19:31:34
// Design Name: 
// Module Name: Top_Multi
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


module Top_Multi(

    input RESET,
    input CLK

    );

    wire [31:0] IF_INST_W;
    wire [31:0] IF_PC4_W;
    reg [31:0] IF_PC4_R;
    wire [31:0] INST_ADDRESS;
    reg [31:0] IN_ADDRESS;
    
    InstMemory instMemory(
        .instAddress(INST_ADDRESS[31:0]),
        .inst(IF_INST_W[31:0])
    );
    
    PC Pc(
        .RESET(RESET),
        .Clk(CLK),
        .inAddress(IN_ADDRESS[31:0]),
        .outAddress(INST_ADDRESS[31:0])
    );

    ALU PCadder(
        .input1(INST_ADDRESS[31:0]),
        .input2(4),
        .aluCtr(4'b0010),
        .aluRes(IF_PC4_W[31:0])
    );

    wire [4:0] WRITE_REG;
    wire [31:0] WRITE_DATA;
    reg [31:0] ID_REG_READ_DATA1;
    reg [31:0] ID_REG_READ_DATA2;
    wire [31:0] ID_REG_READ_DATA1_W;
    wire [31:0] ID_REG_READ_DATA2_W;
    wire REG_WRITE;
    reg [31:0] IF_INST_R;
    reg [4:0] REG_READ_1;
    reg [4:0] REG_READ_2;

    Registers register (
        .Reset(RESET),
        .Clk(CLK),
        .readReg1(IF_INST_R[25:21]),
        .readReg2(IF_INST_R[20:16]),
        .writeReg(WRITE_REG),
        .writeData(WRITE_DATA),
        .regWrite(REG_WRITE),
        .readData1(ID_REG_READ_DATA1_W),
        .readData2(ID_REG_READ_DATA2_W)
    );

    reg [31:0] ID_SIGNEXT_OUT;
    wire [31:0] ID_SIGNEXT_OUT_W;

    signext SignExt(
        .inst(IF_INST_R[15:0]),
        .data(ID_SIGNEXT_OUT_W)
    );

    reg ID_REG_DST;
    reg ID_ALU_SRC;
    reg ID_MEM_TO_REG;
    reg ID_REG_WRITE;
    reg ID_MEM_READ;
    reg ID_MEM_WRITE;
    reg ID_BRANCH;
    reg [1:0] ID_ALU_OP;
    reg ID_JUMP;
    wire ID_REG_DST_W;
    wire ID_ALU_SRC_W;
    wire ID_MEM_TO_REG_W;
    wire ID_REG_WRITE_W;
    wire ID_MEM_READ_W;
    wire ID_MEM_WRITE_W;
    wire ID_BRANCH_W;
    wire [1:0] ID_ALU_OP_W;
    wire ID_JUMP_W;
    
    Ctr mainCtr(
        .opCode(IF_INST_R[31:26]),
        .regDst(ID_REG_DST_W),
        .aluSrc(ID_ALU_SRC_W),
        .memToReg(ID_MEM_TO_REG_W),
        .regWrite(ID_REG_WRITE_W),
        .memRead(ID_MEM_READ_W),
        .memWrite(ID_MEM_WRITE_W),
        .branch(ID_BRANCH_W),
        .aluOp(ID_ALU_OP_W),
        .jump(ID_JUMP_W)
    );

    reg [31:0] ID_PC4;
    reg [4:0] ID_INST_0;
    reg [4:0] ID_INST_1;
    reg [4:0] EX_WRITE_REG;
    wire [4:0] EX_WRITE_REG_W;

    Mux5 muxWriteReg(
        .ctrSignal(ID_REG_DST),
        .input1(ID_INST_1),
        .input2(ID_INST_0),
        .result(EX_WRITE_REG_W)
    );

    wire [31:0] ALU_INPUT;

    Mux muxAluInput (
        .ctrSignal(ID_ALU_SRC),
        .input1(ID_SIGNEXT_OUT),
        .input2(ID_REG_READ_DATA2),
        .result(ALU_INPUT)
    );

    wire [3:0] ALUCTR_OUT;

    ALUCtr ALUCTR(
        .aluOp(ID_ALU_OP),
        .funct(ID_SIGNEXT_OUT[5:0]),
        .aluCtrOut(ALUCTR_OUT[3:0])
    );

    reg EX_ZERO;
    wire EX_ZERO_W;
    reg [31:0] EX_DATA_MEM_ADDRESS;
    wire [31:0] EX_DATA_MEM_ADDRESS_W;

    ALU Alu(
        .input1(ID_REG_READ_DATA1),
        .input2(ALU_INPUT),
        .aluCtr(ALUCTR_OUT[3:0]),
        .zero(EX_ZERO_W),
        .aluRes(EX_DATA_MEM_ADDRESS_W[31:0])
    );

    reg [31:0] EX_addALU_OUT;
    wire [31:0] EX_addALU_OUT_W;

    ALU addALU(
        .input1(ID_PC4),
        .input2(ID_SIGNEXT_OUT << 2),
        .aluCtr(4'b0010),
        .aluRes(EX_addALU_OUT_W)
    );

    reg [31:0] EX_REG_READ_DATA2;
    reg EX_REG_WRITE;
    reg EX_MEM_READ;
    reg EX_MEM_WRITE;
    reg EX_BRANCH;
    reg EX_MEM_TO_REG;
    reg EX_JUMP;
    
    wire [31:0] NO_JUMP_ADDRESS;
    wire BRANCH = EX_BRANCH & EX_ZERO;

    Mux mux_BRANCH(
        .ctrSignal(BRANCH),
        .input1(EX_addALU_OUT),
        .input2(IF_PC4_W),
        .result(NO_JUMP_ADDRESS[31:0])
    );   
    
    wire [31:0] IN_ADDRESS_W;
    
    Mux mux_JUMP(
        .ctrSignal(ID_JUMP_W),
        .input1((IF_INST_R[25:0] << 2) + (IF_PC4_R & 32'hF0000000)),
        .input2(NO_JUMP_ADDRESS),
        .result(IN_ADDRESS_W[31:0])
    );
    
    reg [31:0] MEM_dataMem_READ_DATA;
    wire [31:0] MEM_dataMem_READ_DATA_W;

    dataMemory dataMem(
        .Clk(CLK),
        .address(EX_DATA_MEM_ADDRESS[31:0]),
        .writeData(EX_REG_READ_DATA2),
        .memWrite(EX_MEM_WRITE),
        .memRead(EX_MEM_READ),
        .readData(MEM_dataMem_READ_DATA_W[31:0])
    );

    reg [31:0] MEM_DATA_MEM_ADDRESS;
    reg MEM_REG_WRITE;
    reg MEM_MEM_TO_REG;
    reg MEM_JUMP;
    reg [4:0] MEM_WRITE_REG;
    
    assign WRITE_REG = MEM_WRITE_REG;
    assign REG_WRITE = MEM_REG_WRITE;

    Mux muxWriteData(
        .ctrSignal(MEM_MEM_TO_REG),
        .input1(MEM_dataMem_READ_DATA),
        .input2(MEM_DATA_MEM_ADDRESS[31:0]),
        .result(WRITE_DATA)
    );
    
    wire STALL = REG_WRITE & ((MEM_WRITE_REG == REG_READ_1) | (MEM_WRITE_REG == REG_READ_2)); 
    
    always @ (RESET)
        begin
            if(RESET)
                begin
                    IF_PC4_R = 0;
                    ID_REG_READ_DATA1 = 0;
                    ID_REG_READ_DATA2 = 0;
                    IF_INST_R = 0;
                    ID_SIGNEXT_OUT = 0;
                    ID_REG_DST = 0;
                    ID_ALU_SRC = 0;
                    ID_MEM_TO_REG = 0;
                    ID_REG_WRITE = 0;
                    ID_MEM_READ = 0;
                    ID_MEM_WRITE = 0;
                    ID_BRANCH = 0;
                    ID_ALU_OP = 0;
                    ID_JUMP = 0;
                    ID_PC4 = 0;
                    ID_INST_0 = 0;
                    ID_INST_1 = 0;
                    EX_WRITE_REG = 0;
                    EX_ZERO = 0;
                    EX_DATA_MEM_ADDRESS = 0;
                    EX_addALU_OUT = 0;
                    EX_REG_READ_DATA2 = 0;
                    EX_REG_WRITE = 0;
                    EX_MEM_READ = 0;
                    EX_MEM_WRITE = 0;
                    EX_BRANCH = 0;
                    EX_MEM_TO_REG = 0;
                    EX_JUMP = 0;
                    MEM_dataMem_READ_DATA = 0;
                    MEM_DATA_MEM_ADDRESS = 0;
                    MEM_REG_WRITE = 0;
                    MEM_MEM_TO_REG = 0;
                    MEM_JUMP = 0;
                    MEM_WRITE_REG = 0;
                end
        end
    
    always @ (posedge CLK)
        begin
            if(STALL || BRANCH)
                begin
                    ID_REG_READ_DATA1 <= 0;
                    ID_REG_READ_DATA2 <= 0;
                    ID_SIGNEXT_OUT <= 0;
                    ID_REG_DST <= 0;
                    ID_ALU_SRC <= 0;
                    ID_MEM_TO_REG <= 0;
                    ID_REG_WRITE <= 0;
                    ID_MEM_READ <= 0;
                    ID_MEM_WRITE <= 0;
                    ID_BRANCH <= 0;
                    ID_ALU_OP <= 0;
                    ID_JUMP <= 0;
                    ID_PC4 <= 0;
                    ID_INST_0 <= 0;
                    ID_INST_1 <= 0;
                    EX_MEM_READ <= 0;
                    EX_MEM_WRITE <= 0;
                    IN_ADDRESS <= IN_ADDRESS - 12;
                end
            IN_ADDRESS <= IN_ADDRESS_W;
            IF_INST_R <= IF_INST_W;
            IF_PC4_R <= IF_PC4_W;
            ID_PC4 <= IF_PC4_R[31:0];
            ID_INST_0 <= IF_INST_R[20:16];
            ID_INST_1 <= IF_INST_R[15:11];
            ID_REG_READ_DATA1 <= ID_REG_READ_DATA1_W;
            ID_REG_READ_DATA2 <= ID_REG_READ_DATA2_W;
            ID_SIGNEXT_OUT <= ID_SIGNEXT_OUT_W;
            ID_REG_DST <= ID_REG_DST_W;
            ID_ALU_SRC <= ID_ALU_SRC_W;
            ID_MEM_TO_REG <= ID_MEM_TO_REG_W;
            ID_REG_WRITE <= ID_REG_WRITE_W;
            ID_MEM_READ <= ID_MEM_READ_W;
            ID_MEM_WRITE <= ID_MEM_WRITE_W;
            ID_BRANCH <= ID_BRANCH_W;
            ID_ALU_OP <= ID_ALU_OP_W;
            ID_JUMP <= ID_JUMP_W;
            REG_READ_1 <= IF_INST_R[25:21];
            REG_READ_2 <= IF_INST_R[20:16];

            EX_REG_READ_DATA2 <= ID_REG_READ_DATA2[31:0];
            EX_REG_WRITE <= ID_REG_WRITE;
            EX_MEM_READ <= ID_MEM_READ;
            EX_MEM_WRITE <= ID_MEM_WRITE;
            EX_BRANCH <= ID_BRANCH;
            EX_MEM_TO_REG <= ID_MEM_TO_REG;
            EX_JUMP <= ID_JUMP;
            EX_ZERO <= EX_ZERO_W;
            EX_DATA_MEM_ADDRESS <= EX_DATA_MEM_ADDRESS_W;
            EX_addALU_OUT <= EX_addALU_OUT_W;

            MEM_DATA_MEM_ADDRESS <= EX_DATA_MEM_ADDRESS[31:0];
            MEM_REG_WRITE <= EX_REG_WRITE;
            MEM_MEM_TO_REG <= EX_MEM_TO_REG;
            MEM_JUMP <= EX_JUMP;
            MEM_WRITE_REG <= EX_WRITE_REG;
            MEM_dataMem_READ_DATA <= MEM_dataMem_READ_DATA_W;
            EX_WRITE_REG <= EX_WRITE_REG_W;
            
            if((REG_READ_1 == EX_WRITE_REG) && (EX_MEM_TO_REG == 0) && (RESET == 0))
                begin
                    ID_REG_READ_DATA1 <= EX_DATA_MEM_ADDRESS;
                end
            else if((REG_READ_2 == EX_WRITE_REG) && (EX_MEM_TO_REG == 0) && (RESET == 0))
                begin
                    ID_REG_READ_DATA2 <= EX_DATA_MEM_ADDRESS;
                end
            else if((MEM_WRITE_REG == REG_READ_1) && (MEM_MEM_TO_REG == 0) && (RESET == 0))
                begin
                    ID_REG_READ_DATA1 <= EX_DATA_MEM_ADDRESS;
                end
            else if((MEM_WRITE_REG == REG_READ_2) && (MEM_MEM_TO_REG == 0) && (RESET == 0))
                begin
                    ID_REG_READ_DATA2 <= EX_DATA_MEM_ADDRESS;
                end   
            
        end
    
    
endmodule

//JUMP? 