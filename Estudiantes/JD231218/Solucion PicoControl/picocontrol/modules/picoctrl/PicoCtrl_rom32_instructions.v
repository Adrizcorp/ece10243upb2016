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
         5'h0: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b000_0001};
         5'h1: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h01};
         5'h2: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b000_0010};
         5'h3: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h03         };
         5'h4: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b000_0100};
         5'h5: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h05         };
         5'h6: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b000_1000};
         5'h7: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h07         };
         5'h8: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0001_0000};
         5'h9: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h09         };
         5'ha: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0010_0000};
         5'hb: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h0B			  };
         5'hc: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0100_0000};
         5'hd: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h0D			  };
         5'he: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b1000_0000};
         5'hf: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h0F			  };
			5'h10: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0100_0000};
         5'h11: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h11			  };
         5'h12: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0010_0000};
         5'h13: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h13			  };
         5'h14: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b0001_0000};
         5'h15: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h15			  };
         5'h16: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b000_1000};
         5'h17: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h17			  };
         5'h18: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b000_0100};
         5'h19: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h19			  };
         5'h1a: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b000_0010};
         5'h1b: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h1B			  };
         5'h1c: data = {if_c0_eq_0 , then_write , to_reg_0 , 8'b000_0001};
         5'h1d: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h1D			  };
         5'h1e: data = {if_c0_eq_0 , then_jump  , 2'b00    , 8'h00			  };
         5'h1f: data = nop;
      endcase
	end
endmodule
