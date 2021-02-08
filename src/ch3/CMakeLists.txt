set(problems
    p2
    p3
    p4
    p5
    p6)

foreach(p ${problems})
  add_problem(ch3 ${p})
endforeach()
