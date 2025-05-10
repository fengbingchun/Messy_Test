#ifndef KEYWORD_I_
#define KEYWORD_I_

/* Warnings for C# keywords */
#define CSHARPKW(x) %keywordwarn("'" `x` "' is a C# keyword, renaming to '" `x` "_'",rename="%s_")  `x`

CSHARPKW(in);
CSHARPKW(out);

#undef CSHARPKW

#endif //KEYWORD_I_
