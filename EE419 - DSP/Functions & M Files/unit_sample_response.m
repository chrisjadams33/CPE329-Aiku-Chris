% This function takes 4 inputs: the Bk and Ak coefficients for a 
% difference equation, number_of_samples, and figure #. 
% The function returns the unit sample response.
function [hn, n] = unit_sample_response(Bk, Ak, number_of_samples, figure_number)

    [dn, n] = unit_sample(number_of_samples); %get arrays of sample index
    hn = filter(Bk, Ak, dn); %filter the Z domain tf to the time domain
    
    figure(figure_number)
    
    %make stem plot of unit sample response
    stem(n, hn, '.', 'MarkerSize', 20, 'Linewidth', 2);
    xlabel('Sample index')
    ylabel('Unit Sample Response')
    title('Unit Sample Response') 
    
end
