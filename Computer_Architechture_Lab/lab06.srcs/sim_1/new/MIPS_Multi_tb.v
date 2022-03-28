`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/03 22:09:02
// Design Name: 
// Module Name: MIPS_Multi_tb
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


module MIPS_Multi_tb(

    );
    
    reg CLK;
    reg RESET;
    
    Top_Multi MIPS_Multi(
    .RESET(RESET),
    .CLK(CLK)
    );
    
    initial begin
        CLK = 0;
        RESET = 1;
        $readmemb("F:/archlabs/lab06/mem_inst.dat",MIPS_Multi.instMemory.instFile);
        $display("%b",MIPS_Multi.instMemory.instFile);
        $readmemh("F:/archlabs/lab06/mem_data.dat",MIPS_Multi.dataMem.memFile);
        $display("%h",MIPS_Multi.dataMem.memFile);
        #40 RESET = 0;
    end
    
    always #20 CLK = !CLK;
    
endmodule
