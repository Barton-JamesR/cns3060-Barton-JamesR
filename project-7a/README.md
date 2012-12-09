James Richard Barton
=====================

CNS 3060-601
Barton.JamesR@gmail.com

cns3060-Barton-JamesR
=====================

This one was actually fairly easy.  I had a lot of trouble with it initially until I realized that I never actually called fork() anywhere... but I fixed that.  It appears to run without fault, so I think it's about done.  I elected to do 7a first because I was concerned about the differences between 'runs on OSx' and 'runs on the class server' which I was fairly certain was Linux-based... so Processes it is!

Something that did get me though was the part where the parent would send SIGUSR2 after a few seconds to the child; this wouldn't allow the child to do more than three seconds worth of work total... wouldn't it make more sense for the parent to send it to the child after it was being blocked, to allow the child as much time as it needed to work, at which point... but then it couldn't... Something like that.  Yeah.

And for the record, the stuff that I was talking about in the comments, and the work process, and the... etc. was from the Touhou Project.  Pay it no mind.
