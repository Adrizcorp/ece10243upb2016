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
         5'h0: data = {if_c0_eq_0 , then_write , to_reg_1 , 8'd1};
         5'h1: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h01};
         5'h2: data = {if_c0_eq_0 , then_write , to_reg_1 , 8'd2};
         5'h3: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h03         };
         5'h4: data = {if_c0_eq_0 , then_write , to_reg_1 , 8'd4};
         5'h5: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h05         };
         5'h6: data = {if_c0_eq_0 , then_write , to_reg_1 , 8'd8};
         5'h7: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h07         };
         5'h8: data = {if_c0_eq_0 , then_write , to_reg_1 , 8'd16};
         5'h9: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h09         };
         5'ha: data = {if_c0_eq_0 , then_write , to_reg_1 , 8'd32};
         5'hb: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'hb			  };
         5'hc: data = {if_c0_eq_0 , then_write  , to_reg_1, 8'd64			  };
         5'hd: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'hd			  };
         5'he: data = {if_c0_eq_0 , then_write  , to_reg_1, 8'd128		  };
         5'hf: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'hf			  };
			5'h10: data ={if_c0_eq_0 , then_write  , to_reg_1, 8'd64			  };
         5'h11: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h11			  };
         5'h12: data = {if_c0_eq_0 , then_write  , to_reg_1, 8'd32		  };
         5'h13: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h13		  };
         5'h14: data = {if_c0_eq_0 , then_write  , to_reg_1, 8'd16		  };
         5'h15: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h15		  };
         5'h16: data = {if_c0_eq_0 , then_write  , to_reg_1, 8'd8			  };
         5'h17: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h17		  };
         5'h18: data = {if_c0_eq_0 , then_write  , to_reg_1, 8'd4			  };
         5'h19: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h19			  };
         5'h1a: data = {if_c0_eq_0 , then_write  , to_reg_1, 8'd2			  };
         5'h1b: data = {if_c1_eq_0 , then_jump  , 2'b00    , 8'h1b			  };
         5'h1c: data = {if_c0_eq_0 , then_write  , to_reg_1, 8'd1			  };
         5'h1d: data = {if_c1_eq_1 , then_jump  , 2'b00    , 8'h1d			  };
         5'h1e: data = nop;
         5'h1f: data = nop;
      endcase
	end
endmodule
