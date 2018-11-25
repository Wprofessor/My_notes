package javatest1.classandobject.arrarlist;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class ArrayListDemo {

    public static void main(String[] args) {
        ArrayList<Person> personArrayList = new ArrayList<>();
        List<Person> additionList = new ArrayList<>();

        Person wang = new Person("wangtianrui", 25);

        personArrayList.add(wang);
        personArrayList.add(new Person("zhaolizhi", 21));
        personArrayList.add(new Person("zhao", 21));
        personArrayList.add(new Person("hao", 20));

        additionList.add(new Person("hao", 20));
        additionList.add(new Person("hao", 20));
        additionList.add(new Person("hao", 20));

        personArrayList.addAll(additionList);
        /*Iterator<Person> iterable = personArrayList.iterator();
        while (( iterable).hasNext()){
            System.out.println(((Iterator) iterable).next());
        }*/
        //类型：对象
       /* for (Person p:
                personArrayList) {
            System.out.println(p);
        }*/

        personArrayList.set(0, new Person("wangtianrui", 13));
        personArrayList.remove(0);
        for (Person p :
                personArrayList) {
            System.out.println(p);
        }

        List<Person> subList =  personArrayList.subList(0,2);
        for (Person p:
             subList) {
            System.out.println(p);
        }

//        Collections.sort(personArrayList);
        personArrayList.sort(new Comparator<Person>() {
            @Override
            public int compare(Person o1, Person o2) {
                return Integer.compare(o1.getAge(),o2.getAge());
            }
        });
        System.out.println("----排序后----");
        for (Person p:
                personArrayList) {
            System.out.println(p);
        }
    }
}
