function hn_lp = FIR_Filter_By_Window(M, Fc, window)
% This function 

%test this func. using: hn_lp = FIR_Filter_By_Window(9, 0.3, hamming(9))

n = -(M-1)/2:(M-1)/2;
h_ideal = sin(2*pi.*n*Fc)/pi./n;
h_ideal(((M-1)/2)+1) = 2*Fc;
h_window = window.'; 
hn_lp = h_ideal.*h_window;

end