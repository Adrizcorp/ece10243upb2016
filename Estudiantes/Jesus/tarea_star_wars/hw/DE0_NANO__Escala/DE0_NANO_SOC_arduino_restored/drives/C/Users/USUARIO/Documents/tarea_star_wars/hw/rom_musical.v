module rom_musical(
		input [7:0]sel,
		output [31:0]out
	);

reg [31:0]temp=32'd0;
assign out[31:0]=temp[31:0];
always@(*)
begin
	case(sel[7:0])
		8'd0: temp[31:0]=32'd95553;//DO
		8'd1: temp[31:0]=32'd85131;//RE
		8'd2: temp[31:0]=32'd75841;//MI
		8'd3: temp[31:0]=32'd71585;//FA
		8'd4: temp[31:0]=32'd63774;//SOL
		8'd5: temp[31:0]=32'd56817;//LA
		8'd6: temp[31:0]=32'd50618;//SI 
		8'd7: temp[31:0]=32'd60239;//SOL #
		8'd8: temp[31:0]=32'd54944;//LA #
		8'd9: temp[31:0]=32'd47800;//DOh
		8'd10: temp[31:0]=32'd45125;//DO#h
		8'd11: temp[31:0]=32'd40191;//RE#h
		8'd12: temp[31:0]=32'd37935;//MIh
		8'd13: temp[31:0]=32'd35815;//FAh
		8'd14: temp[31:0]=32'd37935;//REh
		8'd15: temp[31:0]=32'd31886;//SOLh
		8'd16: temp[31:0]=32'd30119;//SOL#h
		8'd17: temp[31:0]=32'd28408;//LAh
		8'd18: temp[31:0]=32'd33782;//FA#h
		default: temp[31:0]=32'd0;
	endcase
end
	
	
endmodule
