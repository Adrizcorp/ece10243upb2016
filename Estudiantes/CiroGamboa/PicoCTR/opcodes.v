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

localparam if_c0_eq_0 = 4'b0000;
localparam if_c0_eq_1 = 4'b1000;  
localparam if_c1_eq_0 = 4'b0001;
localparam if_c1_eq_1 = 4'b1001;  
localparam if_c2_eq_0 = 4'b0010;
localparam if_c2_eq_1 = 4'b1010;  
localparam if_c3_eq_0 = 4'b0011;
localparam if_c3_eq_1 = 4'b1011; 
localparam if_c4_eq_0 = 4'b0100;
localparam if_c4_eq_1 = 4'b1100; 
localparam if_c5_eq_0 = 4'b0101;
localparam if_c5_eq_1 = 4'b1101; 
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
  