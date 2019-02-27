function [y_n, y_q, n] = limit_cycles_unit_sample_response(A_coeff, bits, size)
%this funtion takes in a feedback loop coefficient, # of bits to quantize, 
%and length of response to compute both the full precision output and
%and quantized output based of the difference equation: 
%y[n] = x[n] ? A1y[n-1] 
%the funtion will plot the two on a single plot for comparison

%initialize sequences
x_n = zeros(1,size);
y_n = zeros(1,size);
y_q = zeros(1,size);

x_n(1) = 1;                                 %unit sample
n = 0:size-1;                             %sample integer
A_1 = A_coeff;                              %full precision coefficient
A_q = round(A_coeff*2^bits);                %quantized coefficient


%loop transfer function
for i=1:length(x_n)
    if i == 1                               %first point
        %assume zero initial conditions
        y_n(i) = x_n(i);
        y_q(i) = x_n(i);
    else
        y_n(i) = x_n(i) - A_1*y_n(i-1);     %calc full precision output
        y_q(i) = x_n(i) - round(A_coeff*2^bits*y_n(i-1))/(2^bits);     %calc quantized output
    end
end



%plot both output sequences on same plot
figure

stem(n, y_n)
hold on
stem(n, y_q)
legend_2 = ['Quantized to ', num2str(bits), ' bits'];
legend('Full Precision', legend_2)
grid
title1 = strcat('Limit Cycles in IIR Filter (A1=',num2str(A_coeff), ')');
xlabel('Sample Number')
ylabel('Amplitude')
title(title1)
end
