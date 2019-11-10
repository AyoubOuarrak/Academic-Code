function [alfa,i] = Newton(x,f,f1,toll,Nmax)
% FUNZIONE alfa = Newton(x,f,f1,toll,iter)
% x: punto di partenza del metodo
% f: funzione di cui voglio conoscere una radice
% f1: derivata prima di f
% toll: tolleranza della soluzione
% Nmax: numero massimo di iterazioni

    for i = 1 : Nmax
        while abs(eval(f)) > toll
            x = x - eval(f)/eval(f1);
        end
    end
    
    alfa = x;

end

