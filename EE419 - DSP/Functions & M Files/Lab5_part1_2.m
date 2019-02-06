fs = 50e3; %sampling freq.
T = 2;     %sapling period

% load echo data
x1 = DeadAheadEcho;         Mx1 = length(DeadAheadEcho);        t_x1 = 0:T/(Mx1-1):T;
x2 = StarboardBowEcho;      Mx2 = length(StarboardBowEcho);     t_x2 = 0:T/(Mx2-1):T;
x3 = StarboardBeamEcho;     Mx3 = length(StarboardBeamEcho);    t_x3 = 0:T/(Mx3-1):T;    
x4 = StarboardQuarterEcho;  Mx4 = length(StarboardQuarterEcho); t_x4 = 0:T/(Mx4-1):T;
x5 = DeadAsternEcho;        Mx5 = length(DeadAsternEcho);       t_x5 = 0:T/(Mx5-1):T;
x6 = PortQuarterEcho;       Mx6 = length(PortQuarterEcho);      t_x6 = 0:T/(Mx6-1):T;     
x7 = PortBeamEcho;          Mx7 = length(PortBeamEcho);         t_x7 = 0:T/(Mx7-1):T;
x8 = PortBowEcho;           Mx8 = length(PortBowEcho);          t_x8 = 0:T/(Mx8-1):T;

% plot time-domain waveforms 
figure(1)

subplot(4, 2, 1)
plot(t_x1, x1)
xlabel('Time (s)')
ylabel('Magnitude')
title('Time-domain Waveform: DeadAheadEcho')

hold on

subplot(4, 2, 3)
plot(t_x2, x2)
xlabel('Time (s)')
ylabel('Magnitude')
title('Time-domain Waveform: StarboardBowEcho')

subplot(4, 2, 5)
plot(t_x3, x3)
xlabel('Time (s)')
ylabel('Magnitude')
title('Time-domain Waveform: StarboardBeamEcho')

subplot(4, 2, 7)
plot(t_x4, x4)
xlabel('Time (s)')
ylabel('Magnitude')
title('Time-domain Waveform: StarboardQuarterEcho')

subplot(4, 2, 2)
plot(t_x5, x5)
xlabel('Time (s)')
ylabel('Magnitude')
title('Time-domain Waveform: DeadAsternEcho')

subplot(4, 2, 4)
plot(t_x6, x6)
xlabel('Time (s)')
ylabel('Magnitude')
title('Time-domain Waveform: PortQuarterEcho')

subplot(4, 2, 6)
plot(t_x7, x7)
xlabel('Time (s)')
ylabel('Magnitude')
title('Time-domain Waveform: PortBeamEcho')

subplot(4, 2, 8)
plot(t_x8, x8)
xlabel('Time (s)')
ylabel('Magnitude')
title('Time-domain Waveform: PortBowEcho')

% plot analog frequency responses
% Fd_x1 = (0:Mx1-1)/Mx1; Fd_x2 = (0:Mx2-1)/Mx2; Fd_x3 = (0:Mx3-1)/Mx3;
% fa_x1 = Fd_x1*fs; fa_x2 = Fd_x2*fs; fa_x3 = Fd_x3*fs; 
% 
% fftx1 = fft(x1); fftx2 = fft(x2); fftx3 = fft(x3);
% 
% figure(2) 
% 
% subplot(4, 2, 1)
% plot(fa_x1, abs(fftx1)/Mx1)
% xlabel('Sample Index')
% ylabel('DFT Magnitude')
% title('Analog Frequency Frequency Response: ')
% 
% hold on
% 
% subplot(4, 2, 3)
% plot(fa_x2, abs(fftx2)/Mx2)
% xlabel('Sample Index')
% ylabel('DFT Magnitude')
% title('Analog Frequency Frequency Response: ')
% 
% subplot(4, 2, 5)
% plot(fa_x3, abs(fftx3)/Mx3)
% xlabel('Sample Index')
% ylabel('DFT Magnitude')
% title('Analog Frequency Frequency Response: ')

% listen to echos
% soundsc(x1)
% pause(20)
% soundsc(x2)
% pause(2)
% soundsc(x3)
% pause(2)
% soundsc(x4)
% pause(2)
% soundsc(x5)
% pause(2)
% soundsc(x6)
% pause(2)
% soundsc(x7)
% pause(2)
% soundsc(x8)
