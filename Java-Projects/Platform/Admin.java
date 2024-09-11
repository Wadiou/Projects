package Platform;

public class Admin extends User implements Manageable {

    public Admin(String userID, String username, String password, String email) {
        super(userID, username, password, email);
    }

    @Override
    public void addProduct(Product product) {
        ECommercePlatform.addProduct(product);
    }

    @Override
    public void removeProduct(String productID) {
        Product product = ECommercePlatform.findProductByID(productID);
        if (product != null) {
            ECommercePlatform.removeProduct(product);
        } else {
            System.out.println("Product not found!");
        }
    }

    @Override
    public void updateProduct(String productID, int newQuantity) {
        Product product = ECommercePlatform.findProductByID(productID);
        if (product != null) {
            product.setQuantity(newQuantity);
            ECommercePlatform.updateProductQuantity(productID, newQuantity);
        } else {
            System.out.println("Product not found!");
        }
    }
}
