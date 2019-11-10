function x = SolveUpper(A, b)
% x = SolveUpper(A, b)
% Solutore di sistemi Ax = b
% A: matrice quadrata triangolare superiore
% b : vettore dei termini noti
% x : vettore soluzione risultante

    n = length(A);
    x(n) = b(n)/A(n,n);
    
    for i = n-1 : -1 : 1
        temp = 0;

        for k = n : -1 : i+1
            temp = temp + A(i,k)*x(k);
        end

        x(i) = (b(i) - temp)/A(i,i);
    end

end

