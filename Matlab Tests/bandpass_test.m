clc;
clear all;

L = 48000;
Fs = 48000;
N = L;
                     
T = 1/Fs;
f = 0.5;                                                                       
phase = 0;
Q = 1.0; 
fc = 15000;                                
omega = 2 * pi * (fc/Fs);
alpha = (2 * sin(omega))/(2 * Q);

b0 = alpha;
b1 = 0;
b2 = -alpha;
a0 = 1 + alpha;
a1 = - 2 * cos(omega);
a2 = 1 - alpha;

b0 = b0 / a0;
b1 = b1 / a0;
b2 = b2 / a0;
a1 = a1 / a0;
a2 = a2 / a0;
a0 = a0 / a0;
x   = zeros(N,1);
x(1) = 1;

y = zeros(N,1);

xz1 = 0;
xz2 = 0;
yz1 = 0;
yz2 = 0;


for n = 1:N
    y(n) = x(n)*b0 + xz1*b1 + xz2*b2 - yz1*a1 - yz2*a2 ;
    xz2 = xz1;
    xz1 = x(n);                   
    yz2 = yz1;
    yz1 = y(n);
end

plot(linspace(0,Fs,N),20*log10(abs(fft(y))));
xlim ([0 24000]);
