	nios_practica u0 (
		.clk_clk            (<connected-to-clk_clk>),            //         clk.clk
		.div_freq_export    (<connected-to-div_freq_export>),    //    div_freq.export
		.leds_export        (<connected-to-leds_export>),        //        leds.export
		.reset_reset_n      (<connected-to-reset_reset_n>),      //       reset.reset_n
		.sw_export          (<connected-to-sw_export>),          //          sw.export
		.uart_rxd           (<connected-to-uart_rxd>),           //        uart.rxd
		.uart_txd           (<connected-to-uart_txd>),           //            .txd
		.noise_export       (<connected-to-noise_export>),       //       noise.export
		.noise_en_export    (<connected-to-noise_en_export>),    //    noise_en.export
		.sel_nota_export    (<connected-to-sel_nota_export>),    //    sel_nota.export
		.noise_pulse_export (<connected-to-noise_pulse_export>)  // noise_pulse.export
	);

