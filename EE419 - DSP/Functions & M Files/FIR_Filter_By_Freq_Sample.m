function [hn, HF, F] = FIR_Filter_By_Freq_Sample(HF_mag_samples, figure_num)
%This function

% part a
k = 0:length(HF_mag_samples)-1; %# of mag samples is M 
M = length(k);                % M is equal to # k samples for DFT 

Hk_angle = exp(-j*pi.*k*(M-1)/M); 
Hk = HF_mag_samples.*Hk_angle; 

hn = real(ifft(Hk)); 

% part b
M_no_pad = M;                   %for use in low-res FFT ==> DFT, discrete
HF_no_pad = fft(hn, M_no_pad);  %compute non-padded HF

M_pad = 2^12;                   %for use in high-res FFT ==> "DTFT", psuedo continuous
HF = fft(hn, M_pad);            %compute padded HF
F = 0:1/(M_pad-1):1;           %sample freq. spacing

%plot digital frequency response
figure(figure_num)
subplot(2,1,1)
plot(F, abs(HF)) %plot magnitude response (linear)
xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Magnitude Response')
title('Digital Frequency Response of Filter')

hold on

%superimpose non-padded DFT magnitude
stem(k/M, abs(HF_no_pad), '.', 'MarkerSize', 20, 'Linewidth', 2);

subplot(2,1,2)
plot(F, angle(HF)) %plot phase response
xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Phase Response') 

hold on

%superimpose non-padded DFT phase
stem(k/M, angle(HF_no_pad), '.', 'MarkerSize', 20, 'Linewidth', 2);


%part c, plot magnitude response (in dB this time)
F_c = 0:1/(M_pad-1):0.5;                   %F = 0-0.5 instead of F =0-1 like before
figure(figure_num + 1)
plot(F_c, 20*log10(HF(0:0.5*(M_pad - 1)))) %only take up to F = 0.5 worth of HF
xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Magnitude Response in dB')
title('Digital Frequency Response of Filter')




end
