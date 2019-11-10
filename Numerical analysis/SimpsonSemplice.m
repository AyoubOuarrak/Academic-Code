function res = SimpsonSemplice(a,b,f)
% a,b : intervallo di integrazione
% f : funzione integranda

h = (b-a)/2;

x = a;
y1 = eval(f);
x = b;
y2 = eval(f);
x = (a+b)/2;
y3 = eval(f);

res = h*(y1 + y2 + 4*y3)/3;

end