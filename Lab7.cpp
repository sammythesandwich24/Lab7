#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;



int main()
{
    // Create our window and world with gravity 0,1
    RenderWindow window(VideoMode(1000, 800), "Bounce");
    World world(Vector2f(0, 1));

    // Create the ball
    PhysicsCircle ball;
    ball.setCenter(Vector2f(200, 200));
    ball.setRadius(20);
    ball.setVelocity(Vector2f(.1,-.1));

    // Create the floor
    PhysicsRectangle floor;
     floor.setCenter(Vector2f(400, 590));
      floor.setSize(Vector2f(800, 40));
   
    floor.setStatic(true);

    // Create the ceiling
    PhysicsRectangle ceiling;
    ceiling.setSize(Vector2f(800, 40));
    ceiling.setCenter(Vector2f(400, 10));
    ceiling.setStatic(true);

    // Create the left wall
    PhysicsRectangle leftWall;
    leftWall.setCenter(Vector2f(10, 300));
    leftWall.setSize(Vector2f(40, 600));
    
    leftWall.setStatic(true);

    // Create the right wall
    PhysicsRectangle rightWall;
    rightWall.setSize(Vector2f(40, 600));
    rightWall.setCenter(Vector2f(790, 300));
    rightWall.setStatic(true);

    // Create the center block
    PhysicsRectangle centerBlock;
    centerBlock.setSize(Vector2f(100, 100));
    centerBlock.setCenter(Vector2f(400, 300));
    centerBlock.setStatic(true);

    int bangCount = 0; // Initialize bang count to 0
    int thudCount = 0;
    // Set onCollision lambda for the center block
    centerBlock.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
        cout << "bang " << bangCount << endl;
        bangCount++;
        if (bangCount >= 3) {
            exit(0); // Exit the program after the center block has been hit 3 times
        }
    };
    leftWall.onCollision = rightWall.onCollision = ceiling.onCollision = floor.onCollision =
        [&thudCount](PhysicsBodyCollisionResult result) {
       cout << "thuds " << thudCount << endl;
       thudCount++;

    };

  //  leftWall.onCollision = rightWall.onCollision = ceiling.onCollision = floor.onCollision =
     
  //  };

    // Add all the physics bodies to the world
    world.AddPhysicsBody(floor);
    world.AddPhysicsBody(ceiling);
    world.AddPhysicsBody(leftWall);
    world.AddPhysicsBody(rightWall);
    world.AddPhysicsBody(ball);

    world.AddPhysicsBody(centerBlock);

    Clock clock;
    Time lastTime(clock.getElapsedTime());

    while (window.isOpen()) {
        // Handle events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        // calculate MS since last frame
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());

        if (deltaTimeMS > 0) {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }

        window.clear(Color(0, 0, 0));
        window.draw(ball);
        window.draw(floor);
        window.draw(ceiling);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(centerBlock);
        window.display();
    }

    return 0;
}
