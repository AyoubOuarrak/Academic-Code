% FATTORIZZAZIONE DI MATRICI TRIDIAGONALI
function [L,U] = SolveTridiag(A)
% Calcolo della fattorizzazione LU per matrice tridiagonale

    a = diag(A,-1)';
    c = diag(A,1)';
    % Vettori contenenti le tre diagonali di A
    
    n = max(size(A));
    % Dimensione della matrice
    
    d(1) = 1;
    for k = 1 : n
        d(k+1) = det(A(1:k,1:k));
        if(d(k+1) == 0)
            fprintf('Un minore ha determinante nullo!\n')
            return
        end
    end
    % Calcolo i determinanti di tutti i minori pricipali di A
    
    L = diag(ones(1,n));
    U = zeros(n,n);
    % Inizio a costruire la matrice L e la matrice U
    
    for k = 2 : n
        L(k,k-1) = a(k-1)*(d(k-1)/d(k));
    end
    % Costruisco la matrice L
    
    for k = 2 : n
        U(k-1,k) = c(k-1);
    end
    
    for k = 1 : n
        U(k,k) = d(k+1)/d(k);
    end    
    % Costruisco la matrice U
    
end