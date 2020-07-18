# Snake-A.I

Wrote the solver portion of the Snake Program (djikstra.cpp, djikstra.h, player.cpp, player.h, weightedGraph.cpp, weightedGraph.h) for an algorithms course at my university

		- Create a weighted graph (lower weights on the outside; right now increase is by powers of 3)
		
		- Run djikstra's (repeat 3 - hoping it finds a slightly different path -random weight added to weight)
		
			- if it finds a path
			
				- look forward and see if path to cells adj to tail are open
				
					if true, follow dijkstra path
					
				- if false, move in direction of tail and hope something opens up

			-if it doesnt find a path, move in direction of tail and hope something opens up, keep a counter

		- if counter exceeds a threshold, return None
