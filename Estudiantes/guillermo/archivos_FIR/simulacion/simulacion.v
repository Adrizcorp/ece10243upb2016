module simulacion(clk, SW, audio_out_fir,seno);

input clk;
input [2:0]SW;
output [23:0]audio_out_fir;
output [11:0]seno;



wire [31:0]nco_inc;
wire clk_44100hz;


fir_ece10243upb fir_ece10243upb_inst
(
	.clk(clk_44100hz) ,	// input  clk_sig
	.audio_in({{4{seno[11]}},seno[11:0]}) ,	// input [15:0] audio_in_sig
	.audio_out(audio_out_fir[23:0]) ,	// output [23:0] audio_out_sig
	.coef_in(16'd0) ,	// input [15:0] coef_in_sig
	.clk_coef(1'b0)
);

mux_nco_freq mux_nco_freq_inst
(
	.sel(SW[2:0]) ,	// input [2:0] sel_sig
	.out(nco_inc[31:0]) 	// output [31:0] out_sig
);
waveform_gen waveform_gen_inst
(
	.clk(clk) ,	// input  clk_sig
	.reset(1'b1) ,	// input  reset_sig
	.phase_inc(nco_inc[31:0]) ,	// input [31:0] phase_inc_sig
	.sin_out(seno[11:0]) 	// output [11:0] sin_out_sig
);


 div_freq div_freq_inst
(
	.clk(clk) ,	// input  clk_sig
	.in(32'd566) ,	// input [31:0] in_sig
	.div(clk_44100hz) 	// output  div_sig
);
endmodule
