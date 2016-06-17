% low_pass or Band_pass filters with windows Blackman Harris
clear all
clc
Nf=70     % orden del filtro 
N = Nf+1; % N?meros de Coeficientes 
n = 0;
fs = 44100;   % Frecuencia de muestreo 
fc1 = 6000;    % Frecuencia de corte m?nima
fc2 = 10000;   % Frecuencia de corte m?xima
Wc1 = (2*pi*fc1)/fs
Wc2 = (2*pi*fc2)/fs
M = floor(N/2)
valor=0;
conteo=0;
sum=0;
  
 
for i = 1:N  
 
    w(i) = (0.54 - 0.46*(cos((2*pi*n)/N)));
    %w(i) = (0.35875-0.48829*cos((2*pi*n)/(N-1))+0.14128*cos((4*pi*n)/(N-1))-0.01168*cos((6*pi*n)/(N-1)) );  
 if n ~= M
   hd(i) = ((sin(Wc1*((n)-M)))/(pi*((n)-M))) - ((sin(Wc2*((n)-M)))/(pi*((n)-M))) ;
 else
   hd(i) = 1 - ((Wc2-Wc1)/pi);
 end
 
 h(i) = hd(i)*w(i);
 n = n+1;
  
end

%fvtool(h);

[x, fs, nbits]= wavread('song.wav'); %archivo audio

%Escriba su codigo de su filtro aqui
%-----------------------------------
for t = 1:1272100
        y(t)=0;
  end
  for o = 1:N
        v(o)=0;
        z(o)=0;
  end
for i = 1:1272099
    z(1)= x(i);
  for k = 1:N %suma de los vectores z y h
       v(k)= z(k)* h(k);
  end
  for a = 1:N %suma de los vectores z y h
           y(i)= y(i) + v(a);
  end
  for j=1:Nf
    z(72-j)=z(72-j-1);
  end
end
fvtool(y);
%Escriba su codigo de su filtro hasta aqui

sound(y,fs)% audio filtrado