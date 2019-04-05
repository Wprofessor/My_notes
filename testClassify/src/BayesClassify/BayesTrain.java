package BayesClassify;

import java.awt.event.KeyAdapter;
import java.util.ArrayList;

public class BayesTrain {
    private ArrayList<Double> p0 = new ArrayList<Double>();
    private ArrayList<Double> p1 = new ArrayList<Double>();
    private double pInsult;
    loadData data = new loadData();

    public void train(ArrayList<ArrayList<Integer>> lisnewVocaset, ArrayList<Integer> Labels) {
        int labNum = lisnewVocaset.size();
        int numWord = lisnewVocaset.get(0).size();
        int sum = 0;
        for (int i = 0; i < Labels.size(); i++) {
            sum += Labels.get(i);
        }
        this.pInsult = sum / labNum;
        ArrayList<Integer> p0num = new ArrayList<>();
        ArrayList<Integer> p1num = new ArrayList<>();

        for (int i = 0; i < numWord; i++) {
            p0num.add(1);
            p1num.add(1);
        }
        int p0Denom = 2;
        int p1Denom = 2;
        for (int i = 0; i < labNum; i++) {
            if (Labels.get(i) == 1) {
                for (int j = 0; j < numWord; j++) {
                    p1num.set(j, p1num.get(i) + lisnewVocaset.get(i).get(j));
                }
                p1Denom += 1;
            } else {
                for (int j = 0; j < numWord; j++) {
                    p0num.set(j, p0num.get(i) + lisnewVocaset.get(i).get(j));
                }
                p0Denom += 1;
            }
        }
        for (int i = 0; i < numWord; i++) {
            this.p0.add(Math.log(p0num.get(i) / p0Denom));
            this.p1.add(Math.log(p1num.get(i) / p1Denom));
        }
    }

    /**
     * 分类函数
     *
     * @return
     */
    public int ClassifyNB(ArrayList<Integer> InputData, ArrayList<Double> p0, ArrayList<Double> p1, Double pInsult) {
        double p0vec;
        double p1vec;
        double sum1 = 0.0, sum2 = 0.0;
        for (int i = 0; i < p0.size(); i++) {
            sum1 += InputData.get(i) * p0.get(i);
            sum2 += InputData.get(i) * p1.get(i);
        }
        p0vec = sum1 + Math.log(pInsult);
        p1vec = sum2 + Math.log(pInsult);
        if (p0vec > p1vec)
            return 0;
        else
            return 1;
    }

    public ArrayList<Double> getP0() {
        return p0;
    }

    public ArrayList<Double> getP1() {
        return p1;
    }

    public double getpInsult() {
        return pInsult;
    }
}
