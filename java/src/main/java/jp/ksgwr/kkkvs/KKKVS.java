package jp.ksgwr.kkkvs;

public class KKKVS {

    public native void print();

    static {
        System.loadLibrary("jkkkvs");
    }
}
