// Listing 12.5
module PicoCtrl_rom32_instructions
   (
    input wire [4:0] addr,
    output reg [15:0] data
   );
   `include "opcodes.v"
   // body
   always @*
	begin
      case (addr)
         5'h0: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0000_0001};
         5'h1: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h01};
         5'h2: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0000_0010};
         5'h3: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h03         };
         5'h4: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0000_0100};
         5'h5: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h05         };
         5'h6: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0000_1000};
         5'h7: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h07         };
         5'h8: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0001_0000};
         5'h9: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h09         };
         5'ha: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0010_0000};
         5'hb: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h0b			  };
         5'hc: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0100_0000};
         5'hd: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h0d			  };
         5'he: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b1000_0000};
         5'hf: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h0f			  };
			5'h10: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0100_0000};
         5'h11: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h011			  };
         5'h12: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0010_0000};
         5'h13: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h013			  };
         5'h14: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0001_0000};
         5'h15: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h015			  };
         5'h16: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0000_1000};
         5'h17: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h017			  };
         5'h18: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0000_0100};
         5'h19: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h019			  };
         5'h1a: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0000_0010};
         5'h1b: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h01b			  };
         5'h1c: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0000_0001};
         5'h1d: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h01d};
         5'h1e: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h00};
         5'h1f: data = nop;
      endcase
	end
endmodule
