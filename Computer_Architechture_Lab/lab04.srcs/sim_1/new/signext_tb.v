`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/26 09:53:35
// Design Name: 
// Module Name: signext_tb
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


module signext_tb(

    );
    
    reg [15:0] Inst;
    wire [31:0] Data;
    
    signext u0(
        .inst(Inst),
        .data(Data)
    );
    
    initial begin
        Inst = 0;
        
        #100;
        Inst = 16'b0000000000000000;
        
        #100;
        Inst = 16'b0000000000000001;
        
        #100;
        Inst = 16'b1111111111111111;
        
        #100;
        Inst = 16'b0000000000000010;
        
        #100;
        Inst = 16'b1111111111111110;
        
    end
endmodule
