%% DSPBA Design Parameters Start

%% System Parameters
my_design.ChanCount   = 4;                    % How many data channels
my_design.ClockRate   = 200.000000;           % The system clock rate in MHz
my_design.SampleRate  = 50.000000;            % The data rate per channel in MSps (mega-samples per second)
my_design.ClockMargin = 0.0;                  % Adjust the pipelining effort


%% Simulation Parameters
my_design.SampleTime  = 1;                    % One unit in Simulink simulation is one clock cycle 
my_design.endTime     = 100;                  % How many simulation clock cycles

%% Stimulus data setup
my_design.inputdata=zeros(my_design.ChanCount,my_design.endTime+1);
for chan=1:my_design.ChanCount
    my_design.inputdata(chan,:) = sin((0:my_design.endTime)*pi/10*chan)/chan;
end;

%% ModelIP setup
my_design.filter1.SampleRate     = my_design.SampleRate;        % Input rate at filter1
my_design.filter1.FilterLength   = 49;                          % Number of Taps
my_design.filter1.Interpolation  = 2;                           % Interpolation rate  

%% Derived Parameters 
my_design.Period          = my_design.ClockRate / my_design.SampleRate;           % Clock cycles between consecutive data samples for a particular channel
my_design.ChanWireCount   = ceil(my_design.ChanCount/my_design.Period);           % How many wires are needed to support the specified number of channels?
my_design.ChanCycleCount  = ceil(my_design.ChanCount/my_design.ChanWireCount);    % Range of the channel signal
%% DSPBA Design Parameters End