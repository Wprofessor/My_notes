package com.company.ThreadDemo;

import java.util.concurrent.ThreadLocalRandom;

public class SpeakLab extends Thread {
    @Override
    public void run() {
        for (int i = 1; i <= 20; i++) {
            System.out.println("Lab" + i);
        }
    }
}
