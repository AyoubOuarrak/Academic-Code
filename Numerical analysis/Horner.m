function val = Horner(coeff, x)
% ALGORITMO DI HORNER
% coeff: vettore dei coefficienti del polinomio da valutare
% x: punto in cui deve essere valutato il polinomio p(x)

    val = coeff(1);
    for k = 2 : length(coeff)
        val = val*x + coeff(k);
    end
    
end

