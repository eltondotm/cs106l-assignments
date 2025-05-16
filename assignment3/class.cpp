#include "class.h"
#include <cstdlib>

TerminalGame::TerminalGame() : w(DEFAULT_WIDTH), h(DEFAULT_HEIGHT) {
  px = 0, py = 0;
  vx = 0, vy = 0;
  generate_frame();
}

TerminalGame::TerminalGame(int width, int height, int player_x, int player_y) : w(width), h(height) {
  px = player_x, py = player_y;
  vx = 0, vy = 0;
  generate_frame();
}

// Update frame based on current state
void TerminalGame::update() {
  *get_pos(px, py) = ' ';
  
  int try_x, try_y;
  try_x = px + vx;
  if (vy > 0) {
    try_y = py - 1;
  } else {
    try_y = py + 1;
  }

  if (*get_pos(try_x, py) == ' ') px = try_x;
  if (*get_pos(px, try_y) == ' ') py = try_y;
  
  *get_pos(px, py) = 'O';
}

// Draw frame to terminal
void TerminalGame::draw() {
  clear();
  std::cout << frame << std::flush;
}

std::pair<int, int> TerminalGame::get_player_pos() const {
  return { px, py };
}

void TerminalGame::set_player_pos(int x, int y) {
  px = x;
  py = y;
}

void TerminalGame::set_player_vel(int x_vel, int y_vel) {
  vx = x_vel;
  vy = y_vel == -1 || *get_pos(px, py + 1) != FILLED ? vy - 1 : y_vel;
}

// No book-keeping for rectangles, just never overwrite them
void TerminalGame::add_rect(int x1, int y1, int x2, int y2) {
  for (int y = y1; y <= y2; ++y) {
    for (int x = x1; x <= x2; ++x) {
      *get_pos(x, y) = FILLED;
    }
  }
}

void TerminalGame::clear() {
  #ifdef _WIN32
    system("cls");
  #else
    std::cout << "\033[2J\033[1;1H";
  #endif
}

// Currently, this will erase all rectangles. Also it is very ugly.
void TerminalGame::generate_frame() {
  for (int y = 0; y < h; ++y) {
    frame += "\n";
    for (int x = 0; x < w; ++x) {
      if (x == 0) {
        if (y == 0) { 
          frame += '*'; 
        } else if (y == h - 1) {
          frame += '*';
        } else {
          frame += '|';
        }
      } else if (x == w - 1) {
        if (y == 0) { 
          frame += '*'; 
        } else if (y == h - 1) {
          frame += '*';
        } else {
          frame += '|';
        }
      } else if (y == 0 || y == h - 1) {
        frame += '-';
      } else {
        frame += ' ';
      }
    }
  }
}

// With the purpose of modifying the char at that location
char* TerminalGame::get_pos(int x, int y) {
  return &frame[y * (w + 1) + x + 1];
}
