package javatest1.dataandvar;

public abstract class Person {


    private String name;
    private int sex;

    public Person() {

    }

    public Person(String name, int sex) {
        this.name = name;
        this.sex = sex;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getSex() {
        return sex;
    }

    public void setSex(int sex) {
        this.sex = sex;
    }


    /**
     * 用于对Person的描述
     * @return 返回对人的描述信息
     */
    public abstract String getDescription() ;

    public abstract void save(JDBDao.SaveListener listener);
}
