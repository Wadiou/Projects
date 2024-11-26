package Platform;

public interface Manageable {
    void addProduct(Product product);
    void removeProduct(String productID);
    void updateProduct(String productID, int newQuantity);
}
