set(problems
    p1
    p2
    p3
    p4
    p5
    p6
    p7
    p8)

foreach(p ${problems})
  add_problem(ch5 ${p})
endforeach()
