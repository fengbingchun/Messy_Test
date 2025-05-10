/* ZEBRA, Who Owns the Zebra? */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

########################################################################
#  The Zebra Puzzle is a well-known logic puzzle.
#
#  It is often called "Einstein's Puzzle" or "Einstein's Riddle"
#  because it is said to have been invented by Albert Einstein as a boy,
#  with the common claim that Einstein said "only 2 percent of the
#  world's population can solve". It is also sometimes attributed to
#  Lewis Carroll. However, there is no known evidence for Einstein's or
#  Carroll's authorship.
#
#  There are several versions of this puzzle. The version below is
#  quoted from the first known publication in Life International
#  magazine on December 17, 1962.
#
#   1. There are five houses.
#   2. The Englishman lives in the red house.
#   3. The Spaniard owns the dog.
#   4. Coffee is drunk in the green house.
#   5. The Ukrainian drinks tea.
#   6. The green house is immediately to the right of the ivory house.
#   7. The Old Gold smoker owns snails.
#   8. Kools are smoked in the yellow house.
#   9. Milk is drunk in the middle house.
#  10. The Norwegian lives in the first house.
#  11. The man who smokes Chesterfields lives in the house next to the
#      man with the fox.
#  12. Kools are smoked in the house next to the house where the horse
#      is kept.
#  13. The Lucky Strike smoker drinks orange juice.
#  14. The Japanese smokes Parliaments.
#  15. The Norwegian lives next to the blue house.
#
#  Now, who drinks water? Who owns the zebra?
#
#  In the interest of clarity, it must be added that each of the five
#  houses is painted a different color, and their inhabitants are of
#  different national extractions, own different pets, drink different
#  beverages and smoke different brands of American cigarettes. One
#  other thing: In statement 6, right means your right.
#
#  (From Wikipedia, the free encyclopedia.)
########################################################################

set HOUSE := { 1..5 };

set COLOR := { "blue", "green", "ivory", "red", "yellow" };

set NATIONALITY := { "Englishman", "Japanese", "Norwegian", "Spaniard",
      "Ukranian" };

set DRINK := { "coffee", "milk", "orange_juice", "tea", "water" };

set SMOKE := { "Chesterfield", "Kools", "Lucky_Strike", "Old_Gold",
      "Parliament" };

set PET := { "dog", "fox", "horse", "snails", "zebra" };

var color{HOUSE, COLOR}, binary;
c1{h in HOUSE}: sum{c in COLOR} color[h,c] = 1;
c2{c in COLOR}: sum{h in HOUSE} color[h,c] = 1;

var nationality{HOUSE, NATIONALITY}, binary;
n1{h in HOUSE}: sum{n in NATIONALITY} nationality[h,n] = 1;
n2{n in NATIONALITY}: sum{h in HOUSE} nationality[h,n] = 1;

var drink{HOUSE, DRINK}, binary;
d1{h in HOUSE}: sum{d in DRINK} drink[h,d] = 1;
d2{d in DRINK}: sum{h in HOUSE} drink[h,d] = 1;

var smoke{HOUSE, SMOKE}, binary;
s1{h in HOUSE}: sum{s in SMOKE} smoke[h,s] = 1;
s2{s in SMOKE}: sum{h in HOUSE} smoke[h,s] = 1;

var pet{HOUSE, PET}, binary;
p1{h in HOUSE}: sum{p in PET} pet[h,p] = 1;
p2{p in PET}: sum{h in HOUSE} pet[h,p] = 1;

/* the Englishman lives in the red house */
f2{h in HOUSE}: nationality[h,"Englishman"] = color[h,"red"];

/* the Spaniard owns the dog */
f3{h in HOUSE}: nationality[h,"Spaniard"] = pet[h,"dog"];

/* coffee is drunk in the green house */
f4{h in HOUSE}: drink[h,"coffee"] = color[h,"green"];

/* the Ukrainian drinks tea */
f5{h in HOUSE}: nationality[h,"Ukranian"] = drink[h,"tea"];

/* the green house is immediately to the right of the ivory house */
f6{h in HOUSE}:
   color[h,"green"] = if h = 1 then 0 else color[h-1,"ivory"];

/* the Old Gold smoker owns snails */
f7{h in HOUSE}: smoke[h,"Old_Gold"] = pet[h,"snails"];

/* Kools are smoked in the yellow house */
f8{h in HOUSE}: smoke[h,"Kools"] = color[h,"yellow"];

/* milk is drunk in the middle house */
f9: drink[3,"milk"] = 1;

/* the Norwegian lives in the first house */
f10: nationality[1,"Norwegian"] = 1;

/* the man who smokes Chesterfields lives in the house next to the man
   with the fox */
f11{h in HOUSE}:
   (1 - smoke[h,"Chesterfield"]) +
   (if h = 1 then 0 else pet[h-1,"fox"]) +
   (if h = 5 then 0 else pet[h+1,"fox"]) >= 1;

/* Kools are smoked in the house next to the house where the horse is
   kept */
f12{h in HOUSE}:
   (1 - smoke[h,"Kools"]) +
   (if h = 1 then 0 else pet[h-1,"horse"]) +
   (if h = 5 then 0 else pet[h+1,"horse"]) >= 1;

/* the Lucky Strike smoker drinks orange juice */
f13{h in HOUSE}: smoke[h,"Lucky_Strike"] = drink[h,"orange_juice"];

/* the Japanese smokes Parliaments */
f14{h in HOUSE}: nationality[h,"Japanese"] = smoke[h,"Parliament"];

/* the Norwegian lives next to the blue house */
f15{h in HOUSE}:
   (1 - nationality[h,"Norwegian"]) +
   (if h = 1 then 0 else color[h-1,"blue"]) +
   (if h = 5 then 0 else color[h+1,"blue"]) >= 1;

solve;

printf "\n";
printf "HOUSE  COLOR   NATIONALITY  DRINK         SMOKE         PET\n";
for {h in HOUSE}
{  printf "%5d", h;
   printf{c in COLOR: color[h,c]} "  %-6s", c;
   printf{n in NATIONALITY: nationality[h,n]} "  %-11s", n;
   printf{d in DRINK: drink[h,d]} "  %-12s", d;
   printf{s in SMOKE: smoke[h,s]} "  %-12s", s;
   printf{p in PET: pet[h,p]} "  %-6s", p;
   printf "\n";
}
printf "\n";

end;
