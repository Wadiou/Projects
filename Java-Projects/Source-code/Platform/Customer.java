package Platform;
import  static java.lang.Math.random;
import java.util.ArrayList;

public class Customer extends User implements Purchasable {
     ShoppingCart cart = new ShoppingCart();
    private ArrayList<Order> orderHistory = new ArrayList<>();

    public Customer(String userID, String username, String password, String email) {
        super(userID, username, password, email);
    }

    public void addToCart(String productID, int quantity) {
        Product product = ECommercePlatform.findProductByID(productID);
        if (product != null && quantity <= product.getQuantity()) {
            product.setQuantityreduce(quantity);
            cart.addItem(product, quantity);
        } else {
            System.out.println("Not enough quantity or product not found!");

        }
    }

    public void removeFromCart(String productID, int quantity) {
        cart.removeItem(productID, quantity);
    }

    public void checkout() {
        Order order = new Order(super.getUserID(), cart.getItems());
        orderHistory.add(order);
        cart.clear();
    }

    public void viewOrderHistory() {
        for (Order order : orderHistory) {
            order.getOrderDetails();
        }
    }

    class ShoppingCart {
        private ArrayList<CartItem> items = new ArrayList<>();

        public void addItem(Product product, int quantity) {
            for (CartItem item : items) {
                if (item.getProduct().getProductID().equals(product.getProductID())) {
                    item.increaseQuantity(quantity);
                    return;
                }
            }
            items.add(new CartItem(product, quantity));
        }

        public void removeItem(String productID, int quantity) {
            for (CartItem item : items) {
                if (item.getProduct().getProductID().equals(productID)) {
                    item.decreaseQuantity(quantity);
                    if (item.getQuantity() <= 0) {
                        items.remove(item);
                    }
                    Product product = ECommercePlatform.findProductByID(productID);
                    if (product != null) {
                        product.setQuantityadd(quantity);
                    }
                    return;
                }
            }
            System.out.println("Product not found in cart!");
        }

        public ArrayList<CartItem> getItems() {
            return items;
        }

        public void viewCart() {
            for (CartItem item : items) {
                System.out.println(item.getProduct().getName() + " - Quantity: " + item.getQuantity());
            }
        }

        public void clear() {
            for (CartItem item : items) {
                Product product = ECommercePlatform.findProductByID(item.getProduct().getProductID());
                if (product != null) {
                    product.setQuantityadd(item.getQuantity());
                }
            }
            items.clear();
        }

        class CartItem {
            private Product product;
            private int quantity;

            public CartItem(Product product, int quantity) {
                this.product = product;
                this.quantity = quantity;
            }

            public Product getProduct() {
                return product;
            }

            public int getQuantity() {
                return quantity;
            }

            public void increaseQuantity(int quantity) {
                this.quantity += quantity;
            }

            public void decreaseQuantity(int quantity) {
                this.quantity -= quantity;
            }
        }
    }
}
