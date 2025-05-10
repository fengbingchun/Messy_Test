/* sorting.mod - how to sort arrays in MathProg */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

#  Sometimes it is necessary to print parameters or variables in the
#  order of ascending or descending their values. Suppose, for example,
#  that we have the following subscripted parameter:

set I := 1..12;

param a{i in I} := Uniform(2, 7);

#  If we print all its members:

printf{i in I} "a[%d] = %g\n", i, a[i];

#  the output may look like follows:
#
#  a[1]  = 2.64156
#  a[2]  = 2.04798
#  a[3]  = 2.14843
#  a[4]  = 4.76896
#  a[5]  = 6.09132
#  a[6]  = 3.27780
#  a[7]  = 4.06113
#  a[8]  = 4.05898
#  a[9]  = 6.63120
#  a[10] = 6.50318
#  a[11] = 3.46065
#  a[12] = 4.69845
#
#  However, we would like the parameter members to appear in the order
#  of ascending their values.
#
#  Introduce the following auxiliary parameter:

param pos{i in I} :=
      1 + card({j in I: a[j] < a[i] or a[j] = a[i] and j < i});

#  where pos[i] = k means that in the sorted list member a[i] would
#  have k-th position, 1 <= k <= |I|. Then introduce another auxiliary
#  parameter:

param ind{k in 1..card(I)} := sum{i in I: pos[i] = k} i;

#  where ind[k] = i iff pos[k] = i.
#
#  Now, the following statement:

printf{k in 1..card(I)} "a[%d] = %g\n", ind[k], a[ind[k]];

#  prints the parameter members in the desired order:
#
#  a[2]  = 2.04798
#  a[3]  = 2.14843
#  a[1]  = 2.64156
#  a[6]  = 3.27780
#  a[11] = 3.46065
#  a[8]  = 4.05898
#  a[7]  = 4.06113
#  a[12] = 4.69845
#  a[4]  = 4.76896
#  a[5]  = 6.09132
#  a[10] = 6.50318
#  a[9]  = 6.63120

end;
