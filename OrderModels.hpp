#pragma once

#include <glm/glm.hpp>
#include <string>

enum class Location {
    STORE1,
    STORE2,
    CLIENT1,
    CLIENT2
};

glm::vec3 get_location_position(Location loc);

glm::u8vec4 get_location_color(Location loc);

std::string get_location_name(Location loc);

struct Order {
    Location store;
    Location client;
    bool is_accepted;

    // when set to true, food has been picked up
    // when set to false, food hasn't been picked up yet.
    // only valid when is_accepted==true
    bool is_delivering;

    // income if successfully made this order (in USD)
    int income;

    // remaining time: the remaing time in seconds (time-in-game)
    float remaining_time;
};