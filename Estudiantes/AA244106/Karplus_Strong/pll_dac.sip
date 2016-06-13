set_global_assignment -entity "pll_dac" -library "lib_pll_dac" -name IP_TOOL_NAME "altera_pll"
set_global_assignment -entity "pll_dac" -library "lib_pll_dac" -name IP_TOOL_VERSION "15.0"
set_global_assignment -entity "pll_dac" -library "lib_pll_dac" -name IP_TOOL_ENV "mwpim"
set_global_assignment -library "lib_pll_dac" -name SPD_FILE [file join $::quartus(sip_path) "pll_dac.spd"]

set_global_assignment -library "lib_pll_dac" -name MISC_FILE [file join $::quartus(sip_path) "pll_dac_sim/pll_dac.vo"]
