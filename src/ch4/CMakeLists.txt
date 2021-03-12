set(problems
    p1
    p2
    p3
    p4
    p5
    p6
    p7
    p8
    p9
    p10
    p11
    p12)

foreach(p ${problems})
  add_problem(ch4 ${p})
endforeach()
