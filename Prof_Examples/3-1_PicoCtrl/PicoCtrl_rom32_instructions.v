// Listing 12.5
module PicoCtrl_rom32_instructions
   (
    input wire [4:0] addr,
    output reg [15:0] data
   );
//////////////////////////////////////////////////////////////////////////////-
// file name     : opcodes.vhd
// author        : Jakub Stastny, stastj1 <at> seznam <dot> cz; Adapted to Verilog by Yair Linn
// project       : PicoCTRL
//
//       (c) 2006 Ceske vysoke uceni technicke,
//                fakulta elektrotechnicka
//                katedra teorie obvodu
//
//  Tento kod, vesktera dokumentace i ostatni dostupne prostredky,
//  programy, skripty jsou majetkem Katedry teorie obvodu Ceskeho
//  vysokeho uceni technickeho. Komercni uziti kymkoliv bez predchoziho
//  pisemneho souhlasu je prisne zakazano a bude trestano podle platnych
//  zakonu.
//
//  This code and all related documents and scripts are the property of
//  the Department of Circuit Theory, Czech Technical University.
//  Its commercial usage by anyone without prior written consent of the
//  Department is strictly  prohibited and will be prosecuted
//  according to the law.
//
//  usage:
//    operating codes - localparams - for the picoctrl microinstructions
//
//  history:
//    8.1.2006  file created
//////////////////////////////////////////////////////////////////////////////-



// control
// condiciones  C son las entradas, el microprocesador tiene 7 controles
// los cuales son relojes de entradas, los eq son valores de comparacion, como a continuacion
localparam if_c0_eq_0 = 4'b0000;   //  cuando el reloj 0 este en bajo haga
localparam if_c0_eq_1 = 4'b1000;  //  cuando el reloj 0 este en alto haga
localparam if_c1_eq_0 = 4'b0001;  //  cuando el reloj 1 este en bajo haga
localparam if_c1_eq_1 = 4'b1001;  //  cuando el reloj 1 este en alto haga
localparam if_c2_eq_0 = 4'b0010;
localparam if_c2_eq_1 = 4'b1010;  
localparam if_c3_eq_0 = 4'b0011;
localparam if_c3_eq_1 = 4'b1011; 
localparam if_c4_eq_0 = 4'b0100;
localparam if_c4_eq_1 = 4'b1100; 
localparam if_c5_eq_0 = 4'b0101;  //  cuando el reloj 5 este en bajo haga
localparam if_c5_eq_1 = 4'b1101;  //  cuando el reloj 5 este en alto haga
localparam if_c6_eq_0 = 4'b0110;
localparam if_c6_eq_1 = 4'b1110; 
localparam if_c7_eq_0 = 4'b0111;
localparam if_c7_eq_1 = 4'b1111;    
  
 
localparam then_write = 2'b01;
localparam then_jump  = 2'b00;
  
localparam to_reg_0 = 2'b00;
localparam to_reg_1 = 2'b01;
localparam to_reg_2 = 2'b10;
localparam to_reg_3 = 2'b11;      

localparam nop = 16'b1000000000000000;
  
   // body
   always @*
	begin
      case (addr) 
		// control
// condiciones  C son las entradas, el microprocesador tiene 7 controles
// los cuales son relojes de entradas, los eq son valores de comparacion, como a continuacion
//localparam if_c0_eq_0 = 4'b0000;   //  cuando el reloj 0 este en bajo haga
//localparam if_c0_eq_1 = 4'b1000;  //  cuando el reloj 0 este en alto haga
//localparam if_c1_eq_0 = 4'b0001;  //  cuando el reloj 1 este en bajo haga
//localparam if_c1_eq_1 = 4'b1001;  //  cuando el reloj 1 este en alto haga
//localparam if_c2_eq_0 = 4'b0010;
//localparam if_c2_eq_1 = 4'b1010;  
//localparam if_c3_eq_0 = 4'b0011;
//localparam if_c3_eq_1 = 4'b1011; 
//localparam if_c4_eq_0 = 4'b0100;
//localparam if_c4_eq_1 = 4'b1100; 
//localparam if_c5_eq_0 = 4'b0101;  //  cuando el reloj 5 este en bajo haga
//localparam if_c5_eq_1 = 4'b1101;  //  cuando el reloj 5 este en alto haga
//localparam if_c6_eq_0 = 4'b0110;
//localparam if_c6_eq_1 = 4'b1110; 
//localparam if_c7_eq_0 = 4'b0111;
//localparam if_c7_eq_1 = 4'b1111;    
         5'h0: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0111_0001};
         5'h1: data = {if_c5_eq_1 , then_jump  , 2'b00    , 8'h01};
         5'h2: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b1011_0010};
         5'h3: data = {if_c5_eq_0 , then_jump  , 2'b00    , 8'h03         };
         5'h4: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b1101_0100};
         5'h5: data = {if_c5_eq_1 , then_jump  , 2'b00    , 8'h05         };
         5'h6: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b1110_1000};
         5'h7: data = {if_c5_eq_0 , then_jump  , 2'b00    , 8'h07         };
         5'h8: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b1101_0100};
         5'h9: data = {if_c5_eq_1 , then_jump  , 2'b00    , 8'h09         };
         5'ha: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b1011_0010};
         5'hb: data = {if_c5_eq_0 , then_jump  , 2'b00    , 8'h0B			  };
         5'hc: data = {if_c0_eq_0 , then_jump  , 2'b00    , 8'h00			  };
         5'hd: data = nop;
         5'he: data = nop;
         5'hf: data = nop;
			5'h10: data = nop;
         5'h11: data = nop;
         5'h12: data = nop;
         5'h13: data = nop;
         5'h14: data = nop;
         5'h15: data = nop;
         5'h16: data = nop;
         5'h17: data = nop;
         5'h18: data = nop;
         5'h19: data = nop;
         5'h1a: data = nop;
         5'h1b: data = nop;
         5'h1c: data = nop;
         5'h1d: data = nop;
         5'h1e: data = nop;
         5'h1f: data = nop;
      endcase
	end
endmodule
