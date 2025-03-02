# eve-astar

> [!IMPORTANT]
> This function is already built-in the game, this code has been created just for fun and understanding.
<br>
EVE Online is commonly known for having a massive size for travelling across solar systems... In fact, it has over 7500 different systems. That is a big number, specially **if you want to travel from a point A to a point B**.

<br>
EVE-astar is a personal project for deepning into heuristics and search algorithm.

<br>
Made in C++ for optimization, it has been implemented from zero to hero.


## Use-Cases
1. Given the map of a region/constellation, the origin point (A) and the destination point (B), you want to **travel using the shortest _high security_ route possible**.
2. Given the map of a region/constellation, the origin point (A) and the destination point (B), you want to **travel using the shortest route possible**.
3. Given the map of a region/constellation, the origin point (A) and the destination point (B), you want to **travel using the just a low/null security route**.

Please, enjoy this as much as I have (probably not, it is going to be a nightmare) coding it.

## The process

At first, the search algorithm from point $A$ to $B$ would be `Dijkstra`. Why Dijkstra? Well, pure Dijkstra cannot check if you are travelling through the safest path, only the shortest one.

This is an interesting approach for understanding how brute force algorithms work.

After implementing Dijkstra, an heuristic function $h(x)$ that has not been decided yet will be implemented; with the corresponding A* algorithm.

## Tests

A battery of tests can be executed. The `.txt` files follow this format:

```
Origin
Destination
System1,Concord_sec_status1,AdjSystem1(distance),AdjSystem2(distance), ... AdjSystemN(distance) 
System2,Concord_sec_status2,AdjSystem1(distance),AdjSystem2(distance), ... AdjSystemN(distance)

...

SystemN,Concord_sec_status2,AdjSystem1(distance),AdjSystem2(distance), ... AdjSystemN(distance)
```

For example, here is a simplified version of one test:
![A simplified test of the EVE PathFinding Problem](test.png)




