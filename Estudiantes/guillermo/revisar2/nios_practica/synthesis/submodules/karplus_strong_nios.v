module karplus_strong_nios(
	input clk,
	input reset,
	input [2:0]address, 
	input chipselect,  ///AVALON io_chipselect
	input write, //AVALON io_wr
	input [31:0]writedata, //AVALON writedata io_write data
	output [31:0]readdata, //AVALON read_data io_read_data
	output irq,
	output [15:0]syn_guitar
);

reg [15:0]noise;
reg noise_en;
reg [9:0]sel_nota;
reg noise_pulse;
reg [31:0]div_freq_in;

wire wr_en= chipselect & write;
wire noise_wr=(address[2:0]==3'd0)? wr_en: 1'b0;
wire noise_en_wr=(address[2:0]==3'd1)? wr_en: 1'b0;
wire sel_nota_wr=(address[2:0]==3'd2)? wr_en: 1'b0;
wire noise_pulse_wr=(address[2:0]==3'd3)? wr_en: 1'b0;
wire div_freq_in_wr=(address[2:0]==3'd4)? wr_en: 1'b0;

assign readdata[31:0]=(address[2:0]==3'd0)? ({16'd0,noise[15:0]}):
							 (address[2:0]==3'd1)? ({31'd0,noise_en}):
							 (address[2:0]==3'd2)? ({22'd0,sel_nota[9:0]}):
							 (address[2:0]==3'd3)? ({31'd0,noise_pulse}):
							 (div_freq_in[31:0]);

reg [15:0]line_length[499:0];
//wire [15:0]mux_ins[699:0];
reg [15:0]z=16'd65000;
wire [15:0]current_value=line_length[sel_nota[9:0]][15:0];
wire [15:0]feedback=  current_value[15:1] + z[15:1];
wire clk_div_freq;
wire clock=noise_en ? noise_pulse : clk_div_freq;
assign syn_guitar[15:0]=noise_en ? 16'd0: feedback[15:0];

 div_freq div_freq_inst
(
	.clk(clk) ,	// input  clk_sig
	.in(div_freq_in[31:0]) ,	// input [31:0] in_sig
	.div(clk_div_freq) 	// output  div_sig
);

always@(posedge clock)
begin
	noise[15:0]<=noise[15:0];
	noise_en<=noise_en;
	sel_nota[9:0]<=sel_nota[9:0];
	noise_pulse<=noise_pulse;
	div_freq_in[31:0]=div_freq_in[31:0];
	if(noise_wr)
	begin
		noise[15:0]<=writedata[15:0];
	end
	if(noise_en_wr)
	begin
		noise_en<=writedata[0];
	end
	if(sel_nota_wr)
	begin
		sel_nota[9:0]<=writedata[9:0];
	end
	if(noise_pulse_wr)
	begin
		noise_pulse<=writedata[0];
	end
	if(div_freq_in_wr)
	begin
		div_freq_in[31:0]<=writedata[31:0];
	end
end



always@(posedge clock)
begin
	z[15:0]<=current_value[15:0];
	line_length[0][15:0]<=noise_en? noise[15:0]:feedback[15:0];
end

genvar index;
generate
	for(index=499;index>=1;index=index-1)
	begin: delay_generate
	//	assign mux_ins[index][15:0]=line_length[index][15:0];
		always@(posedge clock)
		begin
			line_length[index][15:0]<=line_length[index-1][15:0];
		end
		
	end
endgenerate

endmodule
