// 0-1背包
import java.math.BigDecimal;
import java.text.DecimalFormat;
import java.util.*;

public class test {
    public static void main(String[] args) {
        ArrayList<Integer> w = new ArrayList<>();
        ArrayList<Integer> v = new ArrayList<>();
        Map<Character, Character> m = new HashMap<Character, Character>();
        Scanner cin = new Scanner(System.in);
        DecimalFormat ff = new DecimalFormat("0.0");
        int n, c;   //n表示物品数量，c表示背包容量
        int f[][] = new int[100][100];
        System.out.println("请输入物品数量n和背包容量c：");
        while (cin.hasNext()) {
            n = cin.nextInt();
            c = cin.nextInt();
            int x, y;
            for (int i = 0; i < n; i++) {
                System.out.println("请分别输入物品的重量和价值：");
                x = cin.nextInt();
                y = cin.nextInt();
                w.add(x);
                v.add(y);
            }
            // 从下到上
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= c; j++) {
                    if (j >= w.get(i - 1)) {
                        f[i][j] = Math.max(f[i - 1][j], f[i - 1][j - w.get(i - 1)] + v.get(i - 1));
                    } else
                        f[i][j] = f[i - 1][j];
                }
            }
            System.out.println("最大价值为：");
            System.out.println(f[n][c]);

        }
    }
}