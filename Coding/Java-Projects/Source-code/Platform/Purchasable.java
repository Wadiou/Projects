package Platform;

public interface Purchasable {
    void addToCart(String productID, int quantity);
    void removeFromCart(String productID, int quantity);
    void checkout();
    void viewOrderHistory();
}
