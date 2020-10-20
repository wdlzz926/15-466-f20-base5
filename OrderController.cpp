#include "OrderController.hpp"
void OrderController::draw() {
	view->draw();
}
OrderController::OrderController() {
	view = std::make_shared<view::OrderSideBarView>();
	Order o1{Location::STORE1, Location::CLIENT1, false, false, 10, 60.0f};
	Order o2{Location::STORE2, Location::CLIENT1, false, false, 10, 60.0f};
	Order o3{Location::STORE2, Location::CLIENT2, true, false, 10, 60.0f};
	pending_orders_.push_back(o1);
	pending_orders_.push_back(o2);
	accepted_orders_.push_back(o3);
	view->set_pending_orders(pending_orders_);
	view->set_accepted_orders(accepted_orders_);
}
bool OrderController::handle_keypress(SDL_Keycode key) {
	return view->handle_keypress(key);
}
