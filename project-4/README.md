James Richard Barton
=====================

CNS 3060-601
Barton.JamesR@gmail.com

cns3060-Barton-JamesR
=====================

	This particular project was really, really easy compared to the last one.  Everything went off smoothly, debugging took about 1/5th of the time it took to write, and I feel that it just went well overall.

First-Come, First Served
=====================
	The First-Come, First-Served algorithm was incredibly simple to implement.  The algorithm takes in each track in sequence, and then moves the head to each specified track in the same exact order, regardless of efficiency.  All that was needed in this case was to iterate through each part of the array where the input was stored and to move the head to each track in order.

Shortest Path
=====================
	The Shortest Path algorithm was slightly more complex, but still simple in concept.  The algorithm takes the entire input from the user, and moves the head to whatever destination is closest to the current position of the head.  In this case, I had the program run through with a starting position and check each part of the input array to find the closest destination that hadn't already been visited, and repeated the process until there were no longer any unvisited destinations.

Scan-Look/Elevator
=====================
	The Elevator (Scan-Look) algorithm was spectacularly simple to design following the Shortest Path algorithm; Elevator is generally just a Shortest Path that is limited to information in one direction (greater than or less than) until it reaches a boundary (the maximum value, or zero).  Factor in that we don't have to worry about the zero case, given that you would start with the maximum value in any case where you would start in the less than direction, and the algorithm barely added anything to the existing Shortest Path algorithm.

Analysis
=====================

	In regards to the preformance of the algorithms in question, Shortest Path was the most efficient under the circumstances given.  First-Come, First-Served was generally inefficient, and only reached similar levels of performance to the others when the inputs were arranged in ascending order.  Elevator was a close second, but never quite reached the same levels of efficiency as the Shortest Path algorithm.
	However, this is only one scenario.  In a scenario where you would be consistently getting new inputs, Elevator would be far more consistent, taking no more than 2*max - 1 head movements to get to any given location, than the Shortest Path algorithm which might never get to inputs that were far away from it.  First-Come, First-Served would only really be useful in a situation where each case absolutely HAD to be handled in order.  Personally, under this particular circumstance, I would actually prefer to use the Elevator algorithm, to ensure that every request that came in was going to be serviced, as opposed to the more efficient, but more dangerous Shortest Path variant.
