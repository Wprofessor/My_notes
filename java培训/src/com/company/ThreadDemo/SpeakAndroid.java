package com.company.ThreadDemo;

public class SpeakAndroid extends Thread{

    @Override
    public void run() {
        for (int i = 1; i <= 20; i++) {
            System.out.println("Anodroid " + i);
        }
    }
}