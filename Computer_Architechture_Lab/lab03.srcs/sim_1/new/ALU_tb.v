`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/19 11:24:51
// Design Name: 
// Module Name: ALU_tb
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


module ALU_tb(

    );
    
    reg [31:0] Input1;
    reg [31:0] Input2;
    reg [3:0] ALUCtr;
    wire Zero;
    wire [31:0] ALURes;
     
    ALU u0(
    .input1(Input1),
    .input2(Input2),
    .aluCtr(ALUCtr),
    .zero(Zero),
    .aluRes(ALURes)
    );
    
    initial begin
    
        Input1 = 15;
        Input2 = 10;
        ALUCtr = 0;
    
        #100;
    
        #100; //and
        ALUCtr = 4'b0000;
    
        #100; //or
        ALUCtr = 4'b0001;
    
        #100; //add
        ALUCtr = 4'b0010;
    
        #100; //sub
        ALUCtr = 4'b0110;
    
        #100; //sub ,input1 = input2
        ALUCtr = 4'b0110;
        Input1 = 10;
    
        #100; // set on less than,input1 > input2
        ALUCtr = 4'b0111;
        Input1 = 15;
    
        #100; // set on less than,input1 < input2
        ALUCtr = 4'b0111;
        Input1 = 5;
    
        #100; // nor
        ALUCtr = 4'b1100;
        
    end
    
endmodule
