package javatest1.classandobject.arrarlist.linkedlist;

import java.util.LinkedList;
/*
* 双向链表
*/
public class LinkedListDemo {
    public static void main(String[] args) {
        LinkedList<String> queue = new LinkedList<>();
        queue.add("st1");
        queue.add("st2");
        queue.add("st3");
        queue.add("st4");
        queue.add("st5");

        //尾部插入
        queue.offer("st6");
        //从头部删除
        queue.poll();

        for (String p:
             queue) {
            System.out.println(p);
        }
    }
}
