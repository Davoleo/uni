int: n = 3;

var 0..n-1: wa;
var 0..n-1: nt;
var 0..n-1: sa;
var 0..n-1: q;
var 0..n-1: nsw;
var 0..n-1: v;

constraint wa != nt;
constraint wa != sa;
constraint nt != sa;
constraint nt != q;
constraint sa != q;
constraint sa != nsw;
constraint sa != w;
constraint q != nsw;
constraint nsw != v;

solve satisfy;

output [
	"WA = ", show(wa), "\n",
	"NT = ", show(nt), "\n",
	"SA = ", show(sa), "\n",
	"Q = ", show(q), "\n",
	"NSW = ", show(nsw), "\n",
	"V = ", show(v), "\n",
];