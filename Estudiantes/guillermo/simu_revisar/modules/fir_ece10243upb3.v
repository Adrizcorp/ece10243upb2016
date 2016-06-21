module fir_ece10243upb3(
		input clk,
		output [23:0]audio_out,
		input [15:0]coef_in,
		input clk_coef,
		input [3:0]sw,
		input [31:0]nco_inc,
		output [15:0]coef_current

);


reg [15:0]line_length[20:0];
reg [15:0]coef[20:0];
wire [31:0]multi[20:0];
wire [31:0]sum[20:0];
wire [11:0]seno;
wire [15:0]audio_in=seno[11:0];

initial $readmemh("D:\Material_FPGAs\simulaciones\coef.txt",coef);
assign coef_current[15:0]=coef[sw[3:0]][15:0];

always@(posedge clk)
begin
	line_length[0][15:0]<=audio_in[15:0];
end
always@(posedge clk_coef)
begin
	coef[0][15:0]<=coef_in[15:0];
end

assign multi[0][31:0]=line_length[0][15:0]*coef[0][15:0];
assign sum[0][31:0]=multi[20][31:0]+multi[19][31:0];
assign audio_out[23:0]=sum[19][31:8];   //escalar el numero 8 bits

waveform_gen waveform_gen_inst
(
.clk(clk) , // input clk_sig
.reset(1'b1) , // input reset_sig
.en(1'b1) , // input en_sig
.phase_inc(nco_inc[31:0]) , // input [31:0] phase_inc_sig
.sin_out(seno[11:0]) // output [11:0] sin_out_sig
);

genvar index2;
generate
	for(index2=19;index2>=1;index2=index2-1)
	begin: sumas
		assign sum[index2][31:0]=sum[index2-1][31:0]+multi[19-index2][31:0];
	
   end
endgenerate
genvar index;
generate
	for(index=20;index>=1;index=index-1)
	begin: delay_generate
	    assign multi[index][31:0]=line_length[index][15:0]*coef[index][15:0];
		always@(posedge clk)
		begin
			line_length[index][15:0]<=line_length[index-1][15:0];
		end
		always@(posedge clk_coef)
		begin
			coef[index][15:0]<=coef[index-1][15:0];
		end
		
	end
endgenerate

endmodule

