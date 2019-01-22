function plot_freq_responses(Fd, HF, fsample, figure_num)

%plot frequency response (digital)
figure(figure_num)

subplot(2,1,1)
plot(Fd, abs(HF)) %plot magnitude response (linear)

xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Magnitude Response')
title('Digital Frequency Response of Filter')

subplot(2,1,2)
plot(Fd, angle(HF)) %plot phase response

xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Phase Response') 


%plot frequency response (analog)

figure(figure_num + 1)

Fa = Fd*fsample; %convert digital frequency Fd into analog frequency

subplot(2,1,1)
plot(Fa, 20*log10(HF)) %plot magnitude response (in dB)

xlabel('Analog Frequency  f (Hz)')
ylabel('Magnitude Response in dB')
title('Analog Frequency Response of Filter')

subplot(2,1,2)
plot(Fa, angle(HF)) %plot phase response

xlabel('Analog Frequency  f (Hz)')
ylabel('Phase Response')
end 

