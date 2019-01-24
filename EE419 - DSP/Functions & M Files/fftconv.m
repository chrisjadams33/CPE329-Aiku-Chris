function yn = fftconv(xn, hn)
% This function takes two input arguments: the xn coefficients and unit
% sample response. The function computes the FFT and returns one figure
% with 6 subplots: stem plots of x[n], h[n], and y[n] and plots of the
% magnitude responses for them.

Mh = length(hn);       %compute lengths
Mx = length(xn);
M = Mh + Mx - 1;       %number of samples for fft is sum of lenghts - 1
n = 2^(nextpow2(M));   %for most efficient fft computation  

k_x = [0 :1 : Mx - 1]; %for plotting x[n], x-axis
k_h = [0: 1: Mh - 1];  %for plotting h[n], x-axis
k_y = [0: 1: M - 1];   %for plotting y[n], x-axis

Xk = fft(xn, n);       %fft of x[n]
Hk = fft(hn, n);       %fft of h[n]
Yk = Xk.*Hk;           %convolution in time domain is multiplication in freq. 

yn = real(ifft(Yk));   %get good parts of fft of y[n] after doing the inv fft

if (Mh > 1000) or (Mx > 1000) %check to see if excessive # of points to plot
    produce_plots = 0;
else
    %Generate plots
    figure(1)

    %make stem plot of input
    subplot(3, 2, 1)
    stem(k_x, xn, '.', 'MarkerSize', 20, 'Linewidth', 2);
    xlabel('Sample index')
    ylabel('Amplitude')
    title('x[n] sequence')

    %make stem plot of unit sample response
    subplot(3, 2, 3)
    stem(k_h, hn, '.', 'MarkerSize', 20, 'Linewidth', 2);
    xlabel('Sample index')
    ylabel('Amplitude')
    title('h[n] sequence')

    %make stem plot of output
    subplot(3, 2, 5)
    stem(0:M-1, yn(1:M), '.', 'MarkerSize', 20, 'Linewidth', 2);
    xlabel('Sample index')
    ylabel('Amplitude')
    title('h[n] sequence')

    %plot magnitude responses
    %plot Xk_mag
    Fd = (0:(length(Yk)-1))/length(Yk); %compute the sampled digital F, x-axis
    Xk_mag = abs(Xk);

    subplot(3, 2, 2)
    plot(Fd, Xk_mag)
    xlabel('Sample index')
    ylabel('Magnitude Response')
    title('X[k] Spectrum')

    %plot Hk_mag
    Hk_mag = abs(Hk);

    subplot(3, 2, 4)
    plot(Fd, Hk_mag)
    xlabel('Sample index')
    ylabel('Magnitude Response')
    title('H[k] Spectrum')

    %plot Yk_mag
    Yk_mag = abs(Yk);

    subplot(3, 2, 6)
    plot(Fd, Yk_mag)
    xlabel('Sample index')
    ylabel('Magnitude Response')
    title('Y[k] Spectrum')

end
