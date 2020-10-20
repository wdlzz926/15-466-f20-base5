#include "OrderModels.hpp"

#include <exception>

glm::u8vec4 get_location_color(Location loc) {
	switch (loc) {
		case Location::STORE1: return glm::u8vec4(255, 0, 0, 255);
		case Location::STORE2: return glm::u8vec4(255, 255, 0, 255);
		case Location::CLIENT1: return glm::u8vec4(255, 0, 255, 255);
		case Location::CLIENT2: return glm::u8vec4(0, 255, 255, 255);
		default: throw std::invalid_argument("loc not recognized");
	}
}
std::string get_location_name(Location loc) {
	switch (loc) {
		case Location::STORE1: return "store1";
		case Location::STORE2: return "store2";
		case Location::CLIENT1: return "client1";
		case Location::CLIENT2: return "client2";
		default: throw std::invalid_argument("loc not recognized");
	}
}

glm::vec3 get_location_position(Location loc) {
	switch (loc) {
		case Location::STORE1: return glm::vec3(0.0f, 0.0f, 0.0f);
		case Location::STORE2: return glm::vec3(1.0f, 0.0f, 0.0f);
		case Location::CLIENT1: return glm::vec3(0.0f, 1.0f, 0.0f);
		case Location::CLIENT2: return glm::vec3(1.0f, 1.0f, 0.0f);
		default: throw std::invalid_argument("loc not recognized");
	}
}
