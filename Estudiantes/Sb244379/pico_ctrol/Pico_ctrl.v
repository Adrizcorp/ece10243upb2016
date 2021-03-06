
//=======================================================
//  This code is generated by Terasic System Builder
//=======================================================

module Pico_ctrl(

	//////////// CLOCK //////////
	input 		          		FPGA_CLK1_50,
	input 		          		FPGA_CLK2_50,
	input 		          		FPGA_CLK3_50,

	//////////// KEY //////////
	input 		     [1:0]		KEY,

	//////////// LED //////////
	output		     [7:0]		LED,

	//////////// SW //////////
	input 		     [3:0]		SW
);



//=======================================================
//  REG/WIRE declarations
//=======================================================



wire [4:0]picoCtrl32_rom;
wire [15:0]instruction;
wire clk_1hz,clk_1hz_sync;

//=======================================================
//  Structural coding
//=======================================================



PicoCtrl_rom32_instructions PicoCtrl_rom32_instructions_inst
(
	.addr(picoCtrl32_rom[4:0]) ,	// input [4:0] addr_sig
	.data(instruction[15:0]) 	// output [15:0] data_sig
);

picoctrl picoctrl_inst
(
	.clk(FPGA_CLK1_50) ,	// input  clk_sig
	.res_n(1'b1) ,	// input  res_n_sig
	.cond_1(clk_1hz) ,	// input  cond_1_sig
	.cond_2(1'b0) ,	// input  cond_2_sig
	.cond_3(1'b0) ,	// input  cond_3_sig
	.cond_4(1'b0) ,	// input  cond_4_sig
	.cond_5(1'b0) ,	// input  cond_5_sig
	.cond_6(1'b0) ,	// input  cond_6_sig
	.reg_0() ,	// output [7:0] reg_0_sig
	.reg_1(LED[7:0]) ,	// output [7:0] reg_1_sig
	.reg_2() ,	// output [7:0] reg_2_sig
	.reg_3() ,	// output [7:0] reg_3_sig
	.instruction_ROM_Addr(picoCtrl32_rom[4:0]) ,	// output [4:0] instruction_ROM_Addr_sig
	.instruction_ROM_data(instruction[15:0]) 	// input [15:0] instruction_ROM_data_sig
);
div_freq div_freq_inst
(
	.clk(FPGA_CLK1_50) ,	// input  clk_sig
	.in(32'd49_999_999) ,	// input [31:0] in_sig
	.div(clk_1hz) 	// output  div_sig
);

syncro syncro_inst
(
	.async(clk_1hz) ,	// input  async_sig
	.clock(FPGA_CLK1_50) ,	// input  clock_sig
	.sync(clk_1hz_sync) 	// output  sync_sig
);


endmodule
