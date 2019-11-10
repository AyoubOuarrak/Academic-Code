function A = GaussFactorization(A,b)
% GaussFactorization(A)
% A : matrice da ridurre a gradini con l'algoritmo di Gauss

n = max(size(A));

for k = 1 : n-1 % Passo
     for i = k+1 : n % Per ogni riga
        m = -A(i,k)/A(k,k);
        A(i,:) = m*A(k,:) + A(i,:);
        b(i) = b(i) + m*b(k);
     end
end

end