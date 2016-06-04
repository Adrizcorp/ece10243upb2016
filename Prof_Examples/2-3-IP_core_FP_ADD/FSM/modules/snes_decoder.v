module snes_decoder(
			input clk,
			input data,
			input start,
			output finish,
			output idle,
			output latch,
			output clock,
			output [11:0]buttons
	);
							///finish___idle___clock___latch____state
localparam IDLE	=		10'b0________1______1_______0________000001;		
localparam STATE1	=		10'b0________0______1_______1________000010;
localparam STATE2	=		10'b0________0______1_______0________000100;
localparam STATE3	=		10'b0________0______0_______0________001000;
localparam STATE4	=		10'b0________0______1_______0________010000;	
localparam FINISH	=		10'b1________0______1_______0________100000;
localparam DELAY_12u = 10'd600;
localparam DELAY_6u = 10'd300;

reg [9:0]state=IDLE;
reg [9:0]delay=DELAY_12u;
reg [3:0]conteo=4'd0;
reg [14:0]buttons_temp=15'd0;
reg [14:0]buttons_temp2=15'd0;
assign buttons[11:0]=buttons_temp2[11:0];
assign finish=state[9];
assign idle=state[8];
assign clock=state[7];
assign latch=state[6];

always@(posedge clk)
begin
	case(state[9:0])
	IDLE	:begin
				conteo[3:0]<=4'd1;
				delay[9:0]<=DELAY_12u;
				state[9:0]<=STATE1;
				if(!start)
					begin
						state[9:0]<=IDLE;
					end
			 end
	STATE1:begin
				conteo[3:0]<=4'd1;
				delay[9:0]<=delay[9:0]-1'b1;
				state[9:0]<=STATE1;
				if(delay[9:0]==0)
					begin
						delay[9:0]<=DELAY_6u;
						state[9:0]<=STATE2;
					end
			 end
	STATE2:begin
				conteo[3:0]<=conteo[3:0];
				delay[9:0]<=delay[9:0]-1'b1;
				state[9:0]<=STATE2;
				if(delay[9:0]==0)
					begin
						delay[9:0]<=DELAY_6u;
						state[9:0]<=STATE3;
					end
			 end
	STATE3:begin
				conteo[3:0]<=conteo[3:0];
				delay[9:0]<=delay[9:0]-1'b1;
				state[9:0]<=STATE3;
				if(delay[9:0]==0)
					begin
						conteo[3:0]<=conteo[3:0]+1'b1;
						delay[9:0]<=DELAY_6u;
						state[9:0]<=STATE2;
						if(conteo[3:0]==15)
							begin
								delay[9:0]<=DELAY_12u;
								state[9:0]<=STATE4;
							end
					end
			 end
	STATE4:begin
				conteo[3:0]<=conteo[3:0];
				delay[9:0]<=delay[9:0]-1'b1;
				state[9:0]<=STATE4;
				if(delay[9:0]==0)
					begin
						state[9:0]<=FINISH;
					end
			 end
	FINISH:begin
				conteo[3:0]<=4'd0;
				delay[9:0]<=10'd0;
				state[9:0]<=IDLE;
			 end
	default:begin
				conteo[3:0]<=4'd0;
				delay[9:0]<=10'd0;
				state[9:0]<=IDLE;
			 end
	endcase
end


always@(negedge clock)
begin
	buttons_temp[14:0]<={data,buttons_temp[14:1]};
end

always@(posedge finish)
begin
	buttons_temp2[14:0]<=buttons_temp[14:0];
end





endmodule
