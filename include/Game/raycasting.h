#pragma once

#pragma once

#include <cmath>

// Structure to represent the player
struct Player {
    int x;     // Player position X
    int y;     // Player position Y
    int angle; // Player angle of rotation
    int fov;   // Player field of view
};

// Function to move the player based on keyboard input
void movePlayer(Player& player, const Uint8* keys) {
    // Move up, down, left, right
    if (keys[SDL_SCANCODE_UP]) {
        int dx = std::sin(player.angle) * 10;
        int dy = std::cos(player.angle) * 10;
        player.x += dx;
        player.y += dy;
    }
    if (keys[SDL_SCANCODE_DOWN]) {
        int dx = std::sin(player.angle) * 10;
        int dy = std::cos(player.angle) * 10;
        player.x -= dx;
        player.y -= dy;
    }
    if (keys[SDL_SCANCODE_LEFT]) {
        player.angle -= 4;
        if (player.angle < 0) {
            player.angle += 360;
        }
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        player.angle += 4;
        if (player.angle > 359) {
            player.angle -= 360;
        }
    }
}

