package Library;

public class librarytest {
    public static void main(String[] args) {
        Library library = new Library();

        Book book1 = new Book("Java Programming", "Author A", "ISBN001");
        Book book2 = new Book("Python Programming", "Author B", "ISBN002");

        library.addBook(book1);
        library.addBook(book2);

        Member member1 = new Member("John Doe", "MEM001");
        library.addMember(member1);

        library.issueBook("ISBN001", "MEM001");
        library.returnBook("ISBN001", "MEM001");

        book1.getBookInfo();
        member1.getMemberInfo();
    }
}
