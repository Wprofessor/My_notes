package javatest1.dataandvar;

public class Employee extends Person implements Comparable<Employee> { //员工
    private int salary;


    public Employee() {

    }

    public Employee(String name, int sex, int salary) {
        super(name, sex);
        this.salary = salary;
    }

    public int getSalary() {
        return salary;
    }

    public void setSalary(int salary) {
        this.salary = salary;
    }

    //同名方法重载
    public void setSalary(int salary, int pyDeal) {
        this.salary = salary + pyDeal;
    }

    @Override
    public String getDescription() {
        return getName() + "性别： " + getName() + getSex() + getSalary();
    }

    @Override
    public void save(JDBDao.SaveListener listener) {

    }

    @Override
    public String toString() {
        return "Employee{" +
                "name = '" + super.getName() +'\''+",sex = " + super.getSex()+
                "salary=" + salary +
                '}';
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj)
            return false;

        Employee other = (Employee) obj;
        return (this.getName() == other.getName())
                && (this.getSalary() == other.getSalary())
                && (this.getSex() == other.getSex());
    }

    //排序次序
    @Override
    public int compareTo(Employee o) {
        return Integer.compare(getSalary(),o.getSalary());
    }
}
