package javatest1.classandobject;

import java.lang.ref.SoftReference;

public class Student {

    private String num;

    private String lab;

    private String sex;

    public Student(String lab) {
        this.lab = lab;
    }

    public Student(String lab, String sex) {
        this(lab);   //调用构造方法
        this.sex = sex;
    }

    public void setSex(String sex) {
        this.sex = sex;
    }

    public void setNum(String num) {
        this.num = num;
    }

    public void setLab(String lab) {
        this.lab = lab;
    }

    public String getNum() {
        return num;
    }

    public String getLab() {
        return lab;
    }

    public String getSex() {
        return sex;
    }

    public static void main(String[] args) {
        String wang = new String();

    }

}
