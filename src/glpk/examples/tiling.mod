/* Rectifiable polyomino tilings generator */

/* Written and converted to GNU MathProg by NASZVADI, Peter, 2007-2017
   <vuk@cs.elte.hu> */

/*
   This model searches for a maximal packing of a given polyomino
   composed of unit squares in a given rectangle. In a feasible packing, a
   placed polyomino and its intersection of a unit square's inner part in
   the rectangle must be the square or empty. If there exists a packing
   that covers totally the rectangle, then the polyomino is called
   "rectifiable"

   Summary:
   Decides if an Im * Jm rectangle could be tiled with given pattern
   and prints a (sub)optimal solution if found

   Generated magic numbers are implicit tables, check them:

   # for magic in 3248 688 1660 3260
     do printf "Magic % 5d:" "$magic"
         for e in 0 1 2 3 4 5 6 7
         do printf "% 3d" "$((-1 + ((magic / (3**e)) % 3)))"
         done
         echo
     done
   Magic  3248:  1  1 -1 -1  0  0  0  0
   Magic   688:  0  0  0  0  1  1 -1 -1
   Magic  1660:  0  0  0  0  1 -1  1 -1
   Magic  3260:  1 -1  1 -1  0  0  0  0
   #
*/

param Im, default 3;
/* vertical edge length of the box */

param Jm, default 3;
/* horizontal edge length of the box */

set S, default {(0, 0), (1, 0), (2, 0), (0, 1), (1, 1), (2, 1), (0, 2)};
/* P-heptomino is the default shape. More info on this heptomino:
   http://www.cflmath.com/Polyomino/7omino4_rect.html */

set I := 1..Im;
/* rows of rectangle */

set J := 1..Jm;
/* columns of rectangle */

set IJ := I cross J;
/* the rectangle itself */

set E := 0..7;
/* helper set to allow iterating on all transformations of the S shape */

set Shifts := setof{(i, j, e) in IJ cross E:
         setof{(x, y) in S}
             ((x * (-1 + floor(3248 / 3^e) mod 3)) +
              (y * (-1 + floor(688 / 3^e) mod 3)) + i,
              (x * (-1 + floor(1660 / 3^e) mod 3)) +
              (y * (-1 + floor(3260 / 3^e) mod 3)) + j) within IJ}(i, j, e);
/* all shifted, flipped, rotated, mirrored mappings of polyomino that
   contained by the rectangle */

var cell{IJ}, binary;
/* booleans denoting if a cell is covered in the rectangle */

var tile{Shifts}, binary;
/* booleans denoting usage of a shift */

var objvalue;

s.t. covers{(i, j) in IJ}: sum{(k, l, e, a, b) in Shifts cross S:
    i = k + a * (-1 + floor(3248 / 3^e) mod 3) +
        b * (-1 + floor(688 / 3^e) mod 3)
    and
    j = l + a * (-1 + floor(1660 / 3^e) mod 3) +
        b * (-1 + floor(3260 / 3^e) mod 3)
    }tile[k, l, e] = cell[i, j];

s.t. objeval: sum{(i, j) in IJ}cell[i, j] - objvalue = 0;

maximize obj: objvalue;

solve;

printf '\nCovered cells/all cells = %d/%d\n\n', objvalue.val, Im * Jm;
printf '\nA tiling:\n\n';
for{i in I}{
    for{j in J}{
        printf '%s', if cell[i, j].val then '' else ' *** ';
        for{(k, l, e, a, b) in Shifts cross S:
            cell[i, j].val
            and i = k + a * (-1 + floor(3248 / 3^e) mod 3) +
                b * (-1 + floor(688 / 3^e) mod 3)
            and j = l + a * (-1 + floor(1660 / 3^e) mod 3) +
                b * (-1 + floor(3260 / 3^e) mod 3)
            and tile[k, l, e].val
        }{
            printf '% 5d', (k * Jm + l) * 8 + e;
        }
    }
    printf '\n';
}
printf '\n';

data;

param Im := 14;
/* here can be set rectangle's one side */

param Jm := 14;
/* here can be set rectangle's other side */

set S := (0,0),(1,0),(2,0),(0,1),(1,1),(2,1),(0,2);
/* here you can specify arbitrary polyomino */

end;
