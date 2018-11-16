import java.text.DecimalFormat;
import java.util.*;

public class Main {
    private int[][] t = {{0, 1}, {0, -1}, {1, 1}, {1, -1}, {1, 0}, {-1, 0}, {-1, 1}, {-1, -1}};

    public static void main(String[] args) {

        Scanner cin = new Scanner(System.in);
        DecimalFormat ff = new DecimalFormat("0.0");
        Main val = new Main();
        while (cin.hasNext()) {
            char[][] map = new char[105][105];
            String[] str = new String[105];
            int count = 0;
            int m, n;
            m = cin.nextInt();
            n = cin.nextInt();
            if (m == 0)
                break;
            for (int i = 0; i < m; i++) {
                str[i] = cin.next();
            }
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    map[i][j] = str[i].charAt(j);
                }
            }

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (map[i][j] == '@') {
                        val.DFS(i, j, m, n, map);
                        count++;
                    }
                }
            }
            System.out.println(count);
        }
    }

    public Boolean judge(int x, int y, int m, int n, char[][] map) {    //判断是否继续DFS
        if (x >= 0 && x < m && y >= 0 && y < n && map[x][y] == '@')
            return true;
        return false;
    }

    public void DFS(int x, int y, int m, int n, char[][] map) {
        int tx, ty;
        map[x][y] = '*';                      //每次都做标记
        for (int i = 0; i < 8; i++) {
            tx = x + t[i][0];
            ty = y + t[i][1];
            if (judge(tx, ty, m, n, map)) {
                DFS(tx, ty, m, n, map);
            }
        }
    }
}