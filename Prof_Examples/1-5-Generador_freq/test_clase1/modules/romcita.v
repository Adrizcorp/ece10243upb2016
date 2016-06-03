module romcita(
		input [3:0]sel,
		output reg [31:0]data
);


always@(*)
begin
	case(sel[3:0])
	4'b0000: data[31:0]=32'd24999999;
	4'b0001: data[31:0]=32'd2499999;
	4'b0010:	data[31:0]=32'd24999;
	4'b0011: data[31:0]=32'd2499;
	default: data[31:0]=32'd4549798;
//	4'd4: data[31:0]=32'd249;
//	4'd5: data[31:0]=32'd24;
//	4'd6: data[31:0]=32'd24;
//	4'd7: data[31:0]=32'd78435;
//	4'd8: data[31:0]=32'd78135;
//	4'd9: data[31:0]=32'd78175;
//	4'd10: data[31:0]=32'd78135;
//	4'd11: data[31:0]=32'd70135;
//	4'd12: data[31:0]=32'd78135;
//	4'd13: data[31:0]=32'd78635;
//	4'd14: data[31:0]=32'd78195;
//	4'd15: data[31:0]=32'd7135;
	endcase
end


endmodule
