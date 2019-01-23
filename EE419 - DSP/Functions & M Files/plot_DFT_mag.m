function [DFTx, Fd] = plot_DFT_mag(x, fsample, figure_num)
% This function takes three arguments: x, fsample, and the figure #. x
% represents the number of time domain samples of a discrete-time sequence.
% The function returns the DFT magn. plotted vs. digital frequency and also
% vs. analog frequency.

Mx = length(x);
Fd = (0:Mx-1)/Mx;
fftx = fft(x);

figure(figure_num)
subplot(2, 1, 1)
stem(Fd, abs(fftx)/Mx, '.', 'MarkerSize', 20, 'Linewidth', 2);
xlabel('Sample index')
ylabel('DFT Magnitude')
title('Digital Frequency Response of Filter')

fa = Fd*fsample;

subplot(2, 1, 2)
stem(fa, abs(fftx)/Mx, '.', 'MarkerSize', 20, 'Linewidth', 2);
xlabel('Sample index')
ylabel('DFT Magnitude')
title('Analog Frequency Response of Filter')


end