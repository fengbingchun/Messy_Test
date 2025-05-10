/* A solver for the Japanese number-puzzle Shikaku
 * http://en.wikipedia.org/wiki/Shikaku
 *
 * Sebastian Nowozin <nowozin@gmail.com>, 27th January 2009
 */

param ndim := 10;
set rows := 1..ndim;
set rows1 := 1..(ndim+1);
set cols := 1..ndim;
set cols1 := 1..(ndim+1);
param givens{rows, cols}, integer, >= 0, default 0;

/* Set of vertices as (row,col) coordinates */
set V := { (i,j) in { rows, cols }: givens[i,j] != 0 };

/* Set of all feasible boxes of the right size: only this boxes are possible.
 * The box contains (i,j) and ranges from (k,l) to (m,n)
 */
set B := { (i,j,k,l,m,n) in { V, rows, cols, rows1, cols1 }:
    i >= k and i < m and j >= l and j < n and   /* Contains (i,j) */
    ((m-k)*(n-l)) = givens[i,j] and /* Right size */
    card({ (s,t) in V: s >= k and s < m and t >= l and t < n }) = 1
        /* Contains only (i,j), no other number */
};

var x{B}, binary;

/* Cover each square exactly once */
s.t. cover_once{ (s,t) in { rows, cols } }:
    sum{(i,j,k,l,m,n) in B: s >= k and s < m and t >= l and t < n}
        x[i,j,k,l,m,n] = 1;

minimize cost: 0;

solve;

/* Output solution graphically */
printf "\nSolution:\n";
for { row in rows1 } {
    for { col in cols1 } {
        printf{0..0: card({(i,j,k,l,m,n) in B:
                col >= l and col <= n and (row = k or row = m) and
                x[i,j,k,l,m,n] = 1}) > 0 and
            card({(i,j,k,l,m,n) in B:
                row >= k and row <= m and (col = l or col = n) and
                x[i,j,k,l,m,n] = 1}) > 0} "+";
        printf{0..0: card({(i,j,k,l,m,n) in B:
                col >= l and col <= n and (row = k or row = m) and
                x[i,j,k,l,m,n] = 1}) = 0 and
            card({(i,j,k,l,m,n) in B:
                row >= k and row <= m and (col = l or col = n) and
                x[i,j,k,l,m,n] = 1}) > 0} "|";
        printf{0..0: card({(i,j,k,l,m,n) in B:
                row >= k and row <= m and (col = l or col = n) and
                x[i,j,k,l,m,n] = 1}) = 0 and
            card({(i,j,k,l,m,n) in B:
                col >= l and col <= n and (row = k or row = m) and
                x[i,j,k,l,m,n] = 1}) > 0} "-";
        printf{0..0: card({(i,j,k,l,m,n) in B:
                row >= k and row <= m and (col = l or col = n) and
                x[i,j,k,l,m,n] = 1}) = 0 and
            card({(i,j,k,l,m,n) in B:
                col >= l and col <= n and (row = k or row = m) and
                x[i,j,k,l,m,n] = 1}) = 0} " ";

        printf{0..0: card({(i,j,k,l,m,n) in B:
            col >= l and col < n and (row = k or row = m) and
            x[i,j,k,l,m,n] = 1}) > 0} "---";
        printf{0..0: card({(i,j,k,l,m,n) in B:
            col >= l and col < n and (row = k or row = m) and
            x[i,j,k,l,m,n] = 1}) = 0} "   ";
    }
    printf "\n";

    for { (col,p) in { cols, 1 }: card({ s in rows: s = row }) = 1 } {
        printf{0..0: card({(i,j,k,l,m,n) in B:
            row >= k and row < m and (col = l or col = n) and
            x[i,j,k,l,m,n] = 1}) > 0} "|";
        printf{0..0: card({(i,j,k,l,m,n) in B:
            row >= k and row < m and (col = l or col = n) and
            x[i,j,k,l,m,n] = 1}) = 0} " ";
        printf{0..0: card({ (i,j) in V: i = row and j = col}) > 0} " %2d", givens[row,col];
        printf{0..0: card({ (i,j) in V: i = row and j = col}) = 0} "  .";
    }
    printf{0..0: card({ r in rows: r = row }) = 1} "|\n";
}

data;

/* This Shikaku is from
 * http://www.emn.fr/x-info/sdemasse/gccat/KShikaku.html#uid5449
 */
param givens : 1 2 3 4 5 6 7 8 9 10 :=
           1   9 . . . 12 . . 5 . .
           2   . . . . . . . . . .
           3   . . . . . . . . . 6
           4   8 . 6 . 8 . . . . .
           5   . . . . . . . . . .
           6   . . . . . . . . . .
           7   . . . . . 6 . 8 . 12
           8   4 . . . . . . . . .
           9   . . . . . . . . . .
          10   . . 3 . . 9 . . . 4
           ;

end;
