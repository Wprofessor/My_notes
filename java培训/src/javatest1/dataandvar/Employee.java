package javatest1.dataandvar;

public class Employee extends Person { //员工
    private int salary;


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
    public String toString() {
        return getDescription();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if(obj == null)
            return false;
        if (getClass() != obj)
            return false;

        Employee other = (Employee) obj;
        return this.getName() == other.getName()
                && this.getSalary() == other.getSalary()
                &&this.getSex() == other.getSex();
    }
}
