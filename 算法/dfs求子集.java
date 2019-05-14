import java.util.Scanner;
import java.util.Vector;

public class SolveSubset {
    private Vector<Vector<Integer>> res = new Vector<>();
    private Vector<Integer> single = new Vector<>();

    public static void main(String[] args) {
        Vector<Integer> temp = new Vector<>();
        Scanner cin = new Scanner(System.in);
        System.out.println("输入集合大小:");
        SolveSubset m = new SolveSubset();
        while (cin.hasNext()) {
            int n, x;

            n = cin.nextInt();
            for (int i = 0; i < n; i++) {
                System.out.println("输入集合元素:");
                x = cin.nextInt();
                temp.add(x);
            }
            int end = temp.size() - 1;
            System.out.println("子集是：");
            System.out.println(m.getRes(temp, end));
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
