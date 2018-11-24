package javatest1.dataandvar;

//final不能被继承
public final class ProductManager extends Manager{
    public ProductManager(String name, int sex, int salary, int bonus) {
        super(name, sex, salary, bonus);
    }

}
