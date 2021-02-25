## Labyrinth game
The Labyrinth is a game in which the player has to pass safely to the end of thme maze without meeting the monster.

The main focus of the project is the way the player traverses the maze.

There are two charatcters to choose from:
* The Sorceress 
* The Magician
Both of whom have a different way of moving through the labyrinth.

* The Sorceress' traversal uses A* algorithm, because she is able to "see into the future" and can find the shortest path to the end. In this case A* gives us more precise calculation of the shortest path unlike Dijkstra's Algorithm which is not always accurate.

* The Magician's traversal uses Depth First Search because the way he moves is always in one direction until he finds an obsticle.
