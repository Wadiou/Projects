package Platform;

public class Main {
    public static void main(String[] args) {
        ECommercePlatform platform = new ECommercePlatform();

        // Admin registration and actions
        Admin admin = new Admin("1", "admin", "adminpass", "admin@example.com");
        platform.registerUser(admin);

        // Adding products
        Product p1 = new Product("p1", "Laptop", 999.99, 10);
        Product p2 = new Product("p2", "Smartphone", 499.99, 20);
        admin.addProduct(p1);
        admin.addProduct(p2);

        // Customer registration and actions
        Customer customer = new Customer("2", "customer", "custpass", "cust@example.com");
        platform.registerUser(customer);

        // Customer adds products to the cart
        customer.addToCart("p1", 2);
        customer.addToCart("p2", 1);
        System.out.println("Customer's cart after adding products:");
        customer.cart.viewCart();

        // Customer removes product from the cart
        customer.removeFromCart("p1", 1);
        System.out.println("Customer's cart after removing a product:");
        customer.cart.viewCart();

        // Customer checks out
        customer.checkout();
        System.out.println("Customer's order history after checkout:");
        customer.viewOrderHistory();

        // Display products in the platform
        System.out.println("Products in the platform:");
        platform.displayProducts();
    }
}
