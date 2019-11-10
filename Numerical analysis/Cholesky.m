function [L] = Cholesky(A)
% Fattorizzazione di Cholesky
% A : matrice da fattorizzare simmetrica definita positiva

n = max(size(A));
% Dimensione della matrice A

L = zeros(n,n);
% Definisco la matrice L

for i = 1 : n-1 % passo
    
    temp = 0;
    for p = 1 : i-1
        temp = temp + L(i,p)^2;
    end
    L(i,i) = sqrt(A(i,i) - temp);
    % Calcolo gli elementi diagonali di L
    
    temp = 0;
    for p = 1 : i-1
        temp = temp + L(i,p)*L(i+1,p);
    end
    for k = i+1 : n
        L(k,i) = (A(i,k) - temp)/L(i,i);
    end
    % Calcolo gli altri elementi di A per righe
end

temp = 0;
for p = 1 : n
    temp = temp + L(n,p)^2;
end
L(n,n) = sqrt(A(n,n) - temp);
% Calcolo l'ultimo elemento diagonale

end

