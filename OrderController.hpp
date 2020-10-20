#pragma once

#include "OrderModels.hpp"
#include "OrderViews.hpp"
#include <vector>

class OrderController {
public:
	OrderController();
	void update(float elapsed);
	bool handle_keypress(SDL_Keycode key);
	void draw();
	const Order &get_current_active_order();
	void pickup_order(Location store);
	void deliver_order(Location client);
	int current_income_ = 0;
	std::vector<Order> pending_orders_;
	std::vector<Order> accepted_orders_;
	std::shared_ptr<view::OrderSideBarView> view;
};