package BayesClassify;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class test {
    public static void main(String[] args) {
        Map<Character,Integer> map = new HashMap<>();
        map.put('王',1);
        map.put('佳',2);
        map.put('豪',3);
        map.put('哈',4);
        System.out.println(map.get("嗯".charAt(0)));
    }
}
