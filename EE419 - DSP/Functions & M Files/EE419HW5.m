n = 0:100;

x1 = cos(2*pi*(0.02)*n-0.02*pi*4);
x2 = 0.6*cos(2*pi*(0.04)*n-0.04*pi*4);
x3 = 0.4*cos(2*pi*(0.1)*n-0.1*pi*4);

x4 = x1 + x2 + x3;

figure

subplot(4,1,1)
stem(n, x1) 

xlabel('Sample Number')
ylabel('Amplitude')
%title('Discrete Convolution with Unit Step')
grid
subplot(4,1,2)
stem(n, x2) 

xlabel('Sample Number')
ylabel('Amplitude')
grid
subplot(4,1,3)
stem(n, x3) 

xlabel('Sample Number')
ylabel('Amplitude')
grid

subplot(4,1,4)
plot(n, x4, 'g', 'Linewidth', 2) 

xlabel('Sample Number')
ylabel('Amplitude')
grid
