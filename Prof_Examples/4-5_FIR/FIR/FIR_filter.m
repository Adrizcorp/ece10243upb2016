% low_pass or Band_pass filters with windows Blackman Harris
clear all
clc
Nf=24     % orden del filtro 
N = Nf+1; % N?meros de Coeficientes 
n = 0;
fs = 44100;   % Frecuencia de muestreo 
fc1 = 7000;    % Frecuencia de corte m?nima
fc2 = 9000;   % Frecuencia de corte m?xima
Wc1 = (2*pi*fc1)/fs
Wc2 = (2*pi*fc2)/fs
M = floor(N/2)
  
 
for i = 1:N  
%  if(n<=N/2 && n>=0)
%     w(i)= 2*n/N;
%  else
%      w(i)= 2-2*n/N;
%  end
%  
  %w(i)= 0.5*(1-(cos((2*pi*n)/(N))));
% w(i)= 0.54-0.46*(cos((2*pi*n)/(N)));
 w(i)= 0.42-0.5*(cos((2*pi*n)/(N-1)))+0.08*(cos((4*pi*n)/(N-1)));
 % w(i) = (0.35875-0.48829*cos((2*pi*n)/(N-1))+0.14128*cos((4*pi*n)/(N-1))-0.01168*cos((6*pi*n)/(N-1)) );  
 if n ~= M
   hd(i) = ((sin(Wc1*((n)-M)))/(pi*((n)-M))) - ((sin(Wc2*((n)-M)))/(pi*((n)-M))) ;
 else
   hd(i) = 1-((Wc2-Wc1)/pi);
 end
 
 h(i) = hd(i)*w(i);
 n = n+1;
  
end

fvtool(h);

[x, fs, nbits]=wavread('song.wav'); %archivo audio
%sound(x,fs)% audio filtrado
%Escriba su codigo de su filtro aqui
%-----------------------------------



%Escriba su codigo de su filtro hasta aqui
%sound(y,fs)% audio filtrado