James Richard Barton
=====================

CNS 3060-601
Barton.JamesR@gmail.com

cns3060-Barton-JamesR
=====================

Well, part A didn't really surprise me.  All it really did was start stuff up and shut it back down.  I did actually try killing off the main thread afterward instead of returning, and it *did count to 10*.  Pretty great, but irrelevant.  I put it back, and moved on to part B.

Part B didn't really get me either.  I saw that the way the loop was set up, it would make *everything* into the same variable at each step, at about the same time, so I did expect a 10 here.  What I didn't expect was the result for...

Part C.  I honestly didn't expect to get a full 40 when I ran it, let alone consistently.  I figure that it probably just ran through the entire loop before it had to wait in line, and so it got 40 anyway.  Nice, but I'm not so sure that it was *what I was supposed to get*.  Ah well.

Part D gave me a bit of trouble; I actually started the mutex just below sleep(1), and it gave me the wrong answer, so I just kinda moved it up line by line until I got it.  In hindsight, putting it before the update of the tempVariable was... rather obvious really... but hey.  We all learn from our mistakes.


Overall, this whole project was just a nice, laid-back kinda project.  It was good for my schedule (people who say that finals are the worst week in Fall Semester obviously haven't met my family.  I doubt I get more than five minutes on the hour to myself over the entire break.), but I'll probably go back and mess with it just for the feeling of "IT'S FINALLY DONE!!" that I'm accustomed to getting after programming projects.
