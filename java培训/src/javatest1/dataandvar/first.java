package javatest1.dataandvar;

import java.util.Arrays;

public class first {
    public static void main(String[] args) {
        /*Employee e = new Employee("wang",1,7000);

        Manager m = new Manager("wang",1,8000,500);

        //向上转型：用父类引用子类的对象(会丢失子类信息)
        Employee el = new Manager("wang",1,8000,500);*/

        Employee employee1 = new Employee("Rick",1,7000);
        Employee employee2 = new Employee("Rick",1,8000);

        Employee[] employeeList = {employee1,employee2};

        Arrays.sort(employeeList);

        System.out.println(Arrays.toString(employeeList));

//        System.out.println(e.equals(m));
        Manager manager = new Manager("SuperRick",1,7000,5000);
        manager.save(new JDBDao.SaveListener() {
            @Override
            public void onSucceed(String response) {
                System.out.println(response);
            }

            @Override
            public void onFail(Exception e){
            }
        });
    }
}