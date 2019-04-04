package BayesClassify;

public class Main {
    public static void main(String[] args) {
        loadData test = new loadData();
        System.out.println(test.createVocabList(test.InitData()));
    }
}
