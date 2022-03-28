`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/26 11:23:00
// Design Name: 
// Module Name: PC
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


module PC(
    input RESET,
    input Clk,
    input [31:0] inAddress,
    output [31:0] outAddress
    );
    
    reg [31:0] OutAddress;
    reg [1:0] count;
    
    initial begin
    OutAddress = 0;
    count = 0;
    end
    
    always@(posedge Clk or RESET)
        begin
            if(RESET)
                OutAddress = 0;
            else
            begin
                count = count + 1;
                if (count == 2)
                begin
                OutAddress = inAddress;
                count = 0;
                end
            end
        end
        
    assign outAddress = OutAddress;
        
endmodule
