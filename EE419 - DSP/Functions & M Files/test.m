%% Part 1 Optimal FIR Design Via Parks-McClellan
[N, Fo, Ao, W] = firpmord([0.1333, 0.2667], [1 0], [0.013, 0.013], 1);
b = firpm(N, Fo, Ao, W);
[poles, zeros, HF, Fd, hn, n] = show_filter_response([1], b, 1e3, 100e3, 40, 1);
 
 
%% Part 2 Butterworth 
[n, Wn] = buttord(0.1333*2, 0.2667*2, 0.1137, 37.721);
[butter_b, butter_a] = butter(n,Wn);
[poles, zeros, HF, Fd, hn, n] = show_filter_response(butter_a, butter_b, 1e3, 100e3, 40, 1);
 
 
%% Part 3 Chebyshev 1 
[N, Wp] = cheb1ord(0.1333*2, 0.2667*2, 0.1137, 37.721);
[cheb1_b, cheb1_a] = cheby1(N, 0.1137, Wp);
[poles, zeros, HF, Fd, hn, n] = show_filter_response(cheb1_a, cheb1_b, 1e3, 100e3, 40, 1);
 
%% Part 4 Chebyshev 2 
[N, Ws] = cheb2ord(0.1333*2, 0.2667*2, 0.1137, 37.721);
[cheb2_b, cheb2_a] = cheby2(N, 37.721, Ws);
[poles, zeros, HF, Fd, hn, n] = show_filter_response(cheb2_a, cheb2_b, 1e3, 100e3, 40, 1);
 
%% Part 5 Elliptical
[N, Wp] = ellipord(0.1333*2, 0.2667*2, 0.1137, 37.721);
[ellip_b, ellip_a] = ellip(N, 0.1137, 37.721, Wp);
[poles, zeros, HF, Fd, hn, n] = show_filter_response(ellip_a, ellip_b, 1e3, 100e3, 40, 1);

[h_butter] = freqz(butter_b,1,1024);
[h_cheb1] = freqz(cheb1_b,1,1024);
[h_cheb2] = freqz(cheb2_b,1,1024);
[h_ellip] = freqz(ellip_b,1,1024);
[h_pm] = freqz(b,1,1024);