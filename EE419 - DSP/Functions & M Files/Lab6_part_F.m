[Ak, Bk, Hf, Fd] = show_filter_responses_pz([0.95*exp(j*pi*15/180), 0.95*exp(-j*pi*15/180), 0.95*exp(j*pi*7.5/180), 0.95*exp(-j*pi*7.5/180)],[1*exp(j*pi*15/180), 1*exp(-j*pi*15/180), 1*exp(j*pi*7.5/180), 1*exp(-j*pi*7.5/180)], 0.9037008, 48e3,100e3, 40, 1);

[M, C] = tf2latc(Bk, Ak); %get lattice ladder coefficients from 
[Y] = latcfilt(M, C, Hf);

plot_freq_responses(Fd, Y, 48e3, 9)

ScaleFactor = 512;

scaled_M0 = round(M(1)*ScaleFactor); 
scaled_M1 = round(M(2)*ScaleFactor); 
scaled_M2 = round(M(3)*ScaleFactor); 
scaled_M3 = round(M(4)*ScaleFactor); 

unscaled_M0 = scaled_M0/ScaleFactor;
unscaled_M1 = scaled_M1/ScaleFactor;
unscaled_M2 = scaled_M2/ScaleFactor;
unscaled_M3 = scaled_M3/ScaleFactor;

scaled_C0 = round(C(1)*ScaleFactor); 
scaled_C1 = round(C(2)*ScaleFactor); 
scaled_C2 = round(C(3)*ScaleFactor); 
scaled_C3 = round(C(4)*ScaleFactor); 
scaled_C4 = round(C(5)*ScaleFactor);

unscaled_C0 = scaled_C0/ScaleFactor;
unscaled_C1 = scaled_C1/ScaleFactor;
unscaled_C2 = scaled_C2/ScaleFactor;
unscaled_C3 = scaled_C3/ScaleFactor;
unscaled_C4 = scaled_C4/ScaleFactor;

scaled_M = [scaled_M0, scaled_M1, scaled_M2, scaled_M3];
scaled_C = [scaled_C0, scaled_C1, scaled_C2, scaled_C3, scaled_C4];

unscaled_M = [unscaled_M0, unscaled_M1, unscaled_M2, unscaled_M3];
unscaled_C = [unscaled_C0, unscaled_C1, unscaled_C2, unscaled_C3, unscaled_C4];

[Y_q] = latcfilt(unscaled_M, unscaled_C, Y);
plot_freq_responses(Fd, Y_q, 48e3, 11)
