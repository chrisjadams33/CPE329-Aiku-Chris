function [poles, zeros] = plot_mag_responses(Ak, Bk, num_f_points, i)

figure(i)
poles = roots(Ak);
zeros = roots(Bk);
zplane(Bk, Ak);
grid
title('Pole Zero Diagram')

%plot the frequency response
HF = freqz(Bk, Ak, num_f_points);
Fd = linspace(0, 0.5, num_f_points);

figure(1)

subplot(2,1,1)
plot(Fd, abs(HF)) %plot magnitude response (linear)
axis([0 0.5 0 0.05])
xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Magnitude Response')
title('Digital Frequency Response of Filter')

hold on

subplot(2,1,2)
plot(Fd, abs(HF)) %plot phase response
axis([0 0.25 0.95 1.05])
xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Magnitude Response') 

hold on

figure(2)

subplot(2,1,1)
plot(Fd, 20*log10(abs(HF))) %plot magnitude response (linear)
axis([0 0.5 -50 10])
xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Magnitude Response in dB')
title('Digital Frequency Response of Filter')

hold on

subplot(2,1,2)
plot(Fd, 20*log10(abs(HF))) %plot phase response
axis([0 0.25 -0.5 0.5])
xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Magnitude Response in dB') 

hold on

end