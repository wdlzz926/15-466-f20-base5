#include "OrderController.hpp"
#include <iterator>
#include "random.hpp"
void OrderController::draw() {
	view->draw();
}
OrderController::OrderController() {
	view = std::make_shared<view::OrderSideBarView>();
//	Order o1{Location::STORE1, Location::CLIENT1, false, false, 10, 60.0f};
//	Order o2{Location::STORE2, Location::CLIENT1, false, false, 10, 60.0f};
//	Order o3{Location::STORE2, Location::CLIENT2, true, false, 10, 60.0f};
//	pending_orders_.push_back(o1);
//	pending_orders_.push_back(o2);
//	accepted_orders_.push_back(o3);
	view->set_pending_orders(pending_orders_);
	view->set_accepted_orders(accepted_orders_);
}
bool OrderController::handle_keypress(SDL_Keycode key) {
	if (key==SDLK_RETURN) {
		std::pair<int, int> focus = view->get_focus();
		if (focus.first==0 && focus.second < (int) pending_orders_.size()) {
			Order o = pending_orders_.at(focus.second);
			o.is_accepted = true;
			o.is_delivering = false;
			pending_orders_.erase(std::next(pending_orders_.begin(), focus.second));
			accepted_orders_.push_back(o);
			view->set_pending_orders(pending_orders_);
			view->set_accepted_orders(accepted_orders_);
			return true;
		} else {
			return false;
		}
	} else {
		return view->handle_keypress(key);
	}

}

void OrderController::pickup_order(Location store) {
	for (auto &o : accepted_orders_) {
		if (o.store==store) {
			o.is_delivering = true;
		}
	}
	view->set_accepted_orders(accepted_orders_);
}
void OrderController::deliver_order(Location client) {
	for (auto it = accepted_orders_.begin(); it!=accepted_orders_.end();) {
		if (it->client==client && it->is_delivering) {
			add_income(it->income);
			it = accepted_orders_.erase(it);
		} else {
			it++;
		}
	}
	view->set_accepted_orders(accepted_orders_);
}
void OrderController::add_income(int delta) {
	current_income_ += delta;
	view->set_total_income(current_income_);
}

void OrderController::update(float elapsed) {
	next_order_remaining_time -= elapsed;

	if (next_order_remaining_time <= 0) {
		generate_new_pending_order();
	}
//	for (auto it = pending_orders_.begin(); it!=pending_orders_.end();) {
//		it->remaining_time -= elapsed;
//		if (it->remaining_time <= 0) {
//			it = pending_orders_.erase(it);
//		} else {
//			it++;
//		}
//	}
	for (auto it = accepted_orders_.begin(); it!=accepted_orders_.end();) {
		it->remaining_time -= elapsed;
		if (it->remaining_time <= 0) {
			it = accepted_orders_.erase(it);
		} else {
			it++;
		}
	}
	view->set_pending_orders(pending_orders_);
	view->set_accepted_orders(accepted_orders_);
}
void OrderController::generate_new_pending_order() {
	using Random = effolkronium::random_static;
	if (pending_orders_.size() <= 4) {
		Location client = get_random_client();
		Location store = get_random_store();
		int income = Random::get(10, 50);
		float time = Random::get<float>(30.0f, 90.0f);
		Order o1{store, client, false, false, income, time};
		pending_orders_.push_back(o1);
	}
	float next_order_arrival = Random::get<float>(5.0f, 15.0f);
	next_order_remaining_time = next_order_arrival;
}
