`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/26 10:41:33
// Design Name: 
// Module Name: InstMemory
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


module InstMemory(
    input [31:0] instAddress,
    output [31:0] inst
    );
    
    reg [31:0] instFile[0:15];
    reg [31:0] Inst;
    
    always@(instAddress)
        Inst = instFile[instAddress / 4];
        
    assign inst = Inst;
    
endmodule
