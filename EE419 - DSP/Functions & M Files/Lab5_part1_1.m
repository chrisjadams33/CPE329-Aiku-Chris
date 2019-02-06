
% load sonar pulse data
xn = TxPulse;
Mx = length(TxPulse);
% load echo data
yn_1 = TyphoonSubEcho; yn_2 = AkulaSubEcho; yn_3 = LosAngelesSubEcho; 
My_1 = length(yn_1); My_2 = length(yn_2); My_3 = length(yn_3);

% plot time-domain waveforms 
fs = 50e3; %sampling freq.
T = 0.05;  %sapling period
t_x = 0:T/(Mx-1):T;  %acquire time axis for sonar pulse
t_yn_1 = 0:T/(My_1-1):T; t_yn_2 = 0:T/(My_2 - 1):T; t_yn_3 = 0:T/(My_3 - 1):T; %acquire time axis for echo signals

figure(1)

subplot(4, 1, 1)
plot(t_x, xn)
xlabel('Time (s)')
ylabel('Magnitude')
title('Time-domain Waveform: Sonar Pulse')

hold on

subplot(4, 1, 2)
plot(t_yn_1, yn_1)
xlabel('Time (s)')
ylabel('Magnitude')
title('Time-domain Waveform: Typhoon Sub Echo')

subplot(4, 1, 3)
plot(t_yn_2, yn_2)
xlabel('Time (s)')
ylabel('Magnitude')
title('Time-domain Waveform: Akula Sub Echo')

subplot(4, 1, 4)
plot(t_yn_3, yn_3)
xlabel('Time (s)')
ylabel('Magnitude')
title('Time-domain Waveform: LA Sub Echo')

%take and then plot DFTs of each of the time domain signals 
Fd_x = (0:Mx-1)/Mx; 
Fd_y_1 = (0:My_1-1)/My_1; Fd_y_2 = (0:My_2-1)/My_2; Fd_y_3 = (0:My_3-1)/My_3; 

fa_x = Fd_x*fs;
fa_y_1 = Fd_y_1*fs; fa_y_2 = Fd_y_2*fs; fa_y_3 = Fd_y_3*fs; 

fftx = fft(xn); %take the fft of the sonar pulse
fft_y_1 = fft(yn_1); fft_y_2 = fft(yn_2); fft_y_3 = fft(yn_3); %fft of echo signals

figure(2) 

subplot(4, 1, 1)
plot(fa_x, abs(fftx)/Mx)
xlabel('Sample Index')
ylabel('DFT Magnitude')
title('Analog Frequency Frequency Response: Sonar Pulse')

hold on

subplot(4, 1, 2)
plot(fa_y_1, abs(fft_y_1)/My_1)
xlabel('Sample Index')
ylabel('DFT Magnitude')
title('Analog Frequency Response: Typhoon Sub Echo')

subplot(4, 1, 3)
plot(fa_y_2, abs(fft_y_2)/My_2)
xlabel('Sample Index')
ylabel('DFT Magnitude')
title('Analog Frequency Response: Akula Sub Echo')

subplot(4, 1, 4)
plot(fa_y_3, abs(fft_y_3)/My_3)
xlabel('Sample Index')
ylabel('DFT Magnitude')
title('Analog Frequency Response: LA Sub Echo')

%listen to sampled (n) sounds of Sonar Pulse and Echos
soundsc(abs(fftx)/Mx);
soundsc(abs(fft_y_1)/My_1);
soundsc(abs(fft_y_2)/My_2);
soundsc(abs(fft_y_3)/My_3);


