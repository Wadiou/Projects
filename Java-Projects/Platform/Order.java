package Platform;

import java.util.ArrayList;

public class Order {
    private String userID;
    private ArrayList<Customer.ShoppingCart.CartItem> items;

    public Order(String userID, ArrayList<Customer.ShoppingCart.CartItem> items) {
        this.userID = userID;
        this.items = items;
    }

    public void getOrderDetails() {
        System.out.println("Order for User ID: " + userID);
        for (Customer.ShoppingCart.CartItem item : items) {
            item.getProduct().getProductInfo();
        }
    }
}
