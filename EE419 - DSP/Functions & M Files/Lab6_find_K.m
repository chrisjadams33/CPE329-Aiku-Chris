
k = 1;

while (k<10001)
    
    [Ak,Bk,HF,Fd,hn,n, maximum]= show_filter_responses_pz([0.95*exp(j*pi*15/180), 0.95*exp(-j*pi*15/180), 0.95*exp(j*pi*7.5/180), 0.95*exp(-j*pi*7.5/180)],[1*exp(j*pi*15/180), 1*exp(-j*pi*15/180), 1*exp(j*pi*7.5/180), 1*exp(-j*pi*7.5/180)], K(k), 48e3,1000, 250, 1);
    if (maximum >= 1.00000)
        K_found = K(k);
        k = 10001;
    end
    k = k+1;
end