package Platform;

import java.util.ArrayList;

public class ECommercePlatform {

    public static ArrayList<Product> products = new ArrayList<>();
    public static ArrayList<User> users = new ArrayList<>();

    public void registerUser(User user) {
        users.add(user);
        System.out.println("User registered: " + user.getUsername());
    }

    public static void addProduct(Product product) {
        products.add(product);
        System.out.println("Product added: " + product.getName());
    }

    public static void removeProduct(Product product) {
        products.remove(product);
        System.out.println("Product removed: " + product.getName());
    }

    public User findUserByID(String userID) {
        for (User user : users) {
            if (user.getUserID().equals(userID)) {
                return user;
            }
        }
        return null;
    }

    public static Product findProductByID(String productID) {
        for (Product product : products) {
            if (product.getProductID().equals(productID)) {
                return product;
            }
        }
        return null;
    }

    public static void updateProductQuantity(String productID, int newQuantity) {
        Product product = findProductByID(productID);
        if (product != null) {
            product.setQuantity(newQuantity);
        }
    }

    public void displayProducts() {
        System.out.println("Products Info: ");
        for (Product product : products) {
            product.getProductInfo();
        }
    }
}
