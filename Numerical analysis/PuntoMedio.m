function res = PuntoMedio(a,b,f)
% Implementazione della Formula di Newton-Cotes aperta del "Punto Medio"

    x = (a+b)/2;
    % Unico punto della formula del punto medio
    
    y = eval(f);
    % Valutazione della f nel punto x
    
    res = (b-a)*y;
    % Applicazione della formula

end