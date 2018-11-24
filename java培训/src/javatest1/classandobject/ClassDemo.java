package javatest1.classandobject;

public class ClassDemo {
    /**
     * 面向对象
     * 1.成员变量
     * 2.成员方法
     * 3.类成员
     * <p>
     * 实例（对象）
     */

    /**
     *四种访问权限
     *
     * 1.public
     * 2.protected
     * private
     *
     */
    String name;
    int age;

    ClassDemo(String name) {     //重载
        this.name = name;
    }

    ClassDemo(String name, int age) {
        this.name = name;
        this.age = age;
    }

    void show() {
        System.out.println("姓名： " + name + "年龄： " + age);
    }

    public static void main(String[] args) {
        ClassDemo person = new ClassDemo("王佳豪", 20);
        ClassDemo p1 = person;
    }
}
