function [L,A] = NewLU(A)
% GaussFactorization(A)
% A : matrice da ridurre a gradini con l'algoritmo di Gauss

n = length(A);
L = zeros(n) - diag(ones(1,n));

for k = 1 : n-1 % Passo
     for i = k+1 : n % Per ogni riga
        L(i,k) = -A(i,k)/A(k,k);
        A(i,:) = L(i,k)*A(k,:) + A(i,:);
     end
end

L = -1*L;

end