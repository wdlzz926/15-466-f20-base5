#include "OrderModels.hpp"

#include <exception>
#include "random.hpp"

glm::u8vec4 get_location_color(Location loc) {
	switch (loc) {
		case Location::STORE_CHEESECAKE: return glm::u8vec4(0xEB, 0xE1, 0x60, 0xff);
		case Location::STORE_PANCAKE: return glm::u8vec4(0xC0, 0xDF, 0xDD, 0xff);
		case Location::CLIENT1: return glm::u8vec4(0xc4, 0xfa, 0x89, 0xff);
		case Location::CLIENT2: return glm::u8vec4(0x44, 0xbd, 0xd8, 0xff);
		case Location::CLIENT3: return glm::u8vec4(0xea, 0xe8, 0x61, 0xff);
		case Location::CLIENT4: return glm::u8vec4(0xff, 0x91, 0x9a, 0xff);
		default: throw std::invalid_argument("loc not recognized");
	}
}
std::string get_location_name(Location loc) {
	switch (loc) {
		case Location::STORE_CHEESECAKE: return "Cheesecake Workshop";
		case Location::STORE_PANCAKE: return "Tartan Pancakes";
		case Location::CLIENT1: return "client1";
		case Location::CLIENT2: return "client2";
		case Location::CLIENT3: return "client3";
		case Location::CLIENT4: return "client4";
		default: throw std::invalid_argument("loc not recognized");
	}
}

glm::vec3 get_location_position(Location loc) {
	switch (loc) {
		case Location::STORE_CHEESECAKE: return glm::vec3(-3.0f, -3.0f, 0.0f);
		case Location::STORE_PANCAKE: return glm::vec3(17.0f, 0.0f, 0.0f);
		case Location::CLIENT1: return glm::vec3(-9.0f, 11.0f, 0.0f);
		case Location::CLIENT2: return glm::vec3(6.0f, 11.0f, 0.0f);
		case Location::CLIENT3: return glm::vec3(10.0f, -11.0f, 0.0f);
		case Location::CLIENT4: return glm::vec3(7.0f, 2.0f, 0.0f);
		default: throw std::invalid_argument("loc not recognized");
	}
}

using Random = effolkronium::random_static;

Location get_random_store() {
	return Random::get({Location::STORE_CHEESECAKE, Location::STORE_PANCAKE});
}

Location get_random_client() {
	return Random::get({Location::CLIENT1, Location::CLIENT2, Location::CLIENT3, Location::CLIENT4});
}
