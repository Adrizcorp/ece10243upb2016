//Modified by Holguer A. Becera 2014

`timescale 100 ps / 10 ps
`define MSBI 15 // Most significant Bit of DAC input
//This is a Delta-Sigma Digital to Analog Converter
module dac_nano(DACout, DACin, Clk, Reset);
output DACout; // This is the average output that feeds low pass filter
reg DACout; // for optimum performance, ensure that this ff is in IOB
input [`MSBI:0] DACin; // DAC input (excess 2**MSBI)
input Clk;
input Reset;
reg [`MSBI+2:0] DeltaAdder; // Output of Delta adder
reg [`MSBI+2:0] SigmaAdder; // Output of Sigma adder
reg [`MSBI+2:0] SigmaLatch; // Latches output of Sigma adder
reg [`MSBI+2:0] DeltaB; // B input of Delta adder
	
	
	always @(SigmaLatch) 
	begin
		DeltaB = {SigmaLatch[`MSBI+2], SigmaLatch[`MSBI+2]} << (`MSBI+1);
	end	
	 
	always @(DACin or DeltaB)
	begin
		DeltaAdder = DACin + DeltaB;
	end	
	
	always @(DeltaAdder or SigmaLatch) 
	begin
		SigmaAdder = DeltaAdder + SigmaLatch;
	end	
	
	always @(posedge Clk or posedge Reset)
	begin
	if(Reset)
	begin
		SigmaLatch <= #1 1'b1 << (`MSBI+1);
		DACout <= #1 1'b0;
	end
	else
	begin
		SigmaLatch <= #1 SigmaAdder;
		DACout <= #1 SigmaLatch[`MSBI+2];
	end
	end
endmodule

