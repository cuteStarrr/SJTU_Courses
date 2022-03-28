`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/29 15:51:15
// Design Name: 
// Module Name: Mux5
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


module Mux5(
    input ctrSignal,
    input [4:0] input1,
    input [4:0] input2,
    output [4:0] result
    );
    
    assign result = ctrSignal ? input1 : input2;
    
endmodule
