%% Part 1 Optimal FIR Design Via Parks-McClellan
[N, Fo, Ao, W] = firpmord([0.1333, 0.2667], [1 0], [0.013, 0.013], 1);
b = firpm(N, Fo, Ao, W);

%% Part 2 Butterworth 
[n, Wn] = buttord(0.1333*2, 0.2667*2, 0.1137, 37.721);
[butter_b, butter_a] = butter(n,Wn);

%% Part 3 Chebyshev 1 
[N, Wp] = cheb1ord(0.1333*2, 0.2667*2, 0.1137, 37.721);
[cheb1_b, cheb1_a] = cheby1(N, 0.1137, Wp);

%% Part 4 Chebyshev 2 
[N, Ws] = cheb2ord(0.1333*2, 0.2667*2, 0.1137, 37.721);
[cheb2_b, cheb2_a] = cheby2(N, 37.721, Ws);

%% Part 5 Elliptical
[N, Wp] = ellipord(0.1333*2, 0.2667*2, 0.1137, 37.721);
[ellip_b, ellip_a] = ellip(N, 0.1137, 37.721, Wp);

%% Composite magnitude plots in linear and in dB
[poles_pm, zeros_pm] = plot_mag_responses([1 0 0 0 0 0 0 0 0 0 0 0 0 0], b, 100e3, 10);
[poles_butt, zeros_butt] = plot_mag_responses(butter_a, butter_b, 100e3, 11);
[poles_cheb1, zeros_cheb1] = plot_mag_responses(cheb1_a, cheb1_b, 100e3, 12);
[poles_cheb2, zeros_cheb2] = plot_mag_responses(cheb2_a, cheb2_b, 100e3, 13);
[poles_ellip, zeros_ellip] = plot_mag_responses(ellip_a, ellip_b, 100e3, 14);

% for x=1:length(poles_butt)
%     for y=1:length(zeros_butt)
%         diff(y) = abs(abs(poles_butt(x)) - abs(zeros_butt(y)));
%         best_idx = find(diff == min(diff));
%         
%     end
%     
% end


