function t = trapezi(a,b,N,f)
% Calcolo di Integrale definito con la formula dei trapezi composita
% a,b Intervallo di integrazione
% N Numero di punti

    H = (b-a)/(N-1);
    % Passo degli intervalli di integrazione

    x = a : H : b;
    % Punti equispaziati su cui applicare Trapezi con passo h

    if( max(size(x)) ~= N )
        x(N) = b;
    end

    y = eval(f);
    % Valuto la funzione f

    t = 2*sum(y(2:N-1));
    t = 0.5*H*(t + y(1) + y(N));

    return

end