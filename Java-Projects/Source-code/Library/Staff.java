package Library;

public class Staff extends Member {
    private String staffID , position;
    public Staff(String staffID , String position , String name ,String memberID)
    {
        super(name,memberID);
        this.staffID = staffID;
        this.position = position;
    }
    @Override
    public void getMemberInfo()
    {
        super.getMemberInfo();
        System.out.println("Position : " + this.position);
        System.out.println("ID : " + this.staffID);
    }
}
