	component nios_practica is
		port (
			clk_clk            : in  std_logic                     := 'X';             -- clk
			div_freq_export    : out std_logic_vector(31 downto 0);                    -- export
			leds_export        : out std_logic_vector(7 downto 0);                     -- export
			noise_export       : out std_logic_vector(15 downto 0);                    -- export
			noise_en_export    : out std_logic;                                        -- export
			noise_pulse_export : out std_logic;                                        -- export
			reset_reset_n      : in  std_logic                     := 'X';             -- reset_n
			sel_nota_export    : out std_logic_vector(9 downto 0);                     -- export
			sw_export          : in  std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			uart_rxd           : in  std_logic                     := 'X';             -- rxd
			uart_txd           : out std_logic;                                        -- txd
			timer_export       : out std_logic                                         -- export
		);
	end component nios_practica;

	u0 : component nios_practica
		port map (
			clk_clk            => CONNECTED_TO_clk_clk,            --         clk.clk
			div_freq_export    => CONNECTED_TO_div_freq_export,    --    div_freq.export
			leds_export        => CONNECTED_TO_leds_export,        --        leds.export
			noise_export       => CONNECTED_TO_noise_export,       --       noise.export
			noise_en_export    => CONNECTED_TO_noise_en_export,    --    noise_en.export
			noise_pulse_export => CONNECTED_TO_noise_pulse_export, -- noise_pulse.export
			reset_reset_n      => CONNECTED_TO_reset_reset_n,      --       reset.reset_n
			sel_nota_export    => CONNECTED_TO_sel_nota_export,    --    sel_nota.export
			sw_export          => CONNECTED_TO_sw_export,          --          sw.export
			uart_rxd           => CONNECTED_TO_uart_rxd,           --        uart.rxd
			uart_txd           => CONNECTED_TO_uart_txd,           --            .txd
			timer_export       => CONNECTED_TO_timer_export        --       timer.export
		);

