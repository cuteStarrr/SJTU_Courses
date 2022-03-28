`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/19 12:11:31
// Design Name: 
// Module Name: Registers
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


module Registers(
    input Reset,
    input Clk,
    input [25:21] readReg1,
    input [20:16] readReg2,
    input [4:0] writeReg,
    input [31:0] writeData,
    input regWrite,
    output [31:0] readData1,
    output [31:0] readData2
    );
    
    reg [31:0] regFile[31:0];
    reg [31:0] ReadData1;
    reg [31:0] ReadData2;
    
    
    always @ (Clk)
        begin
            ReadData1 = regFile[readReg1];
            ReadData2 = regFile[readReg2];
        end
    
   /* 
    always @ (readReg1 or readReg2)
        begin
            ReadData1 = regFile[readReg1];
            ReadData2 = regFile[readReg2];
        end
    */    
    always @ (posedge Clk or Reset)
        if(Reset)
            begin
                for(integer i = 0; i <= 31; i = i + 1)
                    regFile[i] = 0;
            end
        else
        begin
            if(regWrite)
                regFile[writeReg] = writeData;
        end
        
    assign readData1 = ReadData1;
    assign readData2 = ReadData2;
    
endmodule
