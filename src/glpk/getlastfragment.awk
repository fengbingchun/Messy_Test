# split path and extract last part
{
n = split($1,parts,"/");
print(parts[n]);
exit;
}
