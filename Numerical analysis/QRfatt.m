function A = QRfatt(A)
% Algoritmo per la fattorizzazione QR
% A: matrice da fattorizzare

n = max(size(A));
% Calcolo la dimensione della matrice A

I = diag(ones(1,n));
% Definisco la matrice identità
k = n;
% k è un valore che mi serve per definire di volta in volta il vettore e ad
% ogni passo. Infatti e ad ogni iterazione è più piccolo di uno.

    for i = 1 : n-1
        e = zeros(k,1);
        % Calcolo il vettore e della iterazione attuale...
        e(1) = 1;
        % ...ponendo il suo primo elemento ad 1

        x = A(i:n,i);
        % Estraggo il vettore x
        s = norm(x,2);
        % Calcolo s: in questa versione dell'algoritmo non ho badato al
        % segno con cui posso prendere s per evitare cancellazione numerica
        u = x + s*e;
        % Calcolo il vettore u

        while max(size(u)) ~= n
            u = [0; u];
        end
        % Se sono ad un passo diverso dal primo aggiuno ad u tanti zeri
        % sopra quanti gliene servono per arrivare ad n
        
        U = I - (2*u*u')/(norm(u,2)^2);
        % Costruisco il riflettore elementale matrice di Householder
        A = U*A;
        % Applico il riflettore ad A

        k = k-1;
        % Diminuisco k per ricalcolare e al passo successivo
        
        clear U u s x
        % Mi libero di variabili inutili per sicurezza, le ricalcolerò
        % all'iterazione successiva
    end

end