library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use work.boot_block_pack.all;

package boot_sio_mi32el is

constant boot_sio_mi32el : boot_block_type := (
x"00", x"00", x"00", x"00", x"21", x"40", x"00", x"00",
x"21", x"30", x"00", x"00", x"21", x"10", x"00", x"00",
x"6D", x"33", x"0A", x"3C", x"3E", x"20", x"0B", x"3C",
x"00", x"08", x"0C", x"3C", x"01", x"00", x"0D", x"24",
x"03", x"00", x"0E", x"24", x"53", x"00", x"0F", x"24",
x"0D", x"00", x"18", x"24", x"21", x"C8", x"00", x"00",
x"0D", x"0A", x"43", x"25", x"01", x"FB", x"05", x"80",
x"04", x"00", x"A7", x"30", x"FD", x"FF", x"E0", x"14",
x"00", x"00", x"00", x"00", x"00", x"FB", x"03", x"A0",
x"03", x"1A", x"03", x"00", x"25", x"48", x"79", x"00",
x"04", x"00", x"20", x"15", x"00", x"00", x"00", x"00",
x"FF", x"FF", x"19", x"24", x"0D", x"00", x"00", x"08",
x"32", x"6C", x"63", x"25", x"F3", x"FF", x"60", x"14",
x"FF", x"00", x"05", x"24", x"FF", x"FF", x"03", x"24",
x"02", x"00", x"07", x"24", x"1B", x"00", x"61", x"04",
x"00", x"00", x"00", x"00", x"00", x"48", x"02", x"40",
x"24", x"C8", x"4C", x"00", x"02", x"00", x"20", x"13",
x"21", x"20", x"00", x"00", x"FF", x"00", x"04", x"24",
x"C3", x"CC", x"02", x"00", x"FF", x"00", x"49", x"30",
x"FF", x"00", x"39", x"33", x"2A", x"48", x"29", x"03",
x"03", x"00", x"20", x"11", x"00", x"00", x"00", x"00",
x"2D", x"00", x"00", x"08", x"0F", x"00", x"84", x"38",
x"F0", x"00", x"84", x"38", x"10", x"FF", x"04", x"A0",
x"01", x"FB", x"04", x"80", x"01", x"00", x"99", x"30",
x"EC", x"FF", x"20", x"13", x"00", x"00", x"00", x"00",
x"00", x"FB", x"04", x"80", x"18", x"00", x"61", x"04",
x"F6", x"FF", x"89", x"24", x"05", x"00", x"8F", x"14",
x"FF", x"FF", x"19", x"24", x"21", x"10", x"00", x"00",
x"21", x"18", x"00", x"00", x"2D", x"00", x"00", x"08",
x"03", x"22", x"06", x"00", x"05", x"00", x"99", x"14",
x"00", x"00", x"00", x"00", x"8C", x"00", x"00", x"08",
x"00", x"00", x"00", x"00", x"1D", x"00", x"00", x"08",
x"21", x"10", x"00", x"00", x"CA", x"FF", x"98", x"10",
x"21", x"C8", x"00", x"00", x"20", x"00", x"82", x"28",
x"D8", x"FF", x"40", x"14", x"21", x"10", x"00", x"00",
x"01", x"FB", x"09", x"80", x"04", x"00", x"22", x"31",
x"FD", x"FF", x"40", x"14", x"00", x"00", x"00", x"00",
x"1D", x"00", x"00", x"08", x"00", x"FB", x"04", x"A0",
x"04", x"00", x"39", x"2D", x"05", x"00", x"20", x"13",
x"00", x"49", x"02", x"00", x"FF", x"00", x"05", x"24",
x"FF", x"FF", x"03", x"24", x"1F", x"00", x"00", x"08",
x"02", x"00", x"07", x"24", x"61", x"00", x"82", x"28",
x"03", x"00", x"40", x"14", x"D0", x"FF", x"82", x"24",
x"5B", x"00", x"00", x"08", x"E0", x"FF", x"84", x"24",
x"41", x"00", x"99", x"28", x"03", x"00", x"20", x"17",
x"25", x"10", x"49", x"00", x"C9", x"FF", x"84", x"24",
x"25", x"10", x"89", x"00", x"01", x"00", x"63", x"24",
x"15", x"00", x"6D", x"14", x"F9", x"FF", x"59", x"24",
x"03", x"00", x"24", x"2F", x"0D", x"00", x"80", x"10",
x"04", x"00", x"49", x"28", x"00", x"F0", x"04", x"3C",
x"00", x"10", x"05", x"3C", x"24", x"E8", x"04", x"01",
x"00", x"80", x"02", x"34", x"00", x"00", x"40", x"BC",
x"FE", x"FF", x"40", x"14", x"FC", x"FF", x"42", x"24",
x"21", x"F8", x"00", x"00", x"08", x"00", x"00", x"01",
x"21", x"E8", x"A5", x"03", x"1D", x"00", x"00", x"08",
x"21", x"10", x"00", x"00", x"08", x"00", x"20", x"11",
x"00", x"00", x"00", x"00", x"21", x"28", x"42", x"00",
x"78", x"00", x"00", x"08", x"05", x"00", x"A5", x"24",
x"05", x"00", x"6E", x"14", x"06", x"00", x"A9", x"28",
x"21", x"10", x"42", x"00", x"21", x"38", x"E2", x"00",
x"1D", x"00", x"00", x"08", x"21", x"10", x"00", x"00",
x"A2", x"FF", x"20", x"15", x"00", x"00", x"00", x"00",
x"06", x"00", x"65", x"14", x"2A", x"C8", x"A3", x"00",
x"02", x"00", x"00", x"15", x"21", x"30", x"40", x"00",
x"21", x"40", x"40", x"00", x"1D", x"00", x"00", x"08",
x"21", x"28", x"60", x"00", x"99", x"FF", x"20", x"13",
x"01", x"00", x"64", x"30", x"97", x"FF", x"80", x"10",
x"2A", x"48", x"67", x"00", x"95", x"FF", x"20", x"11",
x"00", x"00", x"00", x"00", x"00", x"00", x"C2", x"A0",
x"1D", x"00", x"00", x"08", x"01", x"00", x"C6", x"24",
x"21", x"30", x"00", x"00", x"21", x"18", x"00", x"00",
x"21", x"20", x"00", x"00", x"90", x"00", x"07", x"24",
x"A0", x"00", x"08", x"24", x"B1", x"00", x"09", x"24",
x"91", x"00", x"0A", x"24", x"80", x"00", x"0B", x"24",
x"81", x"00", x"0C", x"24", x"00", x"48", x"02", x"40",
x"02", x"2E", x"02", x"00", x"10", x"FF", x"05", x"A0",
x"01", x"FB", x"0D", x"80", x"01", x"00", x"AE", x"31",
x"FA", x"FF", x"C0", x"11", x"00", x"00", x"00", x"00",
x"00", x"FB", x"0F", x"80", x"FF", x"00", x"F8", x"31",
x"11", x"00", x"07", x"13", x"91", x"00", x"19", x"2F",
x"07", x"00", x"20", x"13", x"00", x"00", x"00", x"00",
x"0F", x"00", x"0B", x"13", x"04", x"00", x"0F", x"24",
x"3D", x"00", x"0C", x"17", x"21", x"28", x"80", x"00",
x"C6", x"00", x"00", x"08", x"04", x"00", x"02", x"24",
x"1F", x"00", x"08", x"13", x"21", x"10", x"00", x"00",
x"2D", x"00", x"09", x"13", x"00", x"00", x"00", x"00",
x"35", x"00", x"0A", x"17", x"00", x"00", x"00", x"00",
x"95", x"00", x"00", x"08", x"21", x"20", x"60", x"00",
x"95", x"00", x"00", x"08", x"21", x"30", x"60", x"00",
x"00", x"1A", x"03", x"00", x"01", x"FB", x"18", x"80",
x"01", x"00", x"19", x"33", x"FD", x"FF", x"20", x"13",
x"00", x"00", x"00", x"00", x"00", x"FB", x"0D", x"80",
x"FF", x"00", x"AE", x"31", x"FF", x"FF", x"EF", x"25",
x"F7", x"FF", x"E0", x"15", x"21", x"18", x"C3", x"01",
x"95", x"00", x"00", x"08", x"00", x"00", x"00", x"00",
x"01", x"FB", x"0E", x"80", x"04", x"00", x"CF", x"31",
x"FD", x"FF", x"E0", x"15", x"00", x"00", x"00", x"00",
x"00", x"FB", x"0D", x"A0", x"FF", x"FF", x"42", x"24",
x"D0", x"FF", x"40", x"10", x"00", x"2A", x"05", x"00",
x"BE", x"00", x"00", x"08", x"03", x"6E", x"05", x"00",
x"21", x"20", x"00", x"00", x"CB", x"FF", x"46", x"10",
x"C2", x"2F", x"04", x"00", x"21", x"20", x"84", x"00",
x"25", x"C0", x"85", x"00", x"01", x"FB", x"19", x"80",
x"01", x"00", x"2D", x"33", x"FD", x"FF", x"A0", x"11",
x"00", x"00", x"00", x"00", x"00", x"FB", x"0F", x"80",
x"21", x"70", x"43", x"00", x"FF", x"00", x"E5", x"31",
x"00", x"00", x"CF", x"A1", x"21", x"20", x"B8", x"00",
x"C9", x"00", x"00", x"08", x"01", x"00", x"42", x"24",
x"00", x"F0", x"04", x"3C", x"00", x"10", x"05", x"3C",
x"24", x"E8", x"64", x"00", x"00", x"80", x"02", x"34",
x"00", x"00", x"40", x"BC", x"FE", x"FF", x"40", x"14",
x"FC", x"FF", x"42", x"24", x"21", x"F8", x"00", x"00",
x"08", x"00", x"60", x"00", x"21", x"E8", x"A5", x"03",
x"08", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"95", x"00", x"00", x"08", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
x"00", x"00", x"00", x"00", x"00", x"00", x"00", x"00",
	others => (others => '0')
    );

end boot_sio_mi32el;
