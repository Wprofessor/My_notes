package javatest1;

import javatest1.dataandvar.Employee;
import javatest1.dataandvar.Manager;

import javax.swing.plaf.synth.SynthOptionPaneUI;

public class first {
    public static void main(String[] args) {
        Employee e = new Employee("wang",1,7000);

        Manager m = new Manager("wang",1,8000,500);

        //向上转型：用父类引用子类的对象(会丢失子类信息)
        Employee el = new Manager("wang",1,8000,500);



        System.out.println(e.equals(m));
    }
}