function [Cxy, index] =  NormCrossCorrelate(xn, yn)

My = length(yn);       %compute lengths
Mx = length(xn);
M = My + Mx - 1;       %number of samples for fft is sum of lenghts - 1
n = 2^(nextpow2(M));   %for most efficient fft computation

extra = floor(n-M);
index = (0:M-1) - floor(M/2);

Xk = fft(xn, n);       %fft of x[n]
Yk = fft(yn, n);       %fft of h[n]
Ck = Xk.*conj(Yk);      %convolution in time domain is multiplication in freq. 

cn = real(ifft(Ck));   %get good parts of fft of y[n] after doing the inv fft

rxx = real(ifft(Xk.*conj(Xk)));
ryy = real(ifft(Yk.*conj(Yk)));
Cxy_temp = cn/(sqrt(rxx(1)*ryy(1)));

Cxy_neg = Cxy_temp((n/2)+1:end);
Cxy_pos = Cxy_temp(1:(n/2));

Cxy = [Cxy_neg Cxy_pos];
Cxy = Cxy(extra/2+1:end-extra/2);

%Generate plots
    figure(1)

    %make stem plot of input
    subplot(3, 1, 1)
    stem(0:(length(xn)-1), xn, '.', 'MarkerSize', 20, 'Linewidth', 2);
    xlabel('Sample Index')
    ylabel('Amplitude')
    title('x[n] Sequence')

    %make stem plot of unit sample response
    subplot(3, 1, 2)
    stem(0:(length(yn)-1), yn, '.', 'MarkerSize', 20, 'Linewidth', 2);
    xlabel('Sample Index')
    ylabel('Amplitude')
    title('y[n] Sequence')

    %make stem plot of output
    subplot(3, 1, 3)
    stem(index, Cxy, '.', 'MarkerSize', 20, 'Linewidth', 2);
    xlabel('Sample Index')
    ylabel('Normalized Amplitude')
    title('Cross Correlation Between x[n] and y[n]')

end