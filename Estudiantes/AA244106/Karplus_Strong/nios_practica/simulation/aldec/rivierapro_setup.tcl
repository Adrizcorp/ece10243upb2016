
# (C) 2001-2016 Altera Corporation. All rights reserved.
# Your use of Altera Corporation's design tools, logic functions and 
# other software and tools, and its AMPP partner logic functions, and 
# any output files any of the foregoing (including device programming 
# or simulation files), and any associated documentation or information 
# are expressly subject to the terms and conditions of the Altera 
# Program License Subscription Agreement, Altera MegaCore Function 
# License Agreement, or other applicable license agreement, including, 
# without limitation, that your use is for the sole purpose of 
# programming logic devices manufactured by Altera and sold by Altera 
# or its authorized distributors. Please refer to the applicable 
# agreement for further details.

# ACDS 15.0 145 win32 2016.06.11.11:19:03

# ----------------------------------------
# Auto-generated simulation script

# ----------------------------------------
# Initialize variables
if ![info exists SYSTEM_INSTANCE_NAME] { 
  set SYSTEM_INSTANCE_NAME ""
} elseif { ![ string match "" $SYSTEM_INSTANCE_NAME ] } { 
  set SYSTEM_INSTANCE_NAME "/$SYSTEM_INSTANCE_NAME"
}

if ![info exists TOP_LEVEL_NAME] { 
  set TOP_LEVEL_NAME "nios_practica"
}

if ![info exists QSYS_SIMDIR] { 
  set QSYS_SIMDIR "./../"
}

if ![info exists QUARTUS_INSTALL_DIR] { 
  set QUARTUS_INSTALL_DIR "C:/altera/15.0/quartus/"
}

# ----------------------------------------
# Initialize simulation properties - DO NOT MODIFY!
set ELAB_OPTIONS ""
set SIM_OPTIONS ""
if ![ string match "*-64 vsim*" [ vsim -version ] ] {
} else {
}

set Aldec "Riviera"
if { [ string match "*Active-HDL*" [ vsim -version ] ] } {
  set Aldec "Active"
}

if { [ string match "Active" $Aldec ] } {
  scripterconf -tcl
  createdesign "$TOP_LEVEL_NAME"  "."
  opendesign "$TOP_LEVEL_NAME"
}

# ----------------------------------------
# Copy ROM/RAM files to simulation directory
alias file_copy {
  echo "\[exec\] file_copy"
  file copy -force $QSYS_SIMDIR/submodules/nios_practica_RAM_jesus.hex ./
}

# ----------------------------------------
# Create compilation libraries
proc ensure_lib { lib } { if ![file isdirectory $lib] { vlib $lib } }
ensure_lib      ./libraries     
ensure_lib      ./libraries/work
vmap       work ./libraries/work
ensure_lib                       ./libraries/altera_ver           
vmap       altera_ver            ./libraries/altera_ver           
ensure_lib                       ./libraries/lpm_ver              
vmap       lpm_ver               ./libraries/lpm_ver              
ensure_lib                       ./libraries/sgate_ver            
vmap       sgate_ver             ./libraries/sgate_ver            
ensure_lib                       ./libraries/altera_mf_ver        
vmap       altera_mf_ver         ./libraries/altera_mf_ver        
ensure_lib                       ./libraries/altera_lnsim_ver     
vmap       altera_lnsim_ver      ./libraries/altera_lnsim_ver     
ensure_lib                       ./libraries/cyclonev_ver         
vmap       cyclonev_ver          ./libraries/cyclonev_ver         
ensure_lib                       ./libraries/cyclonev_hssi_ver    
vmap       cyclonev_hssi_ver     ./libraries/cyclonev_hssi_ver    
ensure_lib                       ./libraries/cyclonev_pcie_hip_ver
vmap       cyclonev_pcie_hip_ver ./libraries/cyclonev_pcie_hip_ver
ensure_lib           ./libraries/sys_clk  
vmap       sys_clk   ./libraries/sys_clk  
ensure_lib           ./libraries/sw       
vmap       sw        ./libraries/sw       
ensure_lib           ./libraries/sel_nota 
vmap       sel_nota  ./libraries/sel_nota 
ensure_lib           ./libraries/pll      
vmap       pll       ./libraries/pll      
ensure_lib           ./libraries/noise_en 
vmap       noise_en  ./libraries/noise_en 
ensure_lib           ./libraries/noise    
vmap       noise     ./libraries/noise    
ensure_lib           ./libraries/leds     
vmap       leds      ./libraries/leds     
ensure_lib           ./libraries/jtag_uart
vmap       jtag_uart ./libraries/jtag_uart
ensure_lib           ./libraries/div_freq 
vmap       div_freq  ./libraries/div_freq 
ensure_lib           ./libraries/cpu      
vmap       cpu       ./libraries/cpu      
ensure_lib           ./libraries/RAM_jesus
vmap       RAM_jesus ./libraries/RAM_jesus

# ----------------------------------------
# Compile device library files
alias dev_com {
  echo "\[exec\] dev_com"
  vlog -v2k5 "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_primitives.v"                    -work altera_ver           
  vlog -v2k5 "$QUARTUS_INSTALL_DIR/eda/sim_lib/220model.v"                             -work lpm_ver              
  vlog -v2k5 "$QUARTUS_INSTALL_DIR/eda/sim_lib/sgate.v"                                -work sgate_ver            
  vlog -v2k5 "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_mf.v"                            -work altera_mf_ver        
  vlog       "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_lnsim.sv"                        -work altera_lnsim_ver     
  vlog -v2k5 "$QUARTUS_INSTALL_DIR/eda/sim_lib/aldec/cyclonev_atoms_ncrypt.v"          -work cyclonev_ver         
  vlog -v2k5 "$QUARTUS_INSTALL_DIR/eda/sim_lib/aldec/cyclonev_hmi_atoms_ncrypt.v"      -work cyclonev_ver         
  vlog -v2k5 "$QUARTUS_INSTALL_DIR/eda/sim_lib/cyclonev_atoms.v"                       -work cyclonev_ver         
  vlog -v2k5 "$QUARTUS_INSTALL_DIR/eda/sim_lib/aldec/cyclonev_hssi_atoms_ncrypt.v"     -work cyclonev_hssi_ver    
  vlog -v2k5 "$QUARTUS_INSTALL_DIR/eda/sim_lib/cyclonev_hssi_atoms.v"                  -work cyclonev_hssi_ver    
  vlog -v2k5 "$QUARTUS_INSTALL_DIR/eda/sim_lib/aldec/cyclonev_pcie_hip_atoms_ncrypt.v" -work cyclonev_pcie_hip_ver
  vlog -v2k5 "$QUARTUS_INSTALL_DIR/eda/sim_lib/cyclonev_pcie_hip_atoms.v"              -work cyclonev_pcie_hip_ver
}

# ----------------------------------------
# Compile the design files in correct order
alias com {
  echo "\[exec\] com"
  vlog -v2k5 "$QSYS_SIMDIR/submodules/nios_practica_sys_clk.v"   -work sys_clk  
  vlog -v2k5 "$QSYS_SIMDIR/submodules/nios_practica_sw.v"        -work sw       
  vlog -v2k5 "$QSYS_SIMDIR/submodules/nios_practica_sel_nota.v"  -work sel_nota 
  vlog -v2k5 "$QSYS_SIMDIR/submodules/nios_practica_pll.vo"      -work pll      
  vlog -v2k5 "$QSYS_SIMDIR/submodules/nios_practica_noise_en.v"  -work noise_en 
  vlog -v2k5 "$QSYS_SIMDIR/submodules/nios_practica_noise.v"     -work noise    
  vlog -v2k5 "$QSYS_SIMDIR/submodules/nios_practica_leds.v"      -work leds     
  vlog -v2k5 "$QSYS_SIMDIR/submodules/nios_practica_jtag_uart.v" -work jtag_uart
  vlog -v2k5 "$QSYS_SIMDIR/submodules/nios_practica_div_freq.v"  -work div_freq 
  vlog -v2k5 "$QSYS_SIMDIR/submodules/nios_practica_cpu.v"       -work cpu      
  vlog -v2k5 "$QSYS_SIMDIR/submodules/nios_practica_RAM_jesus.v" -work RAM_jesus
  vlog -v2k5 "$QSYS_SIMDIR/nios_practica.v"                                     
}

# ----------------------------------------
# Elaborate top level design
alias elab {
  echo "\[exec\] elab"
  eval vsim +access +r -t ps $ELAB_OPTIONS -L work -L sys_clk -L sw -L sel_nota -L pll -L noise_en -L noise -L leds -L jtag_uart -L div_freq -L cpu -L RAM_jesus -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cyclonev_ver -L cyclonev_hssi_ver -L cyclonev_pcie_hip_ver $TOP_LEVEL_NAME
}

# ----------------------------------------
# Elaborate the top level design with -dbg -O2 option
alias elab_debug {
  echo "\[exec\] elab_debug"
  eval vsim -dbg -O2 +access +r -t ps $ELAB_OPTIONS -L work -L sys_clk -L sw -L sel_nota -L pll -L noise_en -L noise -L leds -L jtag_uart -L div_freq -L cpu -L RAM_jesus -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cyclonev_ver -L cyclonev_hssi_ver -L cyclonev_pcie_hip_ver $TOP_LEVEL_NAME
}

# ----------------------------------------
# Compile all the design files and elaborate the top level design
alias ld "
  dev_com
  com
  elab
"

# ----------------------------------------
# Compile all the design files and elaborate the top level design with -dbg -O2
alias ld_debug "
  dev_com
  com
  elab_debug
"

# ----------------------------------------
# Print out user commmand line aliases
alias h {
  echo "List Of Command Line Aliases"
  echo
  echo "file_copy                     -- Copy ROM/RAM files to simulation directory"
  echo
  echo "dev_com                       -- Compile device library files"
  echo
  echo "com                           -- Compile the design files in correct order"
  echo
  echo "elab                          -- Elaborate top level design"
  echo
  echo "elab_debug                    -- Elaborate the top level design with -dbg -O2 option"
  echo
  echo "ld                            -- Compile all the design files and elaborate the top level design"
  echo
  echo "ld_debug                      -- Compile all the design files and elaborate the top level design with -dbg -O2"
  echo
  echo 
  echo
  echo "List Of Variables"
  echo
  echo "TOP_LEVEL_NAME                -- Top level module name."
  echo
  echo "SYSTEM_INSTANCE_NAME          -- Instantiated system module name inside top level module."
  echo
  echo "QSYS_SIMDIR                   -- Qsys base simulation directory."
  echo
  echo "QUARTUS_INSTALL_DIR           -- Quartus installation directory."
}
file_copy
h
