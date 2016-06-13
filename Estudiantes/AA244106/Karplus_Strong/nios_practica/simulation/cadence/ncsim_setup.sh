
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
# ncsim - auto-generated simulation script

# ----------------------------------------
# initialize variables
TOP_LEVEL_NAME="nios_practica"
QSYS_SIMDIR="./../"
QUARTUS_INSTALL_DIR="C:/altera/15.0/quartus/"
SKIP_FILE_COPY=0
SKIP_DEV_COM=0
SKIP_COM=0
SKIP_ELAB=0
SKIP_SIM=0
USER_DEFINED_ELAB_OPTIONS=""
USER_DEFINED_SIM_OPTIONS="-input \"@run 100; exit\""

# ----------------------------------------
# overwrite variables - DO NOT MODIFY!
# This block evaluates each command line argument, typically used for 
# overwriting variables. An example usage:
#   sh <simulator>_setup.sh SKIP_ELAB=1 SKIP_SIM=1
for expression in "$@"; do
  eval $expression
  if [ $? -ne 0 ]; then
    echo "Error: This command line argument, \"$expression\", is/has an invalid expression." >&2
    exit $?
  fi
done

# ----------------------------------------
# initialize simulation properties - DO NOT MODIFY!
ELAB_OPTIONS=""
SIM_OPTIONS=""
if [[ `ncsim -version` != *"ncsim(64)"* ]]; then
  :
else
  :
fi

# ----------------------------------------
# create compilation libraries
mkdir -p ./libraries/work/
mkdir -p ./libraries/sys_clk/
mkdir -p ./libraries/sw/
mkdir -p ./libraries/sel_nota/
mkdir -p ./libraries/pll/
mkdir -p ./libraries/noise_en/
mkdir -p ./libraries/noise/
mkdir -p ./libraries/leds/
mkdir -p ./libraries/jtag_uart/
mkdir -p ./libraries/div_freq/
mkdir -p ./libraries/cpu/
mkdir -p ./libraries/RAM_jesus/
mkdir -p ./libraries/altera_ver/
mkdir -p ./libraries/lpm_ver/
mkdir -p ./libraries/sgate_ver/
mkdir -p ./libraries/altera_mf_ver/
mkdir -p ./libraries/altera_lnsim_ver/
mkdir -p ./libraries/cyclonev_ver/
mkdir -p ./libraries/cyclonev_hssi_ver/
mkdir -p ./libraries/cyclonev_pcie_hip_ver/

# ----------------------------------------
# copy RAM/ROM files to simulation directory
if [ $SKIP_FILE_COPY -eq 0 ]; then
  cp -f $QSYS_SIMDIR/submodules/nios_practica_RAM_jesus.hex ./
fi

# ----------------------------------------
# compile device library files
if [ $SKIP_DEV_COM -eq 0 ]; then
  ncvlog     "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_primitives.v"                      -work altera_ver           
  ncvlog     "$QUARTUS_INSTALL_DIR/eda/sim_lib/220model.v"                               -work lpm_ver              
  ncvlog     "$QUARTUS_INSTALL_DIR/eda/sim_lib/sgate.v"                                  -work sgate_ver            
  ncvlog     "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_mf.v"                              -work altera_mf_ver        
  ncvlog -sv "$QUARTUS_INSTALL_DIR/eda/sim_lib/altera_lnsim.sv"                          -work altera_lnsim_ver     
  ncvlog     "$QUARTUS_INSTALL_DIR/eda/sim_lib/cadence/cyclonev_atoms_ncrypt.v"          -work cyclonev_ver         
  ncvlog     "$QUARTUS_INSTALL_DIR/eda/sim_lib/cadence/cyclonev_hmi_atoms_ncrypt.v"      -work cyclonev_ver         
  ncvlog     "$QUARTUS_INSTALL_DIR/eda/sim_lib/cyclonev_atoms.v"                         -work cyclonev_ver         
  ncvlog     "$QUARTUS_INSTALL_DIR/eda/sim_lib/cadence/cyclonev_hssi_atoms_ncrypt.v"     -work cyclonev_hssi_ver    
  ncvlog     "$QUARTUS_INSTALL_DIR/eda/sim_lib/cyclonev_hssi_atoms.v"                    -work cyclonev_hssi_ver    
  ncvlog     "$QUARTUS_INSTALL_DIR/eda/sim_lib/cadence/cyclonev_pcie_hip_atoms_ncrypt.v" -work cyclonev_pcie_hip_ver
  ncvlog     "$QUARTUS_INSTALL_DIR/eda/sim_lib/cyclonev_pcie_hip_atoms.v"                -work cyclonev_pcie_hip_ver
fi

# ----------------------------------------
# compile design files in correct order
if [ $SKIP_COM -eq 0 ]; then
  ncvlog "$QSYS_SIMDIR/submodules/nios_practica_sys_clk.v"   -work sys_clk   -cdslib ./cds_libs/sys_clk.cds.lib  
  ncvlog "$QSYS_SIMDIR/submodules/nios_practica_sw.v"        -work sw        -cdslib ./cds_libs/sw.cds.lib       
  ncvlog "$QSYS_SIMDIR/submodules/nios_practica_sel_nota.v"  -work sel_nota  -cdslib ./cds_libs/sel_nota.cds.lib 
  ncvlog "$QSYS_SIMDIR/submodules/nios_practica_pll.vo"      -work pll       -cdslib ./cds_libs/pll.cds.lib      
  ncvlog "$QSYS_SIMDIR/submodules/nios_practica_noise_en.v"  -work noise_en  -cdslib ./cds_libs/noise_en.cds.lib 
  ncvlog "$QSYS_SIMDIR/submodules/nios_practica_noise.v"     -work noise     -cdslib ./cds_libs/noise.cds.lib    
  ncvlog "$QSYS_SIMDIR/submodules/nios_practica_leds.v"      -work leds      -cdslib ./cds_libs/leds.cds.lib     
  ncvlog "$QSYS_SIMDIR/submodules/nios_practica_jtag_uart.v" -work jtag_uart -cdslib ./cds_libs/jtag_uart.cds.lib
  ncvlog "$QSYS_SIMDIR/submodules/nios_practica_div_freq.v"  -work div_freq  -cdslib ./cds_libs/div_freq.cds.lib 
  ncvlog "$QSYS_SIMDIR/submodules/nios_practica_cpu.v"       -work cpu       -cdslib ./cds_libs/cpu.cds.lib      
  ncvlog "$QSYS_SIMDIR/submodules/nios_practica_RAM_jesus.v" -work RAM_jesus -cdslib ./cds_libs/RAM_jesus.cds.lib
  ncvlog "$QSYS_SIMDIR/nios_practica.v"                                                                          
fi

# ----------------------------------------
# elaborate top level design
if [ $SKIP_ELAB -eq 0 ]; then
  ncelab -access +w+r+c -namemap_mixgen $ELAB_OPTIONS $USER_DEFINED_ELAB_OPTIONS $TOP_LEVEL_NAME
fi

# ----------------------------------------
# simulate
if [ $SKIP_SIM -eq 0 ]; then
  eval ncsim -licqueue $SIM_OPTIONS $USER_DEFINED_SIM_OPTIONS $TOP_LEVEL_NAME
fi
