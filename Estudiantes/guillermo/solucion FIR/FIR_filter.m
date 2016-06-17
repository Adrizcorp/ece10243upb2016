% low_pass or Band_pass filters with windows Blackman Harris
clear all
clc
Nf=70    % orden del filtro 
N = Nf+1; % N?meros de Coeficientes 
n = 0;
fs = 44100;   % Frecuencia de muestreo 
fc1 = 6000;    % Frecuencia de corte m?nima
fc2 = 10000;   % Frecuencia de corte m?xima
Wc1 = (2*pi*fc1)/fs
Wc2 = (2*pi*fc2)/fs
M = floor(N/2)


  
 
for i = 1:N 
 w(i) = (0.54 - 0.46*(cos((2*pi*n)/N)));   
 %w(i) = (0.35875-0.48829*cos((2*pi*n)/(N-1))+0.14128*cos((4*pi*n)/(N-1))-0.01168*cos((6*pi*n)/(N-1)) );  
 if n ~= M
   hd(i) = ((sin(Wc1*((n)-M)))/(pi*((n)-M))) - ((sin(Wc2*((n)-M)))/(pi*((n)-M))) ;
 else
   hd(i) = 1-((Wc2-Wc1)/pi);
 end
 
 h(i) = hd(i)*w(i);
 n = n+1;
  
end
z=zeros(size(w));

fvtool(h);

[x, fs, nbits]=wavread('song.wav'); %archivo audio
siz=size(x);
y=zeros(size(x));
g=zeros(size(z));
v=zeros(size(z));

%Escriba su codigo de su filtro aqui
%-----------------------------------
for i=1:siz
    z(1)=x(i);
    %y(i+1)=y(1);
    for t=1:71
        g(t)=h(t)*z(t);
    end
    for u=1:71
        y(i)=y(i)+g(u);
    end
    for o=1:70
        z(72-o)=z(72-o-1);
    end   
end


%Escriba su codigo de su filtro hasta aqui

sound(y,fs)% audio filtrado