`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/26 08:38:52
// Design Name: 
// Module Name: dataMemory
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


module dataMemory(
    input Clk,
    input [31:0] address,
    input [31:0] writeData,
    input memWrite,
    input memRead,
    output [31:0] readData
    );
    
    reg [31:0] memFile[0:31];
    reg [31:0] ReadData;
    
    always@(posedge Clk)
        begin
            if(memRead == 1)
                ReadData = memFile[address];
        end
    
    always@(negedge Clk)
        begin
            if(memWrite == 1)
                memFile[address] = writeData;
        end
        
    assign readData = ReadData;
endmodule
