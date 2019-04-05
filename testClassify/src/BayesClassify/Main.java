package BayesClassify;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        ArrayList<String> DataSet = new ArrayList<>();
        ArrayList<Integer> Labels = new ArrayList<>();
        ArrayList<Character> voast = new ArrayList<>();
        ArrayList<ArrayList<Integer>> TagData = new ArrayList<>();
        ArrayList<Double> p0 = new ArrayList<Double>();
        ArrayList<Double> p1 = new ArrayList<Double>();
        double pInsult;
        loadData test = new loadData();
        DataSet = test.InitData();
        Labels = test.InitLab();
        voast = test.createVocabList(DataSet);
        TagData = test.TagTrainData(voast, DataSet);
        BayesTrain bayesTrain = new BayesTrain();
        bayesTrain.train(TagData, Labels);
        p0 = bayesTrain.getP0();
        p1 = bayesTrain.getP1();
        pInsult = bayesTrain.getpInsult();
        String InputData = "玩一玩";
        ArrayList<Integer> temp = new ArrayList<>();
        temp =  test.SetWord(voast,InputData);
        System.out.println("分类是：");
        System.out.println(bayesTrain.ClassifyNB(temp,p0,p1,pInsult));

    }
}
