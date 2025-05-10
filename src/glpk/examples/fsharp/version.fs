open System
open org.gnu.glpk

[<EntryPoint>]
let main argv =
    printfn "GLPK %s" (GLPK.glp_version())
    0
