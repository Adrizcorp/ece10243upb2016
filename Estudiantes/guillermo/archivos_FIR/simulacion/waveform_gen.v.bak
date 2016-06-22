module waveform_gen(
	 input clk ,
	 input reset,
	 input [31:0]phase_inc ,   
	 output [11:0]sin_out 

);

reg [31:0]phase_acc=32'd0;
reg [11:0]romcitaseno[4095:0];

initial $readmemh("D:\Material_FPGAs\SystemBuilder\CodeGenerated\FIR\simulacion\sin.txt",romcitaseno);
assign sin_out[11:0]=romcitaseno[phase_acc[31:20]][11:0];

always@(posedge clk, negedge reset)
begin
	if(!reset) phase_acc[31:0]<=32'd0;
	else phase_acc[31:0]<=phase_acc[31:0]+phase_inc[31:0];
end



endmodule

