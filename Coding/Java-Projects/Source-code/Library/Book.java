package Library;

public class Book implements Borrowable{
    private String title , author , isbn ;
    boolean isIssued;
    public Book(String title , String author ,String isbn)
    {
        this.title = title;
        this.author = author;
        this.isbn = isbn;
        this.isIssued = false;
    }
    public String getIsbn()
    {
        return this.isbn;
    }
    public void getBookInfo(){
        System.out.println("Book's info :");
        System.out.println("Title : " + this.title);
        System.out.println("Author : " + this.author);
        System.out.println("ISBN : " + this.isbn);
    }

    @Override
    public void borrowItem() {
        this.isIssued = true;
    }

    @Override
    public void returnItem() {
        this.isIssued = false;
    }
}
