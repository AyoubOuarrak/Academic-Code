function [L, U] = LUfactorization(A)
% LUfactorization(A)
% A: matrice da fattorizzare con il metodo LU non singolare con tutti i
% suoi minori principali non singolari
% L: matrice triangolare inferiore risultante con termini unitari sulla
% diagonale principale
% U: matrice triangolare superiore risultante

    n = max(size(A));
    L = diag(ones(1,n));
    U = zeros(n,n);
    
    for k = 1 : n % Passo
        for j = k : n % Costruisco le righe di U
            temp = 0;
            for p = 1 : k-1
                temp = temp + L(k,p)*U(p,j);
            end
            U(k,j) = A(k,j) - temp;
        end
        
        for i = k+1 : n % Costruisco le colonne di L
            res = 0;
            for p = 1 : k-1
                res = res + L(i,p)*U(p,k);
            end
            L(i,k) = (A(i,k) - res)/U(k,k);
        end
        
    end

end

