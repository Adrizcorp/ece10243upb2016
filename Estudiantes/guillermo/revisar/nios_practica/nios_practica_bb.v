
module nios_practica (
	clk_clk,
	div_freq_export,
	leds_export,
	reset_reset_n,
	sw_export,
	uart_rxd,
	uart_txd,
	noise_export,
	noise_en_export,
	sel_nota_export,
	noise_pulse_export);	

	input		clk_clk;
	output	[31:0]	div_freq_export;
	output	[7:0]	leds_export;
	input		reset_reset_n;
	input	[3:0]	sw_export;
	input		uart_rxd;
	output		uart_txd;
	output	[15:0]	noise_export;
	output		noise_en_export;
	output	[9:0]	sel_nota_export;
	output		noise_pulse_export;
endmodule
