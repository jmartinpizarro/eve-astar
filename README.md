# eve-astar

> [!IMPORTANT]
> This function is already built-in the game. This project applies what I learnt in my `Heuristics and Optimization` classes for 
> implementing an A* algorithm.
<br>
EVE Online is commonly known for having a massive size for travelling across solar systems... In fact, it has over 7500 different systems. That number can be massive, specially when you are tring to go from point A to point B.

<br>
EVE-astar is a personal project for deepning into heuristics and search algorithms.

<br>
Made in C++ for optimization, it has been implemented from zero to hero.


## Use-Cases
1. Given the map of a region/constellation, the origin point (A) and the destination point (B), you want to **travel using the shortest _and safest_ route possible**.
2. Given the map of a region/constellation, the origin point (A) and the destination point (B), you want to **travel using the shortest route possible**.
3. Given the map of a region/constellation, the origin point (A) and the destination point (B), you want to **travel using the unsafest security route**.

Please, enjoy this as much as I have (probably not, it is going to be a nightmare) coding it.

## The process

$A^*$ is a `Best-First` algorithm that uses an heuristic $h(x)$:
$$h(x) = f(x) + g(x)$$

where

$f(x)$ is `Dijkstra Algorithm`. Why Dijkstra? Because is an excellent brute force algorithm. 
$g(x)$ is a random heuristic that we might think it may work. In this case, as we want to travel through the **safest path**, we want to take the node that `maximizes` the highest CONCORD security between its adjacent systems.

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




