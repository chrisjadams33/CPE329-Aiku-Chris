%define constants
time = 0.5; 
fa = 10; % analog frequency
A = 1;
theta_1 = pi/3; theta_2 = pi/3; theta_3 = pi/3; theta_5 = pi/3; 
theta_4 = pi/2; %phase shifts
Fs_1 = 200; Fs_2 = 60; Fs_3 = 20; Fs_4 = 20; Fs_5 = 12; %sampling rate

figure

%Plot 1 
t_1 = linspace(0, time, time*Fs_1 + 1);
y_1 = A*cos((2*pi*fa*t_1) + theta_1); 
plot(t_1, y_1, 'b', 'LineWidth', 4); 

%Label
xlabel('Time (s)')
ylabel('Discrete Time Sinusoidal Waveforms')
title('Overlayed Plot of Discrete Time Sinusoidal Waveforms')

hold on

%Plot 2
t_2 = linspace(0, time, time*Fs_2 + 1);
y_2 = A*cos((2*pi*fa*t_2) + theta_2); 
plot(t_2, y_2, 'r', 'LineWidth', 3); 

%Plot 3
t_3 = linspace(0, time, time*Fs_3 + 1);
y_3 = A*cos((2*pi*fa*t_3) + theta_3); 
plot(t_3, y_3, 'g', 'LineWidth', 2); 

%Plot 4
t_4 = linspace(0, time, time*Fs_4 + 1);
y_4 = A*cos((2*pi*fa*t_4) + theta_4); 
plot(t_4, y_4, 'g --', 'LineWidth', 5); 

%Plot 5
t_5 = linspace(0, time, time*Fs_5 + 1);
y_5 = A*cos((2*pi*fa*t_5) + theta_5); 
plot(t_5, y_5, 'k', 'LineWidth', 6); 



