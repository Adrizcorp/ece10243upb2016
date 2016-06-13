set_global_assignment -entity "nios_practica" -library "lib_nios_practica" -name IP_TOOL_NAME "Qsys"
set_global_assignment -entity "nios_practica" -library "lib_nios_practica" -name IP_TOOL_VERSION "15.0"
set_global_assignment -entity "nios_practica" -library "lib_nios_practica" -name IP_TOOL_ENV "Qsys"
set_global_assignment -library "lib_nios_practica" -name SPD_FILE [file join $::quartus(sip_path) "../nios_practica.spd"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "../../nios_practica.qsys"]

set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "nios_practica.v"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "submodules/nios_practica_sys_clk.v"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "submodules/nios_practica_sw.v"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "submodules/nios_practica_sel_nota.v"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "submodules/nios_practica_pll.vo"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "submodules/nios_practica_noise_en.v"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "submodules/nios_practica_noise.v"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "submodules/nios_practica_leds.v"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "submodules/nios_practica_jtag_uart.v"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "submodules/nios_practica_div_freq.v"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "submodules/nios_practica_cpu.v"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "submodules/nios_practica_RAM_jesus.hex"]
set_global_assignment -library "lib_nios_practica" -name MISC_FILE [file join $::quartus(sip_path) "submodules/nios_practica_RAM_jesus.v"]
