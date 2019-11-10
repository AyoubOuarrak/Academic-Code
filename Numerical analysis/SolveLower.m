function x = SolveLower( A, b )
% Risolutore di un sistema Ax = b
% A: matrice triangolare inferiore
% b: vettore dei termini noti
% x: vettore soluzione risultante

    x(1) = b(1)/A(1,1);
    
    for i = 2 : length(A)
    % Per ciascuna riga calcolo la x i-iesima soluzione
        temp = 0;
        
        for k = 1 : i-1
            temp = temp + A(i,k)*x(k);
        end

        x(i) = (b(i) - temp)/A(i,i);
    end

end

