#pragma once

#include <iostream>
#include <string>
#include <utility>

#define DEFAULT_WIDTH 20
#define DEFAULT_HEIGHT 20
#define FILLED '#'

class TerminalGame {
  public:
    TerminalGame();
    TerminalGame(int width, int height, int player_x, int player_y);

    void update();
    void draw();
    std::pair<int, int> get_player_pos() const;
    void set_player_pos(int x, int y);
    void set_player_vel(int x_vel, int y_vel);
    void add_rect(int x1, int y1, int x2, int y2);

  private:
    void clear();
    void generate_frame();
    char* get_pos(int x, int y);

    std::string frame;
    const int w;
    const int h;
    int px;
    int py;
    int vx;
    int vy;
};