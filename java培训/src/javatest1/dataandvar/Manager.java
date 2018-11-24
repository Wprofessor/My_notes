package javatest1.dataandvar;

public class Manager extends Employee {

    private int bonus;

    public int getBonus() {
        return bonus;
    }

    public void setBonus(int bonus) {
        this.bonus = bonus;
    }

    public Manager(String name, int sex, int salary, int bonus) {
        super(name, sex, salary);     //父类构造函数
        this.bonus = (int) (bonus * Math.random());
    }

    @Override
    public int getSalary() {
        int baseSalary = super.getSalary() + getBonus();
//        return super.getSalary()+1;
        return baseSalary;
    }

    //final类不能被重写
    public  final int test() {
        return 0;
    }
}
