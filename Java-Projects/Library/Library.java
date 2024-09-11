package Library;

import java.util.ArrayList;

public class Library {
    private static ArrayList<Book> books = new ArrayList<>();
    private static ArrayList<Member> members = new ArrayList<>();
    public void addBook (Book book)
    {
        books.add(book);
    }
    public void removeBook (Book book)
    {
        books.remove(book);
    }
    public void addMember (Member member)
    {
        members.add(member);
    }
    public void removeMember (Member member)
    {
        members.remove(member);
    }
    public void issueBook (String isbn , String memberID)
    {
        Book book= LibraryHelper.Findby_ISBN(isbn);
        Member member = LibraryHelper.Findby_ID(memberID);
        if (book != null && member != null && !book.isIssued)
        {
            book.borrowItem();
            member.issueBook(book);
        }
    }
    public void returnBook (String isbn , String memberID)
    {
        Book book= LibraryHelper.Findby_ISBN(isbn);
        Member member = LibraryHelper.Findby_ID(memberID);
        if (book != null && member != null && book.isIssued)
        {
            book.returnItem();
            member.returnBook(book);
        }
    }

    private class LibraryHelper
    {
        public static Book Findby_ISBN(String isbn)
        {
            for (Book book : books)
            {
                if (book.getIsbn().equals(isbn))
                    return book;
            }
            return null;
        }
        public static Member Findby_ID(String ID)
        {
            for (Member member : members)
            {
                if (member.getMemberID().equals(ID))
                    return member;
            }
            return null;
        }
    }

}
