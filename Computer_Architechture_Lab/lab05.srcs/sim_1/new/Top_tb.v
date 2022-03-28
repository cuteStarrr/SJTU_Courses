`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/01 20:05:26
// Design Name: 
// Module Name: Top_tb
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


module Top_tb(

    );
    
    reg CLK;
    reg RESET;
    
    Top MIPS(
    .RESET(RESET),
    .CLK(CLK)
    );
    
    initial begin
        CLK = 0;
        RESET = 1;
        $readmemb("F:/archlabs/lab05/mem_inst.dat",MIPS.instMemory.instFile);
        $display("%b",MIPS.instMemory.instFile);
        $readmemh("F:/archlabs/lab05/mem_data.dat",MIPS.dataMem.memFile);
        $display("%h",MIPS.dataMem.memFile);
        #40 RESET = 0;
    end
    
    always #20 CLK = !CLK;
    
endmodule
