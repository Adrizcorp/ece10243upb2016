	component nios_practica is
		port (
			clk_clk                 : in  std_logic                     := 'X';             -- clk
			div_freq_export         : out std_logic_vector(31 downto 0);                    -- export
			karplus_strong_0_export : out std_logic_vector(15 downto 0);                    -- export
			karplus_strong_1_export : out std_logic_vector(15 downto 0);                    -- export
			karplus_strong_2_export : out std_logic_vector(15 downto 0);                    -- export
			karplus_strong_3_export : out std_logic_vector(15 downto 0);                    -- export
			karplus_strong_4_export : out std_logic_vector(15 downto 0);                    -- export
			karplus_strong_5_export : out std_logic_vector(15 downto 0);                    -- export
			leds_export             : out std_logic_vector(7 downto 0);                     -- export
			reset_reset_n           : in  std_logic                     := 'X';             -- reset_n
			sw_export               : in  std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			uart_rxd                : in  std_logic                     := 'X';             -- rxd
			uart_txd                : out std_logic                                         -- txd
		);
	end component nios_practica;

	u0 : component nios_practica
		port map (
			clk_clk                 => CONNECTED_TO_clk_clk,                 --              clk.clk
			div_freq_export         => CONNECTED_TO_div_freq_export,         --         div_freq.export
			karplus_strong_0_export => CONNECTED_TO_karplus_strong_0_export, -- karplus_strong_0.export
			karplus_strong_1_export => CONNECTED_TO_karplus_strong_1_export, -- karplus_strong_1.export
			karplus_strong_2_export => CONNECTED_TO_karplus_strong_2_export, -- karplus_strong_2.export
			karplus_strong_3_export => CONNECTED_TO_karplus_strong_3_export, -- karplus_strong_3.export
			karplus_strong_4_export => CONNECTED_TO_karplus_strong_4_export, -- karplus_strong_4.export
			karplus_strong_5_export => CONNECTED_TO_karplus_strong_5_export, -- karplus_strong_5.export
			leds_export             => CONNECTED_TO_leds_export,             --             leds.export
			reset_reset_n           => CONNECTED_TO_reset_reset_n,           --            reset.reset_n
			sw_export               => CONNECTED_TO_sw_export,               --               sw.export
			uart_rxd                => CONNECTED_TO_uart_rxd,                --             uart.rxd
			uart_txd                => CONNECTED_TO_uart_txd                 --                 .txd
		);

