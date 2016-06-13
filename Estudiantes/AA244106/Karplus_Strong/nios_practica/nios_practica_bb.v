
module nios_practica (
	clk_clk,
	div_freq_export,
	leds_export,
	noise_export,
	noise_en_export,
	noise_pulse_export,
	reset_reset_n,
	sel_nota_export,
	sw_export,
	uart_rxd,
	uart_txd,
	timer_export);	

	input		clk_clk;
	output	[31:0]	div_freq_export;
	output	[7:0]	leds_export;
	output	[15:0]	noise_export;
	output		noise_en_export;
	output		noise_pulse_export;
	input		reset_reset_n;
	output	[9:0]	sel_nota_export;
	input	[3:0]	sw_export;
	input		uart_rxd;
	output		uart_txd;
	output		timer_export;
endmodule
