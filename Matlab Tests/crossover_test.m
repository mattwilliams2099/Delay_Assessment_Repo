clc;
clear all;

L = 48000;
Fs = 48000;
N = L;
                     
T = 1/Fs;
f = 0.5;                                                                       
phase = 0;
Q = 0.5; 
fc = 1000;                                
omega = 2 * pi * (fc/Fs);
alpha = (sin(omega))/(2 * Q);

b0_l = (1 - cos(omega))/2;
b1_l = 1 - cos(omega);
b2_l = (1 - cos(omega))/2;
a0_l = 1 + alpha;
a1_l = - 2 * cos(omega);
a2_l = 1 - alpha;

b0_l = b0_l / a0_l;
b1_l = b1_l / a0_l;
b2_l = b2_l / a0_l;
a1_l = a1_l / a0_l;
a2_l = a2_l / a0_l;
a0_l = a0_l / a0_l;

b0_r = (1 + cos(omega))/2;
b1_r = -(1 + cos(omega));
b2_r = (1 + cos(omega))/2;
a0_r = 1 + alpha;
a1_r = - 2 * cos(omega);
a2_r = 1 - alpha;

b0_r = b0_r / a0_r;
b1_r = b1_r / a0_r;
b2_r = b2_r / a0_r;
a1_r = a1_r / a0_r;
a2_r = a2_r / a0_r;
a0_r = a0_r / a0_r;

x   = zeros(N,1);
x(1) = 1;

y_l = zeros(N,1);
y_r = zeros(N,1);

xz1 = 0;
xz2 = 0;
yz1 = 0;
yz2 = 0;


for n = 1:N
    y_l(n) = x(n)*b0_l + xz1*b1_l + xz2*b2_l - yz1*a1_l - yz2*a2_l ;
    xz2 = xz1;
    xz1 = x(n);                   
    yz2 = yz1;
    yz1 = y_l(n);
end

xz1 = 0;
xz2 = 0;
yz1 = 0;
yz2 = 0;


for n = 1:N
    y_r(n) = x(n)*b0_r + xz1*b1_r + xz2*b2_r - yz1*a1_r - yz2*a2_r ;
    xz2 = xz1;
    xz1 = x(n);                   
    yz2 = yz1;
    yz1 = y_r(n);
end

y = y_l + (-y_r);

plot(linspace(0,Fs,N),20*log10(abs(fft(y))));
hold on;
plot(linspace(0,Fs,N),20*log10(abs(fft(y_l))));
hold on;
plot(linspace(0,Fs,N),20*log10(abs(fft(y_r))));
xlim ([0 24000]);
