/* Power plant LP scheduler, example data with 25hrs for daylightsavings */

/* Implemented, inspected, written and converted to GNU MathProg
   by NASZVADI, Peter, 199x-2017 <vuk@cs.elte.hu> */

/*
   Fast electric power plant scheduler implementation based on new
   results in author's Thesis.

   The base problem is:
   * given some power plants
   * a short time scale partitioned to equidistant intervals
   * the task is to yielding the cheapest schedule for the plants
   * the daily demand forecast is usually accurate and part of the input

   The power plants has technical limitations:
   * upper and lower bounds of produced energy
   * and also a gradient barrier in both directions
     (can depend on time, but this GMPL implementation is simplified)
   * Also units with same properties (technical and price) should be
     scheduled together usually with near same performance values
   * Assumed a simplified network topology, which is contractive, so
     keeping Kirchhoff's laws is a necessary constraint too
   * All solutions must be integer

   The LP relaxation is equivalent with the MIP problem due to the
   model's matrix interesting property: it is Totally Unimodular
   (proven in 2004 by author) and also a Network Matrix (2006,
   presented at OTDK 2016, Szeged, Hungary) so:
   * it is strictly polynomial if it is solved by most simplex algs
   * all base solutions become integer if the RHS vector is integer
     (it is in real life, so this is an acceptable assumption)
   * The transposed matrix is NOT a Network Matrix in most cases!

   However, adding several other constraints easily turns the problem
   to be NP-hard, which is also pinpointed and discussed in the Thesis.

   See more about electric power plants' scheduling in the
   author's Thesis (in Hungarian):
   http://www.cs.elte.hu/matdiploma/vuk.pdf

   It is possible to run with custom parameters, what is needed
   to define is:
   * TIME set (daylightsaving cases or other than hour intervals)
   * PLANTS set (the 'Demand' is mandatory and usually negative)
   * PRICE parameter (can be negative if energy is sold to a consumer)
   * BOUND parameter (technical bounds)
   * MAXGRAD parameter (technical bounds)

   Then generate a pretty-printed solution by typing:
   glpsol --math powpl25h.mod
*/

set TIME, default {
    '00:00', '01:00', '02:00', '03:00', '04:00',
    '05:00', '06:00', '07:00', '08:00', '09:00',
    '10:00', '11:00', '12:00', '13:00', '14:00',
    '15:00', '16:00', '17:00', '18:00', '19:00',
    '20:00', '21:00', '22:00', '23:00', '24:00'
};
/* Time labels, assumed natural ordering. daylightsaving's bias
   can be inserted p.ex. in Central Europe like:
   ... '01:00', '02:00', '02:00b', '03:00', ... */

set TADJ := setof{(r, s) in TIME cross TIME: r < s}(r, s) diff
    setof{(t, u, v) in TIME cross TIME cross TIME: t < u and u < v}(t, v);
/* Tricky adjacent time label generator because GMPL lacks order determination
   of set elements (except intervals composed of equidistant numbers) */

set PLANTS, default {'Demand'};
/* Demand is a promoted, mandatory one, usually filled
   with negative MW values in data section */

set DIRECTION, default {'Up', 'Down'};
/* All possible directions of gradients, do not touch */

param MAXINT, default 10000;
/* A "macro" for bounding absolute value of all used numbers
   and used as default value */

param PRICE{PLANTS}, default MAXINT;
/* Should be specified in data section, self-explanatory.
   can be negative if there are energy buyers */

param BOUND{(p, t, d) in PLANTS cross TIME cross DIRECTION},
    default if t = '00:00' then if d = 'Down' then BOUND[p, t, 'Up'] else 0 else
        if p <> 'Demand' or d = 'Up' then sum{(u, v) in TADJ: v = t} BOUND[p, u, d]
        else BOUND[p, t, 'Up'];
/* Obvious, technical bounds of each power plant unit (real or virtual like
   'Demand'). If some parts are not given in data section, calculated
   from preceeding values. Also for time '00:00', its 'Down' values by
   default are the same as denoted with 'Up' */

param MAXGRAD{(p, d) in PLANTS cross DIRECTION}, default MAXINT;
/* Usually nonnegative integer, might differ in distinct directions per unit
   in the cited thesis, it is allowed to gradient bounds to depend on time,
   but this is a simplified model */

var x{(t, p) in TIME cross PLANTS}, <= BOUND[p, t, 'Up'], >= BOUND[p, t, 'Down'];
/* The schedule, dimension is MW */

s.t. kirchhoff{t in TIME: t <> '00:00'}: sum{p in PLANTS} x[t, p] = 0;
/* Conservative property */

s.t. gradient{(p, t, u) in PLANTS cross TADJ}:
    -MAXGRAD[p, 'Down'] <= x[t, p] - x[u, p] <= MAXGRAD[p, 'Up'];
/* Technical limitations, each unit usually cannot change performance
   arbitrarily in a short time, so limited in both directions per time unit*/

minimize obj: sum{(t, p) in TIME cross PLANTS}(x[t, p] * PRICE[p]);
/* The objective is the cost of the schedule */

solve;

/* Pretty print solution in table */

printf '+--------+';
for{p in PLANTS}{
       printf '-% 6s-+', '------';
}
printf '\n';
printf '|%7s |', ' ';
for{p in PLANTS}{
       printf ' % 6s |', p;
}
printf '\n';
printf '+--------+';
for{p in PLANTS}{
       printf '-% 6s-+', '------';
}
printf '\n';
for{t in TIME}{
    printf '|%7s |', t;
    for{p in PLANTS}{
        printf ' % 6s |', x[t, p].val;
    }
    printf '\n';
}
printf '+--------+';
for{p in PLANTS}{
       printf '-% 6s-+', '------';
}
printf '\n';

data;

set TIME :=
    '00:00', '01:00', '02:00', '02:00b', '03:00', '04:00',
    '05:00', '06:00', '07:00', '08:00', '09:00',
    '10:00', '11:00', '12:00', '13:00', '14:00',
    '15:00', '16:00', '17:00', '18:00', '19:00',
    '20:00', '21:00', '22:00', '23:00', '24:00';

/*
   Generated random default values and names, the demand is the sum of
   2 sinewaves.
   Also specified a treshold for nuclear plants from 15:00 till 19:00
   The sun is shining only morning and in the afternoon: 07:00-18:00, so
   solar plant cannot produce electric energy after sunset.

   Only touch this section, or export it to a data file!
*/

set PLANTS 'Demand', 'Atom1', 'Atom2', 'Coal', 'Gas1', 'Gas2', 'Green', 'Oil', 'Solar', 'Dam';

param PRICE :=
    'Demand'   0
    'Atom1'    2
    'Atom2'    2
    'Coal'  15.6
    'Gas1'    12
    'Gas2'  11.5
    'Green'  8.8
    'Oil'   23.3
    'Solar'  7.6
    'Dam'      3;
/* price per MW */

param BOUND :=
    [*, *, 'Up']   (tr): 'Atom1' 'Atom2' 'Coal' 'Gas1' 'Gas2' 'Green' 'Oil' 'Solar' 'Dam' :=
        '00:00'             240     240    100    150    150      20    90       0    20
        '01:00'             240     240    155    192    208      35   230       0    20
    [*, *, 'Up']   (tr): 'Atom1' 'Atom2' :=
        '15:00'             200     200
        '19:00'             235     235
    [*, *, 'Up']   (tr): 'Solar' :=
        '07:00'              20
        '18:00'               0
    [*, *, 'Down'] (tr): 'Atom1' 'Atom2' 'Coal' 'Gas1' 'Gas2' 'Green' 'Oil' 'Solar' 'Dam' :=
        '01:00'             100     100     50     62     68       0    75       0    20
    [*, *, 'Up'] : '01:00' '02:00' '02:00b' '03:00' '04:00' '05:00' '06:00' '07:00' '08:00' :=
        'Demand'     -868    -851    -842    -837    -791    -887    -912   -1046   -1155
    [*, *, 'Up'] : '09:00' '10:00' '11:00' '12:00' '13:00' '14:00' '15:00' '16:00' :=
        'Demand'     -945    -873    -797    -990   -1241   -1134    -815    -782
    [*, *, 'Up'] : '17:00' '18:00' '19:00' '20:00' '21:00' '22:00' '23:00' '24:00' :=
        'Demand'     -772    -827    -931   -1105   -1215   -1249   -1183    -952;

param MAXGRAD (tr)
    :      'Atom1' 'Atom2' 'Coal' 'Gas1' 'Gas2' 'Green' 'Oil' 'Solar' 'Dam' :=
    'Up'       30      30     35     89     95       5    56       2     4
    'Down'     30      30     45     96    102       5    56       2     4;

end;
