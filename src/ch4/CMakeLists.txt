set(problems
    p1
    p2
    p3
    p4
    p5
    p6)

foreach(p ${problems})
  add_problem(ch4 ${p})
endforeach()
