#include <iostream>
#include <list>
#include <conio.h>
#include <windows.h>
using namespace std;
class Snake {
public:
    enum Face { EAST = 1, NORTH = 2, WEST = 3, SOUTH = 4 }; // 4 directions
    int max_x, max_y, is_alive;
    Face face;
    list<int> cells;
    Snake() { is_alive = 1; }
    Snake(int w, int h): max_x(w), max_y(h) { is_alive = 1; }
    bool having(int a_cell) {
        return this->cells.end() != find(cells.begin(), cells.end(), a_cell);
    }
    void set_face(Face f) { if (2 != abs(face - f)) { face = f; } }
    int head() { return this->cells.back(); }
    int next_head() {
        int x = this->head() % max_x, y = this->head() / max_x;
        switch (this->face) { // caculate new head on current face direction
            case EAST:  x = max_x-1 <= x ? 0 : x+1; break;
            case WEST:  x = x <= 0 ? max_x-1 : x-1; break;
            case NORTH: y = y <= 0 ? max_y-1 : y-1; break;
            case SOUTH: y = max_y-1 <= y ? 0 : y+1; break;
            default: break;
        }
        return y * max_x + x;
    }
}; // .class Snake =============================================================
class SnakeLogic {
    list<int> field, blanks;
    Snake snake;
    int score, food_cell, max_delay_ms;
    void get_input() {
        unsigned int waited_MS = 0, input_wait_MS = 20;
        do {
            if (kbhit()) { // Keyboard hit!
                switch (getch()) { // Get input char
                    case 'a': case 'A': snake.set_face(Snake::WEST);  break;
                    case 's': case 'S': snake.set_face(Snake::SOUTH); break;
                    case 'd': case 'D': snake.set_face(Snake::EAST);  break;
                    case 'w': case 'W': snake.set_face(Snake::NORTH); break;
                    case 'X': snake.is_alive = 0; break; // Stop Game
                    default: break;
                }
            }
            waited_MS += input_wait_MS;
            Sleep(input_wait_MS); // wait for next keyboard hit
        } while (max_delay_ms > waited_MS);
    }
    void generate_food() {
        blanks.clear(); // clear old field on previous calculation
        int i = 0;
        do { if (!snake.having(i)) { blanks.push_back(i); } }
    while (i++ < field.size()); // Finish finding blank cells
        list<int>::iterator it = blanks.begin(); // iterator at beginning
        advance(it, rand() % blanks.size()); // Go to a random blank cell
        food_cell = *(it); // assign new food position
    }
    void update() {
        int next_head = snake.next_head();
        if (snake.having(next_head)) { snake.is_alive = 0; } // die on collision
        else { // if there's a food, keep the tail, else cut tail
            if (next_head == food_cell) {
                generate_food(); score++; // make new food & increase score
            } else { snake.cells.erase(snake.cells.begin()); }
            snake.cells.push_back(next_head); // move ahead
        }
    }
    void re_draw() {
        system("cls");
        cout << "SNAKE CPP. Controls: A-left, S-down, D-right, W-up" << endl;
        int field_cell = 0, width = snake.max_x;
        do {
            if (field_cell % width == 0) { cout << " ~]"; }           //Border
            cout << ( field_cell == food_cell    ? " @ " :
                      snake.head() == field_cell ? " o " :
                      snake.having(field_cell)   ? " x " : " - " ); // .cout
            if (++field_cell % width == 0) { cout << "[~" << endl; }  //Border
        } while (field_cell < field.size());
        cout << "SCORE: " << score << endl;
    }
public:
    SnakeLogic(Snake s) {
        snake = s;
        int shape = snake.max_x * snake.max_y;
        while (shape) { field.push_back(shape--); } // Make field: 0...shape
    }
    void setup(int delay_ms) {
        srand( (unsigned int)time(0) ); // Randomize the seed
        snake.cells.push_back(0); snake.cells.push_back(1); // 2 init cells
        snake.face = Snake::EAST; // init face for cells [0,1]
        max_delay_ms = delay_ms;
        generate_food();
    }
    void loop() {
        while (snake.is_alive) { get_input(); update(); re_draw(); }
    };
}; // .class SnakeLogic || LINE NUMBER #100 ====================================

int main(int argc, const char * argv[]) {
    SnakeLogic game(Snake(20, 15));
    game.setup(100); // Delay 100ms
    game.loop();
    cout << "GAME OVER. Seemore at ngbaanh (@)medium.com" << endl;
    getch(); // press any key to continue
    return 0;
}
/// Thanks for reading my article at my medium blog.
/// Copyright 2020, baanh.nguyen@outlook.com.
/// All rights reserved.
