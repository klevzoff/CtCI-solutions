set(problems
    p1
    p2
    p3)

foreach(p ${problems})
  add_problem(ch5 ${p})
endforeach()
