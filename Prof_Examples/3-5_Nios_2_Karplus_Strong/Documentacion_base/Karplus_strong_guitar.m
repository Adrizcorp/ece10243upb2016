Fs = 16000;
p = 156; %length of delay line
tmax = 7;
sr = rand(1,p); %initial shift register contents
out = zeros(1,Fs*tmax);
ptrout = 2; %pointer to sr
ptrin = 1; %pointer to sr
factor = 0.5; %decay factor 0<factor<=0.5

for i=1:Fs*tmax
    out(i) = sr(ptrin);
    sr(ptrin) = (sr(ptrin)+sr(ptrout))*factor;
    %updata and wrap pointers
    if (ptrin==p) ptrin=1;
    else ptrin=ptrin+1;
    end
    if (ptrout==p)ptrout=1;
    else ptrout=ptrout+1;
    end
end

sound(out,Fs)
plot(out)


