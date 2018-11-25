package javatest1.dataandvar;

public class Main {
    public static void main(String[] args) {
        Employee employee = new Employee("java", 1, 15000);
        System.out.println(employee);
        System.out.println(new Employee("python", 1, 123));

        //创建对象的同时，定义类
        JDBDao.SaveListener saveListener = new JDBDao.SaveListener() {

            private int a = 123;

            public int getA() {
                return a;
            }

            @Override
            public void onSucceed(String jsonResponse) {
                System.out.println(jsonResponse);
                System.out.println("here    ");
                System.out.println(getA());
            }

            @Override
            public void onFail(Exception e) {
                System.out.println("请求失败");
            }
        };
        employee.save(saveListener);
    }
}
