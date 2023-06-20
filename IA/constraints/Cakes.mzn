var 0..100: b; % number of banana cakes
var 0..100: c; % number of chocolate cakes

% flour
constraint 250*b +200*c <= 4000;
% bananas 
constraint 2*b <= 6;
% sugar 
constraint 75*b + 150*c <= 2000;
% butter
constraint 100*b + 150*c <= 500;
% cocoa
constraint 75*c <= 500;

% maximize our profit
solve maximize 400*b + 450*c;

output [
	"number of banana cakes = ", show(b), "\n",
	"number of chocolate cakes = ", show(c), "\n"
];