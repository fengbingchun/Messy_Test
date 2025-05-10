/*
 * Author: Heinrich Schuchardt <xypron.glpk@gmx.de>
 *
 * This model solves a clustering problem:
 *
 * Out of 50 towns select 3 to be cluster centers and assign the other
 * towns to the clusters such that the sum of the population weighted
 * euclidian distances between towns and centers is minimized.
 *
 * The solution is saved as a scalable vector graphic file with a
 * pseudo-random file name.
 */

# Output file
param fn, symbolic := "00000" & 100000 * Uniform01();
param f, symbolic := "ct" & substr(fn, length(fn) - 4) & ".svg";

# Centers
param nc := 3;
set C := {1 .. nc};

# Towns
param nt := 50;
set T := {1 .. nt};
param xt{T} := Uniform01();
param yt{T} := Uniform01();
param pt{T} := ceil(1000 * Uniform01());

# Image size
param scale := 1000;

# Colors
# saturation [0, 255]
param sat := 192;
param hue{c in C} := 6 * (c - 1) / nc;
param red{c in C} :=
  if hue[c] <= 1 or hue[c] >= 5 then 255
  else (if hue[c] >=2 and hue[c] <= 4 then 255 - sat
  else (if hue[c] <=2 then 255 - sat + sat * (2-hue[c])
  else 255 - sat + sat * (hue[c]-4) ));
param green{c in C} :=
  if hue[c] >= 1 and hue[c] <= 3 then 255
  else (if hue[c] >= 4 then 255 - sat
  else (if hue[c] <=1 then 255 - sat + sat * hue[c]
  else 255 - sat + sat * (4-hue[c]) ));
param blue{c in C} :=
  if hue[c] >= 3 and hue[c] <= 5 then 255
  else (if hue[c] <=2 then 255 - sat
  else (if hue[c] <=3 then 255 - sat + sat * (hue[c]-2)
  else 255 - sat + sat * (6-hue[c]) ));

var x{T};
var y{T,T}, binary;

minimize obj : sum{c in T, t in T} y[c,t] * pt[t]
               * sqrt((xt[c] - xt[t])^2 + (yt[c] - yt[t])^2);

s.t. sumx : sum{c in T} x[c] = nc;
s.t. cxy{c in T, t in T} : y[c,t] <= x[c];
s.t. sumy{t in T} : sum{c in T} y[c,t] = 1;

solve;

for {c in T : x[c] > .5} {
  printf "Center %5.4f %5.4f\n", xt[c], yt[c];
  for {t in T : y[c,t] > .5} {
    printf "  Town %5.4f %5.4f (%5.0f)\n", xt[t], yt[t], pt[t];
  }
}

# Output the solution as scalable vector graphic

# header
printf "<?xml version=""1.0"" standalone=""no""?>\n" > f;
printf "<!DOCTYPE svg PUBLIC ""-//W3C//DTD SVG 1.1//EN"" \n" >> f;
printf """http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd"">\n" >> f;
printf "<svg width=""%d"" height=""%d"" version=""1.0"" \n",
  1.2 * scale, 1.2 * scale >> f;
printf "xmlns=""http://www.w3.org/2000/svg"">\n" >> f;

# background
printf "<rect x=""0"" y=""0"" width=""%d"" height=""%d""" &
       " stroke=""none"" fill=""white""/>\n",
       1.2 * scale, 1.2 * scale>> f;

# border
printf "<rect x=""%d"" y=""%d"" width=""%d"" height=""%d""" &
       " stroke=""black"" stroke-width="".5"" fill=""white""/>\n",
       .1 * scale, .1 * scale, scale, scale >> f;

# circles for towns
for {t in T}
  printf {s in T, c in C : y[s,t] > .5
         && c = floor( .5 + sum{u in T : u <= s} x[u])}
         "<circle cx=""%f"" cy=""%f"" r=""%f"" stroke=""black"" " &
         "stroke-width=""1"" fill=""rgb(%d,%d,%d)""/>\n",
         (.1 + xt[t]) * scale, (.1 + yt[t]) * scale, .001 * sqrt(pt[t]) * scale,
         red[c], green[c] , blue[c] >> f;

# lines from towns to assigned centers
for {t in T, c in T : y[c,t] > .5}
  printf "<line x1=""%f"" y1=""%f"" x2=""%f"" y2=""%f""" &
         " style=""stroke:black;stroke-width:.5""/>\n",
         (.1 + xt[c]) * scale, (.1 + yt[c]) * scale,
         (.1 + xt[t]) * scale, (.1 + yt[t]) * scale >> f;

printf "</svg>\n" >> f;

end;
