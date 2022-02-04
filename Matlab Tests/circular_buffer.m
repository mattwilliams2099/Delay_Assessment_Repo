clc;
clear all;
close all;

N = 10;
delaylength = 5;
bufferLength = delaylength + 1;
x = [1 (zeros (1,9))];
del_buffer = zeros (1, bufferLength);
y = zeros (1, N);

for m = 1:N 
    for n = (bufferLength - 1) : -1 : 1    
        del_buffer (n + 1) = del_buffer (n);
    end
del_buffer (1) = x (m);  
y (m) = x (m) + (0.5 *  del_buffer (bufferLength));
end
figure(1);

tiledlayout(2, 1);
nexttile;
stem(x);
title("x[n]");
axis([0 10 -0.5 1.5]);
grid on;

nexttile;
stem(y);
title("y[n]");
axis([0 10 -0.5 1.5]);
grid on;

%%

N = 10;
bufferLength = 6;
delaylength = 5;
x = [1 (zeros (1,9))];
del_buffer = zeros (1, bufferLength);
y = zeros (1, N);
w_index = 1;
r_index = w_index - delaylength;
if r_index < 0
    r_index = bufferLength + r_index;
end

for m = 1:N
    del_buffer(w_index) = x(m);
     y(m) = x(m) + (0.5 * del_buffer(r_index));   
    r_index = r_index + 1;
    if r_index > bufferLength
        r_index = r_index - bufferLength;
    end
    w_index = w_index + 1;
    if w_index > bufferLength
        w_index = w_index - bufferLength;
    end
end

figure(2);
tiledlayout(2, 1);
nexttile;
stem(x);
title("x[n]");
axis([0 10 -0.5 1.5]);
grid on;

nexttile;
stem(y);
title("y[n]");
axis([0 10 -0.5 1.5]);
grid on;