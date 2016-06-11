module rom_musical(
	input wire [3:0]address,
	output reg [31:0]data
);

always @*
	begin
      case (address[3:0]) 
			/*4'h0 : data = 32'd47800; //do
			4'h1 : data = 32'd42588; //re
			4'h2 : data = 32'd37935; //mi
			4'h3 : data = 32'd35815; //fa
			4'h4 : data = 32'd31886; //sol
			4'h5 : data = 32'd24408; //la
			4'h6 : data = 32'd25302; //si*/
			4'h0: data = 32'd95565;
         4'h1: data = 32'd85129;
         4'h2: data = 32'd75842;
         4'h3: data = 32'd71585;
         4'h4: data = 32'd63775;
         4'h5: data = 32'd56817;
         4'h6: data = 32'd50619;
			4'h7 : data = 32'd45125; //do#
			4'h8 : data = 32'd40191; //re#
			4'h9 : data = 32'd33782; //fa#
			4'ha : data = 32'd30083; //sol#
			4'hb : data = 32'd26823; //la#
			4'hc : data = 32'd0;
			4'hd : data = 32'd0;
			4'he : data = 32'd0;
			4'hf : data = 32'd0;
		endcase
	end
	
endmodule
