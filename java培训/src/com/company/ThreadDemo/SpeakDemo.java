package com.company.ThreadDemo;

public class SpeakDemo {
    public static void main(String[] args) {
        SpeakAndroid speakAndroid;
        SpeakLab speakLab;
        speakLab = new SpeakLab();
        speakAndroid = new SpeakAndroid();
        speakAndroid.start();
        speakLab.start();
        for (int i = 1; i <= 10; i++) {
            System.out.println("hello " + i +"");
        }
    }
}
