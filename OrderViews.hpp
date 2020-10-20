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
	TextSpanPtr from_label_;
	TextSpanPtr store_label_;
	TextSpanPtr to_label_;
	TextSpanPtr client_label_;
	TextSpanPtr remaining_time_;
	TextSpanPtr income_;
};

class OrderSideBarView {
public:
	OrderSideBarView();
	void set_pending_orders(const std::vector<Order> &pending_orders);
	void set_accepted_orders(const std::vector<Order> &accepted_orders);
	void draw();
	void redo_render();

private:
	static constexpr int HEADER_FONT_SIZE = 32;
	static int get_orders_view_height(const std::vector<OrderItemView> &orders_view);
	TextSpanPtr pending_order_label_;
	std::vector<OrderItemView> pending_orders_;
	TextSpanPtr accepted_order_label_;
	std::vector<OrderItemView> accepted_orders_;
};
}