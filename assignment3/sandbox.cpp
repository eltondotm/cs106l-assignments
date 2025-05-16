#include "class.h"

#include <chrono>
#include <thread>

#include <windows.h>

/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

bool key_pressed(int VK) {
  return (GetAsyncKeyState(VK) & 0x8000) != 0;
}

// Control with WASD (only works on Windows)
void sandbox() {
  TerminalGame game { 50, 15, 1, 12 };
  game.add_rect(1, 13, 48, 13);
  game.add_rect(8, 8, 13, 12);
  game.add_rect(19, 6, 22, 8);
  game.add_rect(30, 7, 40, 9);

  while (true) {
    int vx = 0;
    int vy = -1;
    if (key_pressed('W')) vy = 5;
    if (key_pressed('A')) vx -= 1;
    if (key_pressed('D')) vx += 1;

    game.set_player_vel(vx, vy);
    game.update();
    game.draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(32));
  }
}