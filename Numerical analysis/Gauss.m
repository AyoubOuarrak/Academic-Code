function [C, d] = Gauss(A, b)
% Gauss(A, b)
% A: Matrice quadrata a cui applicare l'algoritmo di Gauss
% b: Vettore dei termini noti
    
    n = max(size(A));
    
    for k = 1 : n-1 % Indice di passo
        for i = k+1 : n % Indice di riga
            m = -A(i,k)/A(k,k);
            for j = k : n % Indice di colonna
                A(i,j) = A(k,j)*m + A(i,j);
            end
            b(i) = b(k)*m + b(i);
        end
    end
    
    C = A;
    d = b;
    
end

