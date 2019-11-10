function t = simpson(a,b,N,f)
% METODO DI CAVALIERI SIMPSON
% a,b: intervallo di integrazione
% N: numero di punti (dispari)
% f: funzione integranda

    if N == fix(N/2)*2
    % Controllo che il numero di punti sia effettivamente dispari
        return
    end

    H = (b-a)/(N-1);

    x = a : H : b;
    if(max(size(x)) ~= N)
        x(N) = b;
    end

    y = eval(f);

    t = 4*sum(y(2:2:N));
    t = t + 2*sum(y(3:2:N-1));
    t = H*(t + y(1) + y(N))/3;
    return

end
