/* cal.mod - print an ASCII calendar of the given year */

/* Written in GNU MathProg by Andrew Makhorin <mao@gnu.org> */

param year, integer, >= 0001, <= 3999, default 2010;

param first_day{m in 1..12}, integer, >= 0, <= 6, :=
      time2str(str2time(year & "-" & m & "-01", "%Y-%m-%d"), "%w");

param days_in_month{m in 1..12}, integer, >= 28, <= 31, :=
      (str2time(year + (if m < 12 then 0 else 1) & "-" &
         (if m < 12 then m+1 else 1) & "-01", "%Y-%m-%d") -
      str2time(year & "-" & m & "-01", "%Y-%m-%d")) / 86400;

param foo{m in 1..12, k in 0..5, d in 0..6}, integer, :=
      7 * k + d + 1 - first_day[m];

param cal{m in 1..12, k in 0..5, d in 0..6}, integer, :=
      if 1 <= foo[m,k,d] and foo[m,k,d] <= days_in_month[m] then
         foo[m,k,d];

printf "\n";
printf "%33s%04d\n", "", year;
printf "\n";
for {t in 1..12 by 3}
{     for {m in t..t+2}
      {  printf "%7s%-14s", "", time2str(str2time(m, "%m"), "%B");
         printf{0..0: m < t+2} "   ";
      }
      printf "\n";
      for {m in t..t+2}
      {  printf "  S  M Tu  W Th  F  S";
         printf{0..0: m < t+2} "   ";
      }
      printf "\n";
      for {k in 0..5}
      {  for {m in t..t+2}
         {  for {d in 0..6}
            {  printf{0..0: cal[m,k,d]  = 0} "   ";
               printf{0..0: cal[m,k,d] != 0} " %2d", cal[m,k,d];
            }
            printf{0..0: m < t+2} "   ";
         }
         printf "\n";
      }
}
printf "\n";

end;
