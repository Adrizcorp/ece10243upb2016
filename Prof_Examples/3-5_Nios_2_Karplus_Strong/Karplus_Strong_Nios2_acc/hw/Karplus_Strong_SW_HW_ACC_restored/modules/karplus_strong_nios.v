module karplus_strong_nios(
			input clk,
			input [15:0]noise,
			input noise_en,
			input [9:0]sel_nota,
			input noise_pulse,
			input [31:0]div_freq_in,
			output [15:0]syn_guitar
	);

reg [15:0]line_length[699:0];
//wire [15:0]mux_ins[699:0];
reg [15:0]z=16'd65000;
wire [15:0]current_value=line_length[sel_nota[9:0]][15:0];
wire [15:0]feedback= current_value[15:1] + z[15:1];
wire clk_div_freq;
wire clock= noise_en ? noise_pulse: clk_div_freq;
assign syn_guitar[15:0]=noise_en? 16'd0:feedback[15:0];

 div_freq div_freq_inst
(
	.clk(clk) ,	// input  clk_sig
	.in(div_freq_in[31:0]) ,	// input [31:0] in_sig
	.div(clk_div_freq) 	// output  div_sig
);

always@(posedge clock)
begin
	z[15:0]<=current_value[15:0];
	line_length[0][15:0]<=noise_en? noise[15:0]: feedback[15:0];
end

genvar index;
generate
	for (index=699; index >= 1; index=index-1)
	begin: delay_generate
			//assign mux_ins[index][15:0]=line_length[index][15:0];
			always@(posedge clock)
				begin
					line_length[index][15:0]<=line_length[index-1][15:0];
				end
	
	end
endgenerate	
	
endmodule
