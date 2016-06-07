//////////////////////////////////////////////////////////////////////////////-
// filename      : picoctrl_Verilog.v
// author        : Petr Bily, petrbily <at> volny <dot> cz; Adapted to Verilog by Yair Linn
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
//  description and usage:
//    PicoCTRL VHDL design file
//
//  history:
//    8.1.2006  file creation
//////////////////////////////////////////////////////////////////////////////-

module picoctrl (input clk, input res_n, input cond_1,
input cond_2, input cond_3, 
input cond_4, input cond_5, 
input cond_6,
output reg [7:0] reg_0, 
output reg [7:0] reg_1, 
output reg [7:0] reg_2, output reg [7:0] reg_3, output wire [4:0] instruction_ROM_Addr,
input wire[15:0] instruction_ROM_data);

`include "opcodes.v"

  //////////////////////////////////////////////////////////////////////-
  reg [15:0] instruction;

  // the instruction register is written in the FETCH state 
  // in the EXECUTE state the instruction is executed or discarded
  localparam FETCH   = 1'b0;
  localparam EXECUTE = 1'b1;   
  
  reg state;
 
  localparam NOT_EQUAL = 1'b0;
  localparam EQUAL = 1'b1;
  wire evaluation;
  
  reg [4:0] count_sig;   // program counter
  reg [4:0] count_sig_d;   // program counter input 
  reg z_mux;   
  reg [1:0] c1, c2, c3, c4, c5, c6;
// ROM Address assignment

assign instruction_ROM_Addr = count_sig;
////////////////////////////////////////////////////////////////////////////-  
// FETCH/EXECUTE state switching  
   always @ (posedge clk or negedge res_n)
   begin
    if (~res_n) 
      state<=FETCH;
    else	   
	 begin
	   if (state == FETCH)
         state<= EXECUTE;
      else 
        state <= FETCH;
    end  
  end
  
////////////////////////////////////////////////////////////////////////////-
//program counter control 
//next pc value generation
always @*
  begin
    if ((instruction[11:10] == then_jump) && (evaluation == EQUAL)) 
      //jump evaluation - jump is taken
      count_sig_d[4:0] = instruction[4:0]; 
    else
      //fetch the next instruction otherwise
      count_sig_d = count_sig+1;
     
  end

//program counter register
  always @ (posedge clk or negedge res_n)
  begin
     if (~res_n) 
      count_sig<=0;
    else
      if (state == EXECUTE) //clock enable
        count_sig <= count_sig_d;
  end

////////////////////////////////////////////////////////////////////////////-
//program counter control 
  //instruction is loaded only in the FETCH state
  always @ (posedge clk or negedge res_n)
  begin
     if (~res_n) 
      instruction<=16'h0;
    else 
      instruction<=instruction_ROM_data;
  end
////////////////////////////////////////////////////////////////////////////-
//condition processing

//conditions - synchronization      
  always @ (posedge clk or negedge res_n) //two dffs on each of the conditions
  begin           
    if (~res_n) 
	 begin
      c1<=2'b00; 
      c2<=2'b00; 
      c3<=2'b00; 
      c4<=2'b00; 
      c5<=2'b00; 
      c6<=2'b00; 
    end else
	 begin
      c1<={c1[0],cond_1}; 
      c2<={c2[0],cond_2}; 
      c3<={c3[0],cond_3};
      c4<={c4[0],cond_4}; 
      c5<={c5[0],cond_5}; 
      c6<={c6[0],cond_6};
    end  
  end
    
  always @*
  begin      
    case (instruction[14:12])
       3'b000: z_mux <= 0;
       3'b001: z_mux <= c1[1];
       3'b010: z_mux <= c2[1];
       3'b011: z_mux <= c3[1];
       3'b100: z_mux <= c4[1];
       3'b101: z_mux <= c5[1];
       3'b110: z_mux <= c6[1];
       3'b111: z_mux <= 1;
      default: z_mux <= 0;
    endcase
  end 
     
  // condition evaluation
  //if the instruction(15) bit and z_mux signal are equal
  //then the condition is valid, instruction is executed; instruction
  //is discarded otherwise.
  assign evaluation =  (instruction[15] == z_mux) ?  EQUAL : NOT_EQUAL; 
    
////////////////////////////////////////////////////////////////////////////-
//output register control 
//according to the instruction bits, output registers are driven    
  always @ (posedge clk or negedge res_n) //two dffs on each of the conditions
  begin           
    if (~res_n) 
	 begin
      reg_0 <=0;
      reg_1 <=0;
      reg_2 <=0;
      reg_3 <=0;  
   end
   else      
	 begin
      if ((evaluation == EQUAL) & (instruction[11:10] == then_write) & (state==EXECUTE))
		begin
          case (instruction[9:8])
             to_reg_0 : reg_0 <= instruction[7:0];
             to_reg_1 : reg_1 <= instruction[7:0];
             to_reg_2 : reg_2 <= instruction[7:0];
             to_reg_3 : reg_3 <= instruction[7:0];
          endcase
      end else
		begin
		      reg_0 <= reg_0;
				reg_1 <= reg_1;
				reg_2 <= reg_2;
				reg_3 <= reg_3;
      end        
    end
  end 
    
endmodule
