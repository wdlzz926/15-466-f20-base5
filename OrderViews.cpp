#include "OrderViews.hpp"
namespace view {

OrderItemView::OrderItemView(Order order) {
	order_ = order;
	from_label_ = std::make_shared<TextSpan>();
	store_label_ = std::make_shared<TextSpan>();
	to_label_ = std::make_shared<TextSpan>();
	client_label_ = std::make_shared<TextSpan>();
	remaining_time_ = std::make_shared<TextSpan>();
	income_ = std::make_shared<TextSpan>();
	focus_indicator_ = std::make_shared<TextSpan>();

	from_label_->set_text("From: ");
	to_label_->set_text("To: ");
	focus_indicator_->set_font(FontFace::IBMPlexMono)
		.set_text(">>>")
		.set_visibility(false);
	set_order(order);
}

void OrderItemView::draw() {
	from_label_->draw();
	store_label_->draw();
	to_label_->draw();
	client_label_->draw();
	focus_indicator_->draw();
	if (is_expanded_) {
		remaining_time_->draw();
		income_->draw();
	}
}

void OrderItemView::set_order(Order order) {
	order_ = order;
	store_label_->set_text(get_location_name(order.store))
		.set_color(get_location_color(order.store));
	client_label_->set_text(get_location_name(order.client))
		.set_color(get_location_color(order.client));
	std::string remaining_time = "Time remaining: " + std::to_string(static_cast<int>(order.remaining_time)) + "sec";
	remaining_time_->set_text(remaining_time);
	income_->set_text("Income: $" + std::to_string(order.income));
	redo_render();
}

int OrderItemView::get_height() const {
	return (is_expanded_ ? 4 : 2) * FONT_SIZE;
}

void OrderItemView::set_expansion_state(bool value) {
	is_expanded_ = value;
	redo_render();
}

void OrderItemView::set_focus_state(bool value) {
	has_focus_ = value;
	redo_render();
}
void OrderItemView::set_position(int x, int y) {
	position_x = x;
	position_y = y;
	redo_render();
}

void OrderItemView::redo_render() {
	glm::u8vec4 color = glm::u8vec4(255);
	int focus_width = focus_indicator_->get_width();
	focus_indicator_->set_visibility(has_focus_)
		.set_position(position_x - focus_width - 8, position_y);
	from_label_->set_position(position_x, position_y)
		.set_color(color)
		.set_visibility(true);
	int from_label_width = from_label_->get_width();
	store_label_->set_position(position_x + from_label_width, position_y)
		.set_color(get_location_color(order_.store))
		.set_visibility(true);
	to_label_->set_position(position_x, position_y + 1*FONT_SIZE)
		.set_color(color)
		.set_visibility(true);
	int to_label_width = to_label_->get_width();
	client_label_->set_position(position_x + to_label_width, position_y + 1*FONT_SIZE)
		.set_color(get_location_color(order_.client))
		.set_visibility(true);
	if (is_expanded_) {
		remaining_time_->set_position(position_x, position_y + 2*FONT_SIZE)
			.set_color(color)
			.set_visibility(true);
		income_->set_position(position_x, position_y + 3*FONT_SIZE)
			.set_color(color)
			.set_visibility(true);
	} else {
		remaining_time_->set_visibility(false);
		income_->set_visibility(false);
	}
}

OrderSideBarView::OrderSideBarView() {
	pending_order_label_ = std::make_shared<TextSpan>();
	accepted_order_label_ = std::make_shared<TextSpan>();
	pending_order_label_->set_text("Pending Orders")
		.set_color(glm::u8vec4(122, 233, 255, 255))
		.set_position(1000, 32);

	int pending_orders_height = get_orders_view_height(pending_orders_);
	accepted_order_label_->set_text("Accepted Orders")
		.set_color(glm::u8vec4(157, 255, 122, 255))
		.set_position(1000, 32 + pending_orders_height + 32);
}
void OrderSideBarView::set_pending_orders(const std::vector<Order> &pending_orders) {
	pending_orders_.clear();
	for (const Order &o : pending_orders) {
		pending_orders_.emplace_back(o);
	}
	redo_render();
}

void OrderSideBarView::set_accepted_orders(const std::vector<Order> &accepted_orders) {
	accepted_orders_.clear();
	for (const Order &o : accepted_orders) {
		accepted_orders_.emplace_back(o);
	}
	redo_render();
}

int OrderSideBarView::get_orders_view_height(const std::vector<OrderItemView> &orders_view) {
	int height_sum = 0;
	for (const auto &v : orders_view) {
		height_sum += v.get_height();
	}
	return height_sum;
}

void OrderSideBarView::draw() {
	pending_order_label_->draw();
	accepted_order_label_->draw();
	for (auto &v : pending_orders_) {
		v.draw();
	}
	for (auto &v : accepted_orders_) {
		v.draw();
	}
}

void OrderSideBarView::redo_render() {
	int cursor_y = 32;
	pending_order_label_->set_text("Pending Orders")
		.set_color(glm::u8vec4(122, 233, 255, 255))
		.set_font_size(HEADER_FONT_SIZE)
		.set_position(1000, cursor_y);
	cursor_y += HEADER_FONT_SIZE;
	cursor_y += 16; // padding after header
	for (size_t i = 0; i < pending_orders_.size(); i++) {
		bool is_on_focus = (current_hover_panel_ == 0 && current_hover_item_ == (int)i);
		pending_orders_.at(i).set_position(1000, cursor_y);
		pending_orders_.at(i).set_focus_state(is_on_focus);
		pending_orders_.at(i).set_expansion_state(is_on_focus);
		cursor_y += pending_orders_.at(i).get_height();
		cursor_y += 16; // padding
	}
	cursor_y += 32; // padding between sections
	accepted_order_label_->set_text("Accepted Orders")
		.set_color(glm::u8vec4(157, 255, 122, 255))
		.set_font_size(HEADER_FONT_SIZE)
		.set_position(1000, cursor_y);
	cursor_y += HEADER_FONT_SIZE;
	cursor_y += 16; // padding after header

	for (size_t i = 0; i < accepted_orders_.size(); i++) {
		bool is_on_focus = (current_hover_panel_ == 1 && current_hover_item_ == (int)i);
		accepted_orders_.at(i).set_position(1000, cursor_y);
		accepted_orders_.at(i).set_focus_state(is_on_focus);
		accepted_orders_.at(i).set_expansion_state(is_on_focus);
		cursor_y += accepted_orders_.at(i).get_height();
		cursor_y += 16; // padding
	}
}

bool OrderSideBarView::handle_keypress(SDL_Keycode key) {
	if (key==SDLK_UP) {
		if (current_hover_panel_==1 && current_hover_item_==0) {
			current_hover_panel_ = 0;
			current_hover_item_ = std::max<int>((int) pending_orders_.size() - 1, 0);
		} else {
			current_hover_item_ = std::max<int>(current_hover_item_ - 1, 0);
		}
		redo_render();
		return true;
	} else if (key==SDLK_DOWN) {
		if (current_hover_panel_==0
		    && current_hover_item_ >= (int) pending_orders_.size() - 1
		    && !accepted_orders_.empty()) {
			current_hover_panel_ = 1;
			current_hover_item_ = 0;
		} else {
			if (current_hover_panel_==0) {
				current_hover_item_ = std::min<int>(current_hover_item_ + 1, (int) pending_orders_.size() - 1);
			} else {
				current_hover_item_ = std::min<int>(current_hover_item_ + 1, (int) accepted_orders_.size() - 1);
			}
		}
		redo_render();
		return true;
	}
	return false;
}

std::pair<int, int> OrderSideBarView::get_focus() const { return {current_hover_panel_, current_hover_item_}; }

}

