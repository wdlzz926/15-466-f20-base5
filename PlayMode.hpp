#include "Mode.hpp"

#include "Scene.hpp"
#include "WalkMesh.hpp"
#include "OrderController.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;
	void switch_camera();
	void update_order();
	glm::vec2 update_walker(float elapsed);
	glm::vec2 update_car(float elapsed);
	const float friction = 1.5f;
	const float acceleration = 4.0f;
	const float enter_dis = 1.0f;
	const float order_dis = 2.0f;
	const float max_speed = 4.0f;
	const float turn_speed = 30.0f;
	std::shared_ptr<view::TextSpan> button_hint;


	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//player info:
	struct Player {
		WalkPoint at;
		//transform is at player's feet and will be yawed by mouse left/right motion:
		Scene::Transform *transform = nullptr;
		//camera is at player's head and will be pitched by mouse up/down motion:
		Scene::Camera *camera = nullptr;
	} walker, car;

	bool driving = true;
	float car_speed = 0.0f;

	std::shared_ptr<OrderController> order_controller = std::make_shared<OrderController>();
};
