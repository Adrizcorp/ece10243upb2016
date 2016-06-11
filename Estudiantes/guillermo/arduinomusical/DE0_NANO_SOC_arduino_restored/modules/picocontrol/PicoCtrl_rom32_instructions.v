// Listing 12.5
module PicoCtrl_rom32_instructions
   (
    input wire [3:0] addr,
    output reg [31:0] data
   );

   // body
   always @*
	begin
      case (addr)
         4'h0: data = 32'd1;
         4'h1: data = 32'd95565;
         4'h2: data = 32'd85129;
         4'h3: data = 32'd75842;
         4'h4: data = 32'd71585;
         4'h5: data = 32'd63775;
         4'h6: data = 32'd56817;
         4'h7: data = 32'd50619;
         4'h8: data = 32'd47777;
         4'h9: data = 32'd42565;
         4'ha: data = 32'd37920;
         4'hb: data = 32'd1;
         4'hc: data = 32'd1;
         4'hd: data = 32'd1;
         4'he: data = 32'd1;
         4'hf: data = 32'd1;
			
      endcase
	end
endmodule
