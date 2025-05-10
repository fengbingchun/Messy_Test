/* Problem posed by rsymbx

1) Given a large box which contains bags of marbles.
2) Inside each bag, there are multiple marbles.

Objective:
Choose the fixed size set of bags with the maximum number of
colors.
*/

set Bags   := {1..100};
set Colors := {1..1000};

# To keep things easy let us create random bags.
param ncol{b in Bags} := 5 + 30 * Uniform(0,1);
set Bag{b in Bags} :=
  setof{ c in Colors : Uniform(0,1) < ncol[b]/card(Colors) } c;

# Do a little analytics
set allCol := setof{ b in Bags, c in Bag[b]} c;
printf "The smallest bag contains %d marbles\n", min{b in Bags} card(Bag[b]);
printf "The largest bag contains %d marbles\n", max{b in Bags} card(Bag[b]);
printf "%d colors are used\n", card(allCol);

# Bag b is chosen
var x{b in Bags}, binary;
# Color c is in a chosen bag
var y{c in Colors}, >=0, <=1;

# objective
maximize obj :
  sum{c in Colors} y[c];

# maximum of 10 bags
s.t. nBags :
  sum{b in Bags} x[b] <= 10;
# count only colors that are in a chosen bag
s.t. fCol{c in Colors} :
  y[c] <= sum{b in Bags : c in Bag[b]} x[b];

solve;

printf "Bags chosen:\n";
for {b in Bags : x[b] > .5} {
  printf "bag %d", b;
  printf "%s", if b < max{i in Bags : x[i] > .5} i then ', ' else '.';
}
printf "\n";
printf "Colors retrieved: %d\n", obj;

end;
