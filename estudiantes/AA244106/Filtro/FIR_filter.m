% low_pass or Band_pass filters with windows Blackman Harris
clear all
clc
Nf=200     % orden del filtro 
N = Nf+1; % N?meros de Coeficientes 
n = 0;
fs = 44100;   % Frecuencia de muestreo 
fc1 = 4500;    % Frecuencia de corte m?nima
fc2 = 9500;   % Frecuencia de corte m?xima
Wc1 = (2*pi*fc1)/fs
Wc2 = (2*pi*fc2)/fs
M = floor(N/2)
  
 
for i = 1:N  
 %ventana Blackman-Harris
 %w(i) = (0.35875-0.48829*cos((2*pi*n)/(N-1))+0.14128*cos((4*pi*n)/(N-1))-0.01168*cos((6*pi*n)/(N-1)) );  
 
 %ventana Hamming
 w(i)=0.54-0.46*(cos((2*pi*n)/(N-1)));
 
 %ventana Blackman
 %w(i) = 0.42-0.5*cos((2*pi*n)/(N-1))+0.08*cos((4*pi*n)/(N-1));
 
 if n ~= M
   %pasa banda  
   %hd(i) = ((sin(Wc2*((n)-M)))/(pi*((n)-M))) - ((sin(Wc1*((n)-M)))/(pi*((n)-M))) ;
    
   %rechaza banda
   hd(i) = ((sin(Wc1*((n)-M)))/(pi*((n)-M))) - ((sin(Wc2*((n)-M)))/(pi*((n)-M))) ;
 else
   %pasa banda  
   %hd(i) = ((Wc2-Wc1)/pi);
   
   %rechaza banda
   hd(i) = 1-((Wc2-Wc1)/pi);
 end
 
 h(i) = hd(i)*w(i);
 n = n+1;
  
end

%vector temporal, orden+1
%fvtool(h);

[x, fs]=audioread('song.wav'); %archivo audio

%Escriba su codigo de su filtro aqui
%-----------------------------------

%y = filter(hd, hd ,x);

z = zeros(1, Nf+1);
zx = zeros(1, Nf+1);
y = zeros(1, 1272099);

x = transpose(x);
figure(1)
plot(abs(fft(x)));

%plot(y);

%Escriba su codigo de su filtro hasta aqui

for a = 1:1272099
    c = 0;
    if a > Nf
        for b = 1:Nf
            z(b) = z(b+1);           
        end
        z(Nf+1) = x(a);
    else
        z(a) = x(a);
    end
    for d = 1:(Nf+1)
        zx(d) = z(d)*hd(d);
        c = c+zx(d);
    end
    
    y(a) = c;
end
figure(2)
plot(abs(fft(y)));

sound(y,fs)% audio filtrado