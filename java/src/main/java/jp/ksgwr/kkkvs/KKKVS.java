package jp.ksgwr.kkkvs;

public class KKKVS {

    public native void print();

    static {
        System.err.println(System.getProperty("java.library.path"));
        System.loadLibrary("jkkkvs");
    }
}
