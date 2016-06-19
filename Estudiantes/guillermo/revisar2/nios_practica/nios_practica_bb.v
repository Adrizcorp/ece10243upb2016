
module nios_practica (
	clk_clk,
	div_freq_export,
	karplus_strong_0_export,
	karplus_strong_1_export,
	karplus_strong_2_export,
	karplus_strong_3_export,
	karplus_strong_4_export,
	karplus_strong_5_export,
	leds_export,
	reset_reset_n,
	sw_export,
	uart_rxd,
	uart_txd);	

	input		clk_clk;
	output	[31:0]	div_freq_export;
	output	[15:0]	karplus_strong_0_export;
	output	[15:0]	karplus_strong_1_export;
	output	[15:0]	karplus_strong_2_export;
	output	[15:0]	karplus_strong_3_export;
	output	[15:0]	karplus_strong_4_export;
	output	[15:0]	karplus_strong_5_export;
	output	[7:0]	leds_export;
	input		reset_reset_n;
	input	[3:0]	sw_export;
	input		uart_rxd;
	output		uart_txd;
endmodule
