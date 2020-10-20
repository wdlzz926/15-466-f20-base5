#pragma once

#include <memory>
#include <vector>
#include "View.hpp"
#include "OrderModels.hpp"

namespace view {

class OrderItemView {
public:
	explicit OrderItemView(Order order);
	void draw();
	int get_height() const;
	void set_order(Order order);
	void set_position(int x, int y);
	void set_expansion_state(bool value);
	void set_focus_state(bool value);

private:
	void redo_render();

	static constexpr int FONT_SIZE = 16;
	int position_x = 0;
	int position_y = 0;
	Order order_;
	bool is_expanded_ = false;
	bool has_focus_ = false;
	TextSpanPtr from_label_ = std::make_shared<TextSpan>();
	TextSpanPtr store_label_ = std::make_shared<TextSpan>();
	TextSpanPtr to_label_ = std::make_shared<TextSpan>();
	TextSpanPtr client_label_ = std::make_shared<TextSpan>();
	TextSpanPtr remaining_time_ = std::make_shared<TextSpan>();
	TextSpanPtr income_ = std::make_shared<TextSpan>();
	TextSpanPtr is_delivering_label_ = std::make_shared<TextSpan>();
	TextSpanPtr focus_indicator_ = std::make_shared<TextSpan>();
};

class OrderSideBarView {
public:
	OrderSideBarView();
	void set_pending_orders(const std::vector<Order> &pending_orders);
	void set_accepted_orders(const std::vector<Order> &accepted_orders);
	void set_total_income(int value);
	void draw();
	void redo_render();
	bool handle_keypress(SDL_Keycode key);
	std::pair<int, int> get_focus() const;


private:
	static constexpr int HEADER_FONT_SIZE = 32;
	static int get_orders_view_height(const std::vector<OrderItemView> &orders_view);
	TextSpanPtr total_income_label_;
	TextSpanPtr pending_order_label_;
	TextSpanPtr pending_order_prompt_;
	TextSpanPtr pending_order_prompt2_;
	std::vector<OrderItemView> pending_orders_;
	TextSpanPtr accepted_order_label_;
	std::vector<OrderItemView> accepted_orders_;
	int total_income_ = 0;

	// current_hover_panel_: 0 means pending order panel is in hover state
	// 1 means accepted order panel is in hover state
	int current_hover_panel_ = 0;
	int current_hover_item_ = 0;
};
}