function medio = Dicotomico(a,b,f,toll)
% METODO DI RICERCA DI RADICI DICOTOMICO
% a,b : intervallo di partenza tale che f(a)*f(b) < 0
% f : funzione di cui si vuole calcolare una radice
% toll : tolleranza assegnata

x = a;
res_a = eval(f);
x = b;
res_b = eval(f);

if res_a*res_b >= 0 % Controllo sull'input
    fprintf('Gli estremi di partenza devono avere segni opposti!\n')
    return
end

Nmax = ceil(log(b-a)/toll);
% Calcolo le iterazioni da effettuare per avere precisione con quella
% determinata tolleranza assegnata sulla radice

for k = 1 : Nmax
    x = (a + b)/2;
    medio = x;
    res_medio = eval(f);
    % Punto medio
    
    x = a;
    res_a = eval(f);
    
    x = b;
    res_b = eval(f);
    
    if res_medio*res_a < 0
        b = medio;
    elseif medio*res_b < 0
        a = medio;
    end
    % Scelta del prossimo intervallo
    
end