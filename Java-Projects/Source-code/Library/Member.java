package Library;

import java.util.ArrayList;

public class Member {
    private String name , memberID;
    private ArrayList<Book> booksIssued = new ArrayList<>();
    public Member(String name , String memberID)
    {
        this.name = name;
        this.memberID = memberID;
    }
    public void issueBook(Book book)
    {
        this.booksIssued.add(book);
    }
    public void returnBook(Book book)
    {
        this.booksIssued.remove(book);
    }
    public String getMemberID()
    {
        return this.memberID;
    }
    public void getMemberInfo()
    {
        System.out.println("Member's info :");
        System.out.println("Name : " + this.name);
        System.out.println("ID : " + this.memberID);
    }

}
