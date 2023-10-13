
<!-- PROJECT LOGO -->
<br />
<div align="center">

  <h3 align="center">Survival Maze</h3>

  <p align="center">
    A labrinth game where the player should survive till the end
    <br />
   
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
      </ul>
    </li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#acknowledgments">Acknoledgments</a></li>
    
    
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

In this maze survival gamr, your objective is to reach the end of the labrinth while eliminating the opponents that stand in your wait.

* **Player** :
  * The player can control, in third person, a simple human avatar that is represented by colourful cubes. You can move with the W, A, S, D keys.
  * By default, the character will have a Third Person camera attached, but it will be able to attack by launching some projectiles. Entering the attack mode is done with the right mouse, so the camera will be switched to First Person and you will be able to aim and launch projectiles in the direction of the camera by pressing the left mouse button.
  * Projectiles are simple objects that have a direction, a speed and a lifetime. When they encounter an obstacle (enemy, wall) or exceed their lifetime, they will disappear from the scene.

* **Maze** :
  * The maze is different at every run. In the begining the player starts at a random valid position in the maze

* **Enemy** :
  * In the labyrinth the player can meet enemies. They patrol the corridor (they move regularly in their grid cell). Enemies' positioning can block the player.
  * Enemies move only within the square associated with them. 
  * To reach the exit from the maze, the player may be forced to pass through cells containing enemies. However, if the player is touched by an enemy, he loses a life. When you lose all available life, the game will stop immediately.
  * The player has the ability to launch projectiles at the enemies. When they hit, the respective enemy will disappear. The player will thus be able to continue his journey.

* **HUD**
  * In addition to the surrounding world, there's also a HUD (heads-up display). It has 2 elements that always appear on the player's screen in the same position, as graphical interface elements:

    * Life: Life is indicated in the form of a healthbar by 2 rectangles, one wireframe the other solid
    * Time Remaining: Time remaining is indicated by a second status bar, similar to the life bar.

* **Gameplay** :
  * The goal of the game is for the player to successfully exit the maze within a limited time.
  * As stated above, there are cells with enemies that move continuously inside these cells. Every time the player is touched by an enemy, he loses a life. The enemy does not allow the player to bypass him (easily), thus forcing him to shoot at the enemy.
  * When the player exits the maze, runs out of life, or runs out of time, the game ends.





### Built With

These are what I used to build the bot:

* ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
* ![OpenGL](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=for-the-badge&logo=opengl)
* ![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)



<!-- GETTING STARTED -->
## Getting Started

To be able to use this project you will need some stuff first.

### Prerequisites

* cmake
  [Cmake Installation steps](https://cgold.readthedocs.io/en/latest/first-step/installation.html)
* OpenGL



<!-- ROADMAP -->
## Roadmap

- [x] Make a window where to render stuff
- [x] Make the player
- [x] Binding keys
- [x] Cameras
- [x] Make the maze
- [x] Make opponents
- [x] Make opponents move
- [x] Make projectiles
- [x] Apply textures
- [x] Collisions
- [x] Healthbar and Time
 



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Some things that helped me while making this project :
* [Learn OpenGL](https://learnopengl.com/)





