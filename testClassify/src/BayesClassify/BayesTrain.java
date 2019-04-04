package BayesClassify;

import java.util.ArrayList;

public class BayesTrain {
    private ArrayList<Double> p0 = new ArrayList<Double>();
    private ArrayList<Double> p1 = new ArrayList<Double>();
    private double pInsult;
    loadData data = new loadData();
    public void train()

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
