`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/26 09:43:41
// Design Name: 
// Module Name: signext
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


module signext(
    input [15:0] inst,
    output [31:0] data
    );
    
    reg [31:0] Data;
    
    always@(inst)
        begin
            if(inst < 16'b1000000000000000)
                Data = 32'b00000000000000000000000000000000 | inst;
            else
                Data = 32'b11111111111111110000000000000000 | inst;
                //begin
                //    Data = ~inst + 1;
               //     Data = 32'b00000000000000000000000000000000 | Data;
                //    Data = ~Data + 1;
              //  end
        end
        
    assign data = Data;
    
endmodule
