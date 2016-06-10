module fsm_secuencia(
					input clk,
					input start,
					input sw_0,
					output finish,
					output idle,
					output [7:0]leds
);
							//finish____ idle______state, one hot 
localparam	IDLE	=		8'b0_________1_________000001;
localparam	STATE1=		8'b0_________0_________000010;
localparam	STATE2=		8'b0_________0_________000100;
localparam	STATE3=		8'b0_________0_________001000;
localparam	STATE4=		8'b0_________0_________010000;
localparam	FINISH=		8'b1_________0_________100000;

reg [7:0]state=IDLE;
reg [3:0]conteo=4'd0;
assign finish=state[7];
assign idle=state[6];

assign leds[7:0]= (state[7:0]== IDLE)? 8'b10101010:
						(state[7:0]== STATE1)? 8'b01010101:
						(state[7:0]== STATE2)? 8'b10000001:
						(state[7:0]== STATE3)? 8'b01000010:
						(state[7:0]== STATE4)? 8'b00100100:
						(state[7:0]== FINISH)? 8'b00011000:
						8'b00000000;
						


always@(posedge clk)
begin
	case(state[7:0])
	IDLE	:begin
				state[7:0]<=STATE1;
				conteo[3:0]<=4'd0;
				if(!start)
					begin
						state[7:0]<=IDLE;
					end
			 end
	STATE1:begin
				state[7:0]<=STATE2;
				conteo[3:0]<=4'd0;
				if(!sw_0)
					begin
						state[7:0]<=STATE1;
					end
			 end
	STATE2:begin
				state[7:0]<=STATE3;
				conteo[3:0]<=4'd0;
			 end
	STATE3:begin
				state[7:0]<=STATE4;
				conteo[3:0]<=4'd0;
			 end
	STATE4:begin
				state[7:0]<=FINISH;
				conteo[3:0]<=4'd0;
			 end
	FINISH:begin
				state[7:0]<=FINISH;
				conteo[3:0]<=conteo[3:0]+1'b1;
				if(conteo[3:0]>=4'd15)
				begin
					state[7:0]<=IDLE;
				end
			 end
	default:begin
				state[7:0]<=IDLE;
				conteo[3:0]<=4'd0;
				end
	endcase
end


endmodule
