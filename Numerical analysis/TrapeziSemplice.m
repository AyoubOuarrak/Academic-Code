function res = TrapeziSemplice(a,b,f)
% a,b : estremi di integrazione
% f : funzione integranda

x = a;
y1 = eval(f);
x = b;
y2 = eval(f);

res = 0.5*(b-a)*(y1 + y2);

end