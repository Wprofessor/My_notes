// 蛮力法解决0-1背包

import java.math.BigDecimal;
import java.text.DecimalFormat;
import java.util.*;

public class Main {
    private Vector<Vector<Integer>> res = new Vector<>();
    private Vector<Integer> single = new Vector<>();

    public static void main(String[] args) {
        ArrayList<Integer> w = new ArrayList<>();
        ArrayList<Integer> v = new ArrayList<>();
        Vector<Integer> temp = new Vector<>();
        Vector<Vector<Integer>> result = new Vector<>();
        Scanner cin = new Scanner(System.in);
        DecimalFormat ff = new DecimalFormat("0.0");
        int n, c;   //n表示物品数量，c表示背包容量
        Main m = new Main();
        System.out.println("请输入物品数量n和背包容量c：");
        while (cin.hasNext()) {
            n = cin.nextInt();
            c = cin.nextInt();
            for (int i = 0; i < n; i++) {
                temp.add(i);
            }
            int end = temp.size() - 1;
            result = m.getRes(temp,end);
            int x, y;
            for (int i = 0; i < n; i++) {
                System.out.println("请分别输入物品的重量和价值：");
                x = cin.nextInt();
                y = cin.nextInt();
                w.add(x);
                v.add(y);
            }
            // 暴力比较每个子集中的最大价值
            int maxValue = -1;
            for (int i = 0; i < result.size(); i++) {
                int sumV = 0,sumW = 0;
                for (int j = 0; j < result.get(i).size(); j++) {
                    int index = result.get(i).get(j);
                    sumW += w.get(index);
                    sumV += v.get(index);
                }
                if(sumW > c)
                    continue;
                else {
                    if (sumV > maxValue)
                        maxValue = sumV;
                }
            }
            System.out.println("最大价值为：");
            System.out.println(maxValue);

        }
    }

    public void cal(Vector<Integer> temp, int end) {
        if (end < 0) {
            if (single.size() != 0) {
                // System.out.println(single);
                res.add((Vector<Integer>) single.clone());  // 拷贝防止引用覆盖
                return;
            }
        } else {
            single.add(temp.get(end));
            cal(temp, end - 1);
            single.remove(single.size() - 1);
            cal(temp, end - 1);
        }
    }

    public Vector<Vector<Integer>> getRes(Vector<Integer> temp, int end) {
        cal(temp, end);
        return res;
    }
}



