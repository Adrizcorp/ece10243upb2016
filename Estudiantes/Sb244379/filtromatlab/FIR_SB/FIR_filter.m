% low_pass or Band_pass filters with windows Blackman Harris
clear all
clc
Nf=110    % orden del filtro debe ser par
N = Nf+1; % N?meros de Coeficientes 
n = 0;
fs = 44100;   % Frecuencia de muestreo 
fc1 = 5500;    % Frecuencia de corte m?nima
fc2 = 9500;   % Frecuencia de corte m?xima
Wc1 = (2*pi*fc1)/fs;
Wc2 = (2*pi*fc2)/fs;
M = floor(N/2);
  
 
for i = 1:N  
 %ventada tipo Blackman-Harris    
 %w(i) = (0.35875-0.48829*cos((2*pi*n)/(N-1))+0.14128*cos((4*pi*n)/(N-1))-0.01168*cos((6*pi*n)/(N-1)) ); 
 %ventana Haming
 w(i)=0.54-0.46*(cos((2*pi*n)/(N-1)));
 %Ventana Blackman 
 %w(i)= 0.42-0.5*cos((2*pi)/(N-1))+0.08*cos((4*pi*n)/(N-1));
 if n ~= M
 %Filtro pasa banda
 %hd(i) = ((sin(Wc2*((n)-M)))/(pi*((n)-M))) - ((sin(Wc1*((n)-M)))/(pi*((n)-M))) ; %filtro pasa banda
 %Filtro rechaza banda
 hd(i) = ((sin(Wc1*((n)-M)))/(pi*((n)-M))) - ((sin(Wc2*((n)-M)))/(pi*((n)-M))) ;
 else
    hd(i) = 1-((Wc2-Wc1)/pi); 
   %hd(i) = ((Wc2-Wc1)/pi);
 end
 
 h(i) = hd(i)*w(i);
 n = n+1;
  
end

fvtool(h);

[x, fs, nbits]=wavread('song.wav'); %archivo audio
plot  (x)
%Escriba su codigo de su filtro aqui
%-----------------------------------

% x vector de la señal
% z vector con la cantidad de numero de coeficientes
% hd 
% y vector señal filtrada

z=zeros(1,Nf);
x=transpose(x);

for a=1:1272099;

    temp=0;
    temp1=0;
    if a > 100
        for c=1:109
          z(c)=z(c+1);     
        end
        z(110)=x(a);
    end
    for b=1:110;
        
        temp=temp1+(z(b)*h(b));
        temp1=temp;
            
    end
    
    y(a)=temp1; 
end


%Escriba su codigo de su filtro hasta aqui

sound(y,fs)% audio filtrado