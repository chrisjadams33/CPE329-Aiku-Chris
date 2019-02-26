points = 10e3;              %total point convolution
n = 0:points;
dt = 10e-6;                 %time between points
h_n = 1000*exp(-1000*n*dt); %impulse response

x1 = ones(1,points+1);      %step
x2 = (n*dt).*x1;            %ramp
x3 = sin(2*pi*159*n*dt);    %sinusoid 159 Hz

time = n*1000;
ystore = 0;

c = 1;
%discrete convolution
for i=1:(length(h_n))
    while (c <= i)
        ystore = ystore + h_n(c)*x1(i+1-c);
        c = c+1;
    end
    y1(i) = ystore;
    ystore = 0;
    c = 1;
end

for i=1:(length(h_n))
    while (c <= i)
        ystore = ystore + h_n(c)*x2(i+1-c);
        c = c+1;
    end
    y2(i) = ystore;
    ystore = 0;
    c = 1;
end

for i=1:(length(h_n))
    while (c <= i)
        ystore = ystore + h_n(c)*x3(i+1-c);
        c = c+1;
    end
    y3(i) = ystore;
    ystore = 0;
    c = 1;
end

figure

subplot(3,1,1)
plot(time, x1) 

xlabel('time (ms)')
ylabel('Unit Step (x1)')
title('Discrete Convolution with Unit Step')
grid
subplot(3,1,2)
plot(time, h_n) 

xlabel('time (ms)')
ylabel('Impulse Response (h[n])')
grid
subplot(3,1,3)
plot(time, y1) 

xlabel('time (ms)')
ylabel('Filter Output (x1)')
grid

figure

subplot(3,1,1)
plot(time, x2) 

xlabel('time (ms)')
ylabel('Ramp (x2)')
title('Discrete Convolution with Ramp')
grid
subplot(3,1,2)
plot(time, h_n) 

xlabel('time (ms)')
ylabel('Impulse Response (h[n])')
grid
subplot(3,1,3)
plot(time, y2) 

xlabel('time (ms)')
ylabel('Filter Output (x2)')
grid

figure
subplot(3,1,1)
plot(time, x3) 

xlabel('time (ms)')
ylabel('Sunusoid 159Hz (x3)')
title('Discrete Convolution with Sinusoid (159Hz)')
grid
subplot(3,1,2)
plot(time, h_n) 

xlabel('time (ms)')
ylabel('Impulse Response (h[n])')
grid
subplot(3,1,3)
plot(time, y3) 

xlabel('time (ms)')
ylabel('Filter Output (y3)')
grid