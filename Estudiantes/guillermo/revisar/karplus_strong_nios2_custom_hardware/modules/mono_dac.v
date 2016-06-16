//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2006 Xilinx, Inc.
// This design is confidential and proprietary of Xilinx, All Rights Reserved.
//////////////////////////////////////////////////////////////////////////////
//   ____  ____
//  /   /\/   /
// /___/  \  /   Vendor:        Xilinx
// \   \   \/    Version:       1.0.0
//  \   \        Filename:      mono_dac.v
//  /   /        Date Created:  December 25, 2006
// /___/   /\    Last Modified: December 25, 2006
// \   \  /  \
//  \___\/\___\
//
// Devices:   Spartan-3 Generation FPGA
// Purpose:   Mono 8-bit DAC with 3-bit volume, based on XAPP154
// Contact:   crabill@xilinx.com
// Reference: None
//
// Revision History:
//   Rev 1.0.0 - (crabill) First created December 25, 2006.
//
//////////////////////////////////////////////////////////////////////////////
//
// LIMITED WARRANTY AND DISCLAIMER. These designs are provided to you "as is".
// Xilinx and its licensors make and you receive no warranties or conditions,
// express, implied, statutory or otherwise, and Xilinx specifically disclaims
// any implied warranties of merchantability, non-infringement, or fitness for
// a particular purpose. Xilinx does not warrant that the functions contained
// in these designs will meet your requirements, or that the operation of
// these designs will be uninterrupted or error free, or that defects in the
// designs will be corrected. Furthermore, Xilinx does not warrant or make any
// representations regarding use or the results of the use of the designs in
// terms of correctness, accuracy, reliability, or otherwise.
//
// LIMITATION OF LIABILITY. In no event will Xilinx or its licensors be liable
// for any loss of data, lost profits, cost or procurement of substitute goods
// or services, or for any special, incidental, consequential, or indirect
// damages arising from the use or operation of the designs or accompanying
// documentation, however caused and on any theory of liability. This
// limitation will apply even if Xilinx has been advised of the possibility
// of such damage. This limitation shall apply not-withstanding the failure
// of the essential purpose of any limited remedies herein.
//
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2006 Xilinx, Inc.
// This design is confidential and proprietary of Xilinx, All Rights Reserved.
//////////////////////////////////////////////////////////////////////////////

`timescale 1 ns / 1 ps

`define ALTERA

module mono_dac
  (
  input  wire  [7:0] signed_data,
  input  wire  [2:0] volume,
  output reg         audio,
  input  wire        clk
  );

  //******************************************************************//
  // Implement actual DAC, taken from XAPP154.  The DACin input is an //
  // unsigned value (excess 128).                                     //
  //******************************************************************//

  wire         [7:0] DACin;

  reg          [9:0] DeltaB;
  reg          [9:0] DeltaAdder;
  reg          [9:0] SigmaAdder;
  reg          [9:0] SigmaLatch;

  always @* DeltaB = {SigmaLatch[9], SigmaLatch[9], 8'b00000000};
  always @* DeltaAdder = DACin + DeltaB;
  always @* SigmaAdder = DeltaAdder + SigmaLatch;
  always @* audio = SigmaLatch[9];

  initial SigmaLatch <= 10'b0100000000;
  always @(posedge clk)
  begin : dac_feedback
    SigmaLatch <= SigmaAdder;
  end

  //******************************************************************//
  // This is not thrifty, but I have plenty of idle multipliers.      //
  //******************************************************************//

  reg         [17:0] se_scalefactor;
  wire        [17:0] se_signed_data;
  wire        [35:0] se_scaled_data;

  always @*
  begin
    case (volume)
      4'h7:    se_scalefactor = 18'b0000000000_1000_0000; // fullscale
      4'h6:    se_scalefactor = 18'b0000000000_0110_0000;
      4'h5:    se_scalefactor = 18'b0000000000_0100_0000;
      4'h4:    se_scalefactor = 18'b0000000000_0011_0000;
      4'h3:    se_scalefactor = 18'b0000000000_0010_0000;
      4'h2:    se_scalefactor = 18'b0000000000_0001_1000;
      4'h1:    se_scalefactor = 18'b0000000000_0001_0000;
      default: se_scalefactor = 18'b0000000000_0000_0000; // mute
    endcase
  end

  assign se_signed_data = {{10{signed_data[7]}},signed_data};

  `ifdef ALTERA
		assign se_scaled_data=se_signed_data*se_scalefactor;
  `else
		MULT18X18 ssd_m (.A(se_signed_data),.B(se_scalefactor),.P(se_scaled_data));
  `endif
  

  assign DACin = (se_scaled_data[14:7] + 128);

  //******************************************************************//
  //                                                                  //
  //******************************************************************//

endmodule
